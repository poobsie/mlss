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
from decomp_workflow import candidate_by_name


def bounded_process(command, seconds, log, cwd):
    """Kill the complete search process group, including compiler children, on expiry."""
    start = time.monotonic()
    with log.open("w") as stream:
        process = subprocess.Popen(command, cwd=cwd, stdout=stream, stderr=subprocess.STDOUT,
                                   start_new_session=True)
        timed_out = False
        try:
            process.wait(timeout=seconds)
        except subprocess.TimeoutExpired:
            timed_out = True
        finally:
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


def link_compare(obj, symbol, address, expected, folder, flags, symbols):
    folder.mkdir(exist_ok=True)
    runner = Runner(20, folder)
    defined = reference_symbols(runner, obj)
    if symbol not in defined or defined[symbol] & ~1:
        raise ValueError("candidate must define the target first in its text section")
    linker = folder / "verify.ld"
    linker.write_text(f"SECTIONS {{ .text 0x{address:X} : {{ *(.text*) }} "
                      + ".rodata : { *(.rodata*) } .data : { *(.data*) } .bss : { *(.bss*) } }\n")
    elf, binary = folder / "verify.elf", folder / "verify.bin"
    runner.run(flags["LD"] + ["--just-symbols=" + str(ROOT / ".decomp-tools/reference/mlss.elf"),
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
    report = {"function": args.function, "engine": args.engine, "source_sha256":
              hashlib.sha256(source.read_bytes()).hexdigest(), "seconds": args.seconds,
              "jobs": args.jobs, "seed": args.seed if args.engine == "transmuter" else None, "artifacts": str(folder),
              "acceptance_required": True}
    try:
        candidate, block = candidate_by_name(args.function, ROOT / "mlss.map")
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
        target_asm.write_text('.include "asm/macros.inc"\n.syntax unified\n.text\n' + block
                              + f"\n.text\n.size {args.function}, .-{args.function}\n")
        runner.run(flags["AS"] + flags["ASFLAGS"] + ["-o", str(target_obj), str(target_asm)])
        target_check = link_compare(target_obj, args.function, candidate.address, expected,
                                    folder / "target-check", flags, symbols)
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
                                           folder / "baseline-check", flags, symbols)
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
            report["process"] = bounded_process(command, args.seconds + 5, folder / "engine.log", ROOT)
            if (folder / "engine.json").exists():
                report["search"] = json.loads((folder / "engine.json").read_text())
        else:
            (folder / "settings.toml").write_text(f'func_name = "{args.function}"\ncompiler_type = "gcc"\n')
            command = [str(tool_root / "venv/bin/python"), "-u",
                       str(tool_root / "decomp-permuter/permuter.py"), str(folder),
                       "-j", str(args.jobs), "--stop-on-zero", "--best-only", "--quiet"]
            report["process"] = bounded_process(command, args.seconds, folder / "engine.log", ROOT)
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
        if not best.exists() or report.get("search", {}).get("baseScore") is None:
            raise ValueError("search failed to initialize; see engine.log")
        check = Runner(20, folder / "best-check")
        check.folder.mkdir(exist_ok=True)
        best_obj = folder / "best.o"
        check.run([str(compile_script), str(best), "-o", str(best_obj)])
        report["verification"] = link_compare(best_obj, args.function, candidate.address, expected,
                                               folder / "best-check", flags, symbols)
        report["best_source"] = str(best)
        report["status"] = report["verification"]["status"]
        return report
    except (OSError, ValueError, RuntimeError, subprocess.SubprocessError, SystemExit) as error:
        report.update(status="error", error=str(error)[-1200:])
        return report
    finally:
        (folder / "result.json").write_text(json.dumps(report, indent=2) + "\n")


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
    parser.add_argument("--tools", default=os.environ.get("MLSS_MUTATION_TOOLS", str(Path.home() / ".cache/mlss-mutation")))
    parser.add_argument("--work-root", default=str(ROOT / "scratch/mutations"))
    args = parser.parse_args()
    if args.seconds < 1 or not 1 <= args.jobs <= 32 or args.max_compiles < 1:
        parser.error("positive budgets and 1..32 jobs required")
    result = run_search(args)
    print(json.dumps(result, indent=2))
    return 1 if result["status"] == "error" else 0


if __name__ == "__main__":
    raise SystemExit(main())
