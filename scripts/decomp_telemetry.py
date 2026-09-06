#!/usr/bin/env python3
"""Record and report matching-decompilation throughput and exhausted candidates."""

from __future__ import annotations

import argparse
import json
import subprocess
from datetime import datetime, timezone
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
METRICS = ROOT / "config" / "decomp_metrics.jsonl"
REJECTIONS = ROOT / "config" / "decomp_rejections.json"
TOTAL_FUNCTIONS = 7017


def read_jsonl(path: Path) -> list[dict]:
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]


def write_jsonl_record(path: Path, record: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a", encoding="utf-8", newline="\n") as stream:
        stream.write(json.dumps(record, sort_keys=True, separators=(",", ":")) + "\n")


def current_commit() -> str:
    return subprocess.check_output(
        ["git", "rev-parse", "HEAD"], cwd=ROOT, text=True
    ).strip()


def parse_timestamp(value: str) -> datetime:
    return datetime.fromisoformat(value.replace("Z", "+00:00"))


def record_snapshot(args: argparse.Namespace) -> None:
    if not 0 <= args.functions <= TOTAL_FUNCTIONS:
        raise SystemExit(f"functions must be between 0 and {TOTAL_FUNCTIONS}")
    record = {
        "timestamp": datetime.now(timezone.utc).isoformat().replace("+00:00", "Z"),
        "commit": current_commit(),
        "phase": args.phase,
        "functions": args.functions,
        "total_functions": TOTAL_FUNCTIONS,
        "matched_text_bytes": args.matched_bytes,
        "accepted_candidates": args.accepted,
        "attempted_candidates": args.attempted,
        "rejected_candidates": args.rejected,
        "model": args.model,
        "wall_minutes": args.wall_minutes,
        "gate_seconds": args.gate_seconds,
        "coordination_minutes": args.coordination_minutes,
    }
    if args.usage_used_percent is not None:
        record["usage_used_percent"] = args.usage_used_percent
    if args.usage_resets_at is not None:
        record["usage_resets_at"] = args.usage_resets_at
    if args.note:
        record["note"] = args.note
    write_jsonl_record(METRICS, record)
    print(f"Recorded {args.functions}/{TOTAL_FUNCTIONS} at {record['commit'][:8]}.")


def rate(first: dict, last: dict) -> dict[str, float] | None:
    hours = (parse_timestamp(last["timestamp"]) - parse_timestamp(first["timestamp"])).total_seconds() / 3600
    if hours <= 0:
        return None
    result = {
        "hours": hours,
        "functions": last["functions"] - first["functions"],
        "bytes": last["matched_text_bytes"] - first["matched_text_bytes"],
    }
    result["functions_per_hour"] = result["functions"] / hours
    result["bytes_per_hour"] = result["bytes"] / hours
    if (
        first.get("usage_resets_at") == last.get("usage_resets_at")
        and first.get("usage_used_percent") is not None
        and last.get("usage_used_percent") is not None
    ):
        used = last["usage_used_percent"] - first["usage_used_percent"]
        if used > 0:
            result["functions_per_usage_percent"] = result["functions"] / used
            result["bytes_per_usage_percent"] = result["bytes"] / used
    return result


def report(_: argparse.Namespace) -> None:
    records = read_jsonl(METRICS)
    if not records:
        raise SystemExit("No throughput snapshots recorded.")
    print("Decompilation throughput")
    phases: dict[str, list[dict]] = {}
    for item in records:
        phases.setdefault(item["phase"], []).append(item)
    for phase, items in phases.items():
        first, last = items[0], items[-1]
        print(f"  {phase}: {len(items)} snapshot(s), {last['functions']}/{TOTAL_FUNCTIONS}")
        measured = rate(first, last)
        if measured is None:
            print("    awaiting a later snapshot")
            continue
        print(
            f"    +{measured['functions']:.0f} functions, +{measured['bytes']:.0f} bytes "
            f"in {measured['hours']:.2f} h"
        )
        print(
            f"    {measured['functions_per_hour']:.2f} functions/h, "
            f"{measured['bytes_per_hour']:.0f} bytes/h"
        )
        if "functions_per_usage_percent" in measured:
            print(
                f"    {measured['functions_per_usage_percent']:.2f} functions and "
                f"{measured['bytes_per_usage_percent']:.0f} bytes per usage point"
            )


def load_rejections() -> dict:
    if not REJECTIONS.exists():
        return {"version": 1, "entries": []}
    return json.loads(REJECTIONS.read_text(encoding="utf-8"))


def save_rejections(data: dict) -> None:
    with REJECTIONS.open("w", encoding="utf-8", newline="\n") as stream:
        stream.write(json.dumps(data, indent=2) + "\n")


def reject(args: argparse.Namespace) -> None:
    data = load_rejections()
    entries = data.setdefault("entries", [])
    existing = next((item for item in entries if item["symbol"] == args.symbol), None)
    record = {
        "symbol": args.symbol,
        "status": "exhausted",
        "attempts": args.attempts,
        "mismatch_class": args.mismatch_class,
        "required_evidence": args.required_evidence,
    }
    if existing is None:
        entries.append(record)
    else:
        existing.update(record)
    entries.sort(key=lambda item: item["symbol"])
    save_rejections(data)
    print(f"Recorded exhausted candidate {args.symbol}.")


def list_rejections(_: argparse.Namespace) -> None:
    entries = load_rejections().get("entries", [])
    for item in entries:
        print(
            f"{item['symbol']}: {item['mismatch_class']} "
            f"(retry when {item['required_evidence']})"
        )


def parser() -> argparse.ArgumentParser:
    result = argparse.ArgumentParser()
    commands = result.add_subparsers(dest="command", required=True)

    snapshot = commands.add_parser("snapshot")
    snapshot.add_argument("--phase", required=True)
    snapshot.add_argument("--functions", type=int, required=True)
    snapshot.add_argument("--matched-bytes", type=int, required=True)
    snapshot.add_argument("--accepted", type=int, default=0)
    snapshot.add_argument("--attempted", type=int, default=0)
    snapshot.add_argument("--rejected", type=int, default=0)
    snapshot.add_argument("--model", default="unspecified")
    snapshot.add_argument("--wall-minutes", type=float, default=0)
    snapshot.add_argument("--gate-seconds", type=float, default=0)
    snapshot.add_argument("--coordination-minutes", type=float, default=0)
    snapshot.add_argument("--usage-used-percent", type=float)
    snapshot.add_argument("--usage-resets-at", type=int)
    snapshot.add_argument("--note")
    snapshot.set_defaults(func=record_snapshot)

    show = commands.add_parser("report")
    show.set_defaults(func=report)

    rejected = commands.add_parser("reject")
    rejected.add_argument("symbol")
    rejected.add_argument("--attempts", type=int, default=2)
    rejected.add_argument("--mismatch-class", required=True)
    rejected.add_argument("--required-evidence", required=True)
    rejected.set_defaults(func=reject)

    rejected_list = commands.add_parser("rejections")
    rejected_list.set_defaults(func=list_rejections)
    return result


def main() -> None:
    args = parser().parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
