#!/usr/bin/env python3
"""Trial both CPU engines on identical drafts and save results without model polling."""

import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
from types import SimpleNamespace

from decomp_mutate import run_search


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("manifest", help="JSON with cases: [{function, source}]")
    parser.add_argument("--seconds", type=int, default=30, help="per engine per function")
    parser.add_argument("--jobs", type=int, default=8, help="total compiler workers, divided equally")
    parser.add_argument("--output", required=True)
    parser.add_argument("--work-root", required=True, help="prefer native Linux storage under WSL")
    parser.add_argument("--tools", default=os.environ.get("MLSS_MUTATION_TOOLS", str(Path.home() / ".cache/mlss-mutation")))
    args = parser.parse_args()
    if args.jobs < 2 or args.jobs > 32 or args.jobs % 2 or args.seconds < 1:
        parser.error("use 2..32 even total workers and positive seconds")
    manifest = json.loads(Path(args.manifest).read_text())
    results = []
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    for case in manifest["cases"]:
        with ThreadPoolExecutor(max_workers=2) as pool:
            futures = [pool.submit(run_search, SimpleNamespace(
                function=case["function"], source=case["source"], engine=engine,
                seconds=args.seconds, jobs=args.jobs // 2, seed=1, tools=args.tools,
                work_root=args.work_root, max_compiles=10000, prepare_only=False))
                for engine in ("transmuter", "permuter")]
            pair = [future.result() for future in futures]
        if pair[0]["source_sha256"] != pair[1]["source_sha256"]:
            raise RuntimeError("input changed between engine runs")
        if pair[0].get("preprocessed_sha256") != pair[1].get("preprocessed_sha256"):
            raise RuntimeError("preprocessed inputs differ between engine runs")
        results.extend(pair)
        output.write_text(json.dumps({"seconds_per_engine": args.seconds, "total_workers": args.jobs,
                                      "results": results}, indent=2) + "\n")
        print(case["function"], "; ".join(f'{r["engine"]}: {r["status"]}, '
              f'{r.get("compile_attempts", 0)} compiles' for r in pair), flush=True)


if __name__ == "__main__":
    main()
