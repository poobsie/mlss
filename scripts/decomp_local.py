#!/usr/bin/env python3
"""Bounded scratch compilation and reference-span comparison (run under Unix/WSL)."""

import argparse
import hashlib
import json
import re
import shlex
import subprocess
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


class Runner:
    def __init__(self, seconds, folder):
        self.deadline = time.monotonic() + seconds
        self.folder = folder
        self.calls = 0

    def run(self, command, input=None):
        remaining = self.deadline - time.monotonic()
        if remaining <= 0:
            raise TimeoutError("local matching time budget exhausted")
        self.calls += 1
        result = subprocess.run(command, cwd=ROOT, input=input, text=True,
                                capture_output=True, timeout=remaining)
        (self.folder / f"command-{self.calls}.log").write_text(
            shlex.join(map(str, command)) + "\n" + result.stdout + result.stderr)
        if result.returncode:
            raise RuntimeError(f"command failed; see command-{self.calls}.log: "
                               + (result.stderr or result.stdout)[-600:])
        return result.stdout


def build_flags(runner):
    names = ["CPP", "CPPFLAGS", "CC1", "CFLAGS", "AS", "ASFLAGS", "LD", "OBJCOPY"]
    recipe = ".PHONY: decomp-local-flags\ndecomp-local-flags:\n" + "".join(
        f"\t@printf '%s\\n' '$({name})'\n" for name in names)
    values = runner.run(["make", "--no-print-directory", "-s", "-f", "Makefile",
                         "-f", "-", "decomp-local-flags"], recipe).splitlines()
    if len(values) != len(names):
        raise RuntimeError("unexpected Makefile flag output")
    return dict(zip(names, map(shlex.split, values)))


def make_context(headers, output, runner, flags):
    """Preprocess only explicitly selected headers, retaining their dependency closure."""
    includes = []
    for header in headers:
        path = (ROOT / header).resolve()
        path.relative_to(ROOT / "include")
        if not path.is_file():
            raise ValueError(f"missing header: {header}")
        includes.append('#include "' + path.relative_to(ROOT / "include").as_posix() + '"')
    content = runner.run(flags["CPP"] + flags["CPPFLAGS"] +
                         ["-P", "-x", "c", "-"], "\n".join(includes) + "\n")
    if not output.exists() or output.read_text() != content:
        output.write_text(content)
    return output


def reference_symbols(runner, elf):
    output = runner.run(["arm-none-eabi-readelf", "-sW", str(elf)])
    found = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) == 8 and fields[4] in {"GLOBAL", "WEAK"} and fields[6] != "UND":
            name = fields[7]
            if re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", name):
                found[name] = int(fields[1], 16)
    return found


def compare_span(actual, expected):
    mismatch = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b), None)
    if mismatch is None and len(actual) != len(expected):
        mismatch = min(len(actual), len(expected))
    return {"status": "span_match" if actual == expected else "mismatch",
            "actual_bytes": len(actual), "expected_bytes": len(expected),
            "first_mismatch": mismatch}


def mismatch_excerpt(disassembly, address):
    lines = [line.strip() for line in disassembly.splitlines()
             if re.match(r"\s*[0-9a-f]+:", line)]
    index = next((i for i, line in enumerate(lines)
                  if int(line.split(":", 1)[0], 16) >= address), max(0, len(lines) - 1))
    return lines[max(0, index - 2):index + 3]


def compile_candidate(source, symbol, address, expected, folder, runner, flags, symbols):
    preprocessed, assembly, obj, elf, binary = [folder / ("candidate" + ext)
                                               for ext in [".i", ".s", ".o", ".elf", ".bin"]]
    runner.run(flags["CPP"] + flags["CPPFLAGS"] + [str(source), "-o", str(preprocessed)])
    runner.run(flags["CC1"] + [str(preprocessed)] + flags["CFLAGS"] + ["-o", str(assembly)])
    with assembly.open("a") as stream:
        stream.write("\n.text\n.align 2, 0\n")
    runner.run(flags["AS"] + flags["ASFLAGS"] + ["-o", str(obj), str(assembly)])
    defined = reference_symbols(runner, obj)
    if symbol not in defined or defined[symbol] & ~1 != 0:
        raise ValueError("source must define the target as its first emitted function")
    script = folder / "candidate.ld"
    script.write_text("\n".join(f"PROVIDE({name} = 0x{value:X});" for name, value in symbols.items())
                      + f"\nSECTIONS {{ .text 0x{address:X} : {{ *(.text*) }} "
                      + ".rodata : { *(.rodata*) } .data : { *(.data*) } .bss : { *(.bss*) } }\n")
    runner.run(flags["LD"] + ["-T", str(script), "-o", str(elf), str(obj)])
    linked = reference_symbols(runner, elf)
    if symbol not in linked or linked[symbol] & ~1 != address:
        raise ValueError("target must be the first emitted function at its reference address")
    runner.run(flags["OBJCOPY"] + ["-O", "binary", "--only-section=.text", str(elf), str(binary)])
    result = compare_span(binary.read_bytes(), expected)
    disassembly = runner.run(["arm-none-eabi-objdump", "-dr", str(elf)])
    (folder / "disassembly.txt").write_text(disassembly)
    if result["status"] == "mismatch":
        target = folder / "target.bin"
        target.write_bytes(expected)
        target_disassembly = runner.run(["arm-none-eabi-objdump", "-D", "-b", "binary", "-m", "arm",
                                         "-M", "force-thumb", f"--adjust-vma={address}", str(target)])
        (folder / "target-disassembly.txt").write_text(target_disassembly)
        position = address + result["first_mismatch"]
        result["actual_excerpt"] = mismatch_excerpt(disassembly, position)
        result["target_excerpt"] = mismatch_excerpt(target_disassembly, position)
    result.update(source=str(source.relative_to(ROOT)), artifacts=str(folder.relative_to(ROOT)))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("sources", nargs="*", help="standalone C variants; otherwise generate m2c variants")
    parser.add_argument("--header", action="append", default=[], help="relevant include/... header; repeatable")
    parser.add_argument("--seconds", type=int, default=60)
    parser.add_argument("--max-variants", type=int, default=3)
    args = parser.parse_args()
    if args.seconds <= 0 or not 1 <= args.max_variants <= 16:
        parser.error("seconds must be positive and max-variants must be 1..16")
    scratch = ROOT / "scratch" / "matching"
    scratch.mkdir(parents=True, exist_ok=True)
    folder = Path(tempfile.mkdtemp(prefix="candidate-", dir=scratch))
    runner = Runner(args.seconds, folder)
    results = []
    try:
        from decomp_workflow import candidate_by_name, inferred_headers, m2c_draft
        candidate, block = candidate_by_name(args.function, ROOT / "mlss.map")
        if candidate.mode != "thumb":
            raise ValueError("local runner supports Thumb candidates with the normal project compiler flags")
        reference = ROOT / ".decomp-tools/reference/mlss.gba"
        rom = reference.read_bytes()
        offset = candidate.address - 0x08000000
        if offset < 0 or offset + candidate.size > len(rom):
            raise ValueError("candidate span outside reference ROM")
        expected = rom[offset:offset + candidate.size]
        (folder / "target.bin").write_bytes(expected)
        flags = build_flags(runner)
        context = make_context(args.header or inferred_headers(args.function, block),
                               folder / "context.c", runner, flags)
        symbols = reference_symbols(runner, ROOT / ".decomp-tools/reference/mlss.elf")
        sources = [(ROOT / name).resolve() for name in args.sources[:args.max_variants]]
        options = [[], ["--no-switches"], ["--gotos-only"]]
        seen = set()
        count = len(sources) if args.sources else min(args.max_variants, len(options))
        for index in range(count):
            variant = folder / f"variant-{index}"
            variant.mkdir()
            try:
                if args.sources:
                    source = sources[index]
                else:
                    draft = m2c_draft(candidate, block, [context], options[index],
                                      max(0.01, runner.deadline - time.monotonic()))
                    source = variant / "draft.c"
                    source.write_text(context.read_text() + "\n" + draft)
                    if draft.startswith("(m2c"):
                        raise RuntimeError(draft[:600])
                    if re.search(r"^Warning:", draft, re.MULTILINE):
                        results.append({"status": "decompiler_warning", "source": str(source.relative_to(ROOT)),
                                        "detail": "Inspect retained m2c warning before compiling alternative drafts."})
                        break
                    if re.search(r"\bM2C_UNK\w*\b", draft):
                        results.append({"status": "types_required", "source": str(source.relative_to(ROOT)),
                                        "detail": "Supply recovered signatures/types through --header; draft retained."})
                        break
                digest = hashlib.sha256(source.read_bytes()).hexdigest()
                if digest in seen:
                    continue
                seen.add(digest)
                result = compile_candidate(source, args.function, candidate.address, expected,
                                           variant, runner, flags, symbols)
            except (RuntimeError, ValueError) as error:
                result = {"status": "error", "detail": str(error)}
            results.append(result)
            if result["status"] == "span_match":
                break
    except (OSError, ValueError, RuntimeError, TimeoutError, subprocess.TimeoutExpired) as error:
        results.append({"status": "error", "detail": str(error)[:700]})
    report = {"function": args.function, "results": results,
              "artifacts": str(folder.relative_to(ROOT)), "acceptance_required": True}
    (folder / "result.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
    return 0 if any(item["status"] == "span_match" for item in results) else 1


if __name__ == "__main__":
    raise SystemExit(main())
