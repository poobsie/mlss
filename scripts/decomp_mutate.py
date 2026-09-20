#!/usr/bin/env python3
"""Run bounded CPU mutation searches; independently verify best linked bytes."""

import argparse
import hashlib
import json
import os
import re
import shlex
import shutil
import signal
import subprocess
import tempfile
import time
from pathlib import Path

from decomp_local import ROOT, Runner, build_flags, compare_span, reference_symbols
from decomp_workflow import candidate_by_name, canonical_candidate_block


def target_assembly(candidate, block):
    """Build a target whose emitted function must equal the canonical span."""
    block = canonical_candidate_block(candidate, block)
    return (
        '.include "asm/macros.inc"\n.syntax unified\n.text\n'
        + block
        + f"\n.if (. - {candidate.name}) != {candidate.size}\n"
        + f'.error "{candidate.name} assembly does not match its mapped span"\n'
        + ".endif\n"
        + f".size {candidate.name}, .-{candidate.name}\n"
    )


TRANSMUTER_FINALIZATION_GRACE_SECONDS = 30


def bounded_process(command, seconds, log, cwd, checkpoint=None):
    """Kill the complete search process group, including compiler children, on expiry."""
    start = time.monotonic()
    with log.open("w") as stream:
        process = subprocess.Popen(command, cwd=cwd, stdout=stream, stderr=subprocess.STDOUT,
                                   start_new_session=True)
        timed_out = False
        try:
            deadline = start + seconds
            while process.poll() is None:
                remaining = deadline - time.monotonic()
                if remaining <= 0:
                    timed_out = True
                    break
                try:
                    process.wait(timeout=min(1, remaining))
                except subprocess.TimeoutExpired:
                    if checkpoint is not None:
                        checkpoint()
        finally:
            if checkpoint is not None:
                checkpoint()
            # Workers can survive a failed or interrupted parent. Never leave them running.
            try:
                os.killpg(process.pid, signal.SIGTERM)
            except ProcessLookupError:
                pass
            try:
                process.wait(timeout=2)
            except subprocess.TimeoutExpired:
                pass
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            process.wait()
    return {"returncode": process.returncode, "timed_out": timed_out,
            "wall_seconds": round(time.monotonic() - start, 3)}


def checkpoint_best_source(folder, checkpoint_dir):
    """Persist the current engine checkpoint outside a volatile work root."""
    candidates = []
    direct_best = folder / "best.c"
    if direct_best.exists():
        candidates.append((0, direct_best, None))
    for source in folder.glob("output-*/source.c"):
        try:
            score = int((source.parent / "score.txt").read_text())
        except (OSError, ValueError):
            continue
        candidates.append((score, source, score))
    if not candidates:
        return
    _, source, score = min(candidates, key=lambda item: item[0])
    try:
        payload = source.read_bytes()
    except OSError:
        return
    checkpoint_dir.mkdir(parents=True, exist_ok=True)
    temporary = checkpoint_dir / "best.c.tmp"
    temporary.write_bytes(payload)
    temporary.replace(checkpoint_dir / "best.c")
    score_text = "unknown" if score is None else str(score)
    (checkpoint_dir / "best-score.txt").write_text(score_text + "\n")
    engine = folder / "engine.json"
    try:
        engine_payload = engine.read_bytes()
        json.loads(engine_payload)
    except (OSError, ValueError):
        return
    engine_temporary = checkpoint_dir / "engine.json.tmp"
    engine_temporary.write_bytes(engine_payload)
    engine_temporary.replace(checkpoint_dir / "engine.json")


def run_transmuter_process(command, seconds, log, cwd, checkpoint=None):
    """Allow Transmuter to drain workers and write its final checkpoint."""
    return bounded_process(
        command, seconds + TRANSMUTER_FINALIZATION_GRACE_SECONDS, log, cwd,
        checkpoint)


def search_checkpoint_error(engine, process, compile_attempts, best_exists, search):
    if best_exists and search.get("baseScore") is not None:
        return None
    if (engine == "transmuter" and process.get("timed_out")
            and compile_attempts > 0):
        return ("timeout before final checkpoint after "
                f"{compile_attempts} compiler launches; search outcome unavailable")
    return "search failed to initialize; see engine.log"


def link_compare(obj, symbol, address, expected, folder, flags, symbols, aliases=None):
    folder.mkdir(exist_ok=True)
    runner = Runner(20, folder)
    defined = reference_symbols(runner, obj)
    if symbol not in defined or defined[symbol] & ~1:
        raise ValueError("candidate must define the target first in its text section")
    linker = folder / "verify.ld"
    linker.write_text(f"SECTIONS {{ .text 0x{address:X} : {{ *(.text*) }} "
                      + ".rodata : { *(.rodata*) } .data : { *(.data*) } .bss : { *(.bss*) } }\n")
    elf, binary = folder / "verify.elf", folder / "verify.bin"
    imports = ["--just-symbols=" + str(ROOT / ".decomp-tools/reference/mlss.elf")]
    if aliases:
        imports.append("--just-symbols=" + str(aliases))
    runner.run(flags["LD"] + imports + [
                               "-T", str(linker), "-o", str(elf), str(obj)])
    linked = reference_symbols(runner, elf)
    if linked.get(symbol, 0) & ~1 != address:
        raise ValueError("linked target address changed")
    runner.run(flags["OBJCOPY"] + ["-O", "binary", "--only-section=.text", str(elf), str(binary)])
    return compare_span(binary.read_bytes(), expected)


def compiler_script(folder, flags):
    script = folder / "compile.sh"
    # Inputs have already been preprocessed with the repository's real CPPFLAGS.
    script.write_text("#!/usr/bin/env bash\nset -euo pipefail\n"
                      + "cd " + shlex.quote(str(ROOT)) + "\n"
                      + 'input="$1"\noutput="$3"\n'
                      + "trap 'rm -f -- \"$output.s\"' EXIT\n"
                      + "printf '1\\n' >> " + shlex.quote(str(folder / "compiles.log")) + "\n"
                      + shlex.join(flags["CC1"]) + ' "$input" ' + shlex.join(flags["CFLAGS"])
                      + ' -o "$output.s"\n'
                      + 'printf "\\n.text\\n.align 2, 0\\n" >> "$output.s"\n'
                      + shlex.join(flags["AS"] + flags["ASFLAGS"]) + ' -o "$output" "$output.s"\n')
    script.chmod(0o755)
    return script


def run_search(args):
    tool_root = Path(args.tools).expanduser().resolve()
    source = Path(args.source).resolve()
    root = Path(args.work_root).resolve()
    root.mkdir(parents=True, exist_ok=True)
    folder = Path(tempfile.mkdtemp(prefix=args.function + "-", dir=root))
    checkpoint_dir = Path(args.checkpoint_dir).resolve() if args.checkpoint_dir else None
    report = {"function": args.function, "engine": args.engine, "source_sha256":
              hashlib.sha256(source.read_bytes()).hexdigest(), "seconds": args.seconds,
              "jobs": args.jobs, "seed": args.seed if args.engine == "transmuter" else None, "artifacts": str(folder),
              "acceptance_required": True}
    if checkpoint_dir is not None:
        report["checkpoint_dir"] = str(checkpoint_dir)
    try:
        candidate, block = getattr(args, "target", None) or candidate_by_name(args.function, ROOT / "mlss.map")
        aliases = getattr(args, "symbols_elf", None)
        if candidate.mode != "thumb":
            raise ValueError("trial adapter supports Thumb only")
        runner = Runner(45, folder)
        flags = build_flags(runner)
        expected_rom = (ROOT / ".decomp-tools/reference/mlss.gba").read_bytes()
        offset = candidate.address - 0x08000000
        if offset < 0 or offset + candidate.size > len(expected_rom):
            raise ValueError("target span outside reference")
        expected = expected_rom[offset:offset + candidate.size]
        symbols = reference_symbols(runner, ROOT / ".decomp-tools/reference/mlss.elf")
        target_asm, target_obj = folder / "target.s", folder / "target.o"
        target_asm.write_text(target_assembly(candidate, block))
        runner.run(flags["AS"] + flags["ASFLAGS"] + ["-o", str(target_obj), str(target_asm)])
        target_check = link_compare(target_obj, args.function, candidate.address, expected,
                                    folder / "target-check", flags, symbols, aliases)
        if target_check["status"] != "span_match":
            raise ValueError("assembled target does not match the full reference span: " + json.dumps(target_check))
        raw = source.read_text()
        # Historical drafts use SEC solely to choose a holding-file section. Do not erase
        # packed/aligned attributes or change source types while preparing the benchmark.
        raw = re.sub(r"^#define SEC\(name\).*$", "#define SEC(name)", raw, flags=re.MULTILINE)
        prepared = folder / "input.c"
        prepared.write_text(raw)
        base = folder / "base.c"
        runner.run(flags["CPP"] + flags["CPPFLAGS"] + ["-P", str(prepared), "-o", str(base)])
        report["preprocessed_sha256"] = hashlib.sha256(base.read_bytes()).hexdigest()
        compile_script = compiler_script(folder, flags)
        base_obj = folder / "base.o"
        runner.run([str(compile_script), str(base), "-o", str(base_obj)])
        report["baseline"] = link_compare(base_obj, args.function, candidate.address, expected,
                                           folder / "baseline-check", flags, symbols, aliases)
        if report["baseline"]["status"] == "span_match":
            report["status"] = "already_matching"
            return report
        if args.prepare_only:
            report["status"] = "ready"
            return report
        (folder / "compiles.log").write_text("")
        if args.engine == "transmuter":
            best = folder / "best.c"
            config = {"toolRoot": str(tool_root), "source": str(base), "function": args.function,
                      "target": str(target_obj), "compiler": shlex.quote(str(compile_script))
                      + ' "{{inputPath}}" -o "{{outputPath}}"', "cwd": str(ROOT),
                      "jobs": args.jobs, "seconds": args.seconds, "maxCompiles": args.max_compiles,
                      "seed": args.seed, "bestSource": str(best), "result": str(folder / "engine.json")}
            (folder / "engine-config.json").write_text(json.dumps(config))
            command = [str(tool_root / "bun-linux-x64/bun"), str(ROOT / "scripts/transmuter-run.mjs"),
                       str(folder / "engine-config.json")]
            report["process"] = run_transmuter_process(
                command, args.seconds, folder / "engine.log", ROOT,
                (lambda: checkpoint_best_source(folder, checkpoint_dir))
                if checkpoint_dir is not None else None)
            if (folder / "engine.json").exists():
                report["search"] = json.loads((folder / "engine.json").read_text())
        else:
            (folder / "settings.toml").write_text(f'func_name = "{args.function}"\ncompiler_type = "gcc"\n')
            command = [str(tool_root / "venv/bin/python"), "-u",
                       str(tool_root / "decomp-permuter/permuter.py"), str(folder),
                       "-j", str(args.jobs), "--stop-on-zero", "--best-only", "--quiet"]
            report["process"] = bounded_process(
                command, args.seconds, folder / "engine.log", ROOT,
                (lambda: checkpoint_best_source(folder, checkpoint_dir))
                if checkpoint_dir is not None else None)
            outputs = sorted(folder.glob("output-*/source.c"),
                             key=lambda path: int((path.parent / "score.txt").read_text()))
            best = outputs[0] if outputs else base
            log = (folder / "engine.log").read_text(errors="replace")
            baseline = re.search(r"base score = (\d+)", log)
            report["internal_errors"] = log.count("internal permuter failure")
            report["search"] = {"baseScore": int(baseline[1]) if baseline else None,
                                "bestScore": int((best.parent / "score.txt").read_text()) if outputs
                                else (int(baseline[1]) if baseline else None)}
        report["compile_attempts"] = len((folder / "compiles.log").read_text().splitlines())
        checkpoint_error = search_checkpoint_error(
            args.engine, report.get("process", {}), report["compile_attempts"],
            best.exists(), report.get("search", {}))
        if checkpoint_error:
            raise ValueError(checkpoint_error)
        check = Runner(20, folder / "best-check")
        check.folder.mkdir(exist_ok=True)
        best_obj = folder / "best.o"
        check.run([str(compile_script), str(best), "-o", str(best_obj)])
        report["verification"] = link_compare(best_obj, args.function, candidate.address, expected,
                                               folder / "best-check", flags, symbols, aliases)
        report["best_source"] = str(best)
        report["status"] = report["verification"]["status"]
        return report
    except (OSError, ValueError, RuntimeError, subprocess.SubprocessError, SystemExit) as error:
        report.update(status="error", error=str(error)[-1200:])
        return report
    finally:
        if checkpoint_dir is not None:
            checkpoint_best_source(folder, checkpoint_dir)
        (folder / "result.json").write_text(json.dumps(report, indent=2) + "\n")
        if checkpoint_dir is not None:
            checkpoint_dir.mkdir(parents=True, exist_ok=True)
            shutil.copy2(folder / "result.json", checkpoint_dir / "result.json")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("source")
    parser.add_argument("--engine", choices=["transmuter", "permuter"], required=True)
    parser.add_argument("--seconds", type=int, default=60)
    parser.add_argument("--jobs", type=int, default=8)
    parser.add_argument("--max-compiles", type=int, default=10000, help="Transmuter compile limit")
    parser.add_argument("--seed", type=int, default=1)
    parser.add_argument("--prepare-only", action="store_true", help="validate input and target without searching")
    parser.add_argument("--symbols-elf", help="optional exact accepted ELF snapshot for renamed symbol aliases")
    parser.add_argument("--tools", default=os.environ.get("MLSS_MUTATION_TOOLS", str(Path.home() / ".cache/mlss-mutation")))
    parser.add_argument("--work-root", default=str(ROOT / "scratch/mutations"))
    parser.add_argument(
        "--checkpoint-dir",
        help="durable directory for current best source and result when work-root is volatile",
    )
    args = parser.parse_args()
    if args.seconds < 1 or not 1 <= args.jobs <= 32 or args.max_compiles < 1:
        parser.error("positive budgets and 1..32 jobs required")
    result = run_search(args)
    print(json.dumps(result, indent=2))
    return 1 if result["status"] == "error" else 0


if __name__ == "__main__":
    raise SystemExit(main())
