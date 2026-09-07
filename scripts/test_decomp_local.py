#!/usr/bin/env python3
"""Safety checks for scratch matching and context preparation."""

import subprocess
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

from decomp_local import ROOT, Runner, build_flags, compile_candidate, compare_span, make_context


class LocalMatchingTest(unittest.TestCase):
    def test_equal_prefix_is_not_a_match(self):
        for actual, expected in [(b"abc", b"abcd"), (b"abcd", b"abc")]:
            result = compare_span(actual, expected)
            self.assertEqual(result["status"], "mismatch")
            self.assertEqual(result["first_mismatch"], 3)

    def test_same_size_different_bytes_is_not_a_match(self):
        self.assertEqual(compare_span(b"abc", b"adc")["first_mismatch"], 1)
        self.assertEqual(compare_span(b"abc", b"abc")["status"], "span_match")

    def test_failed_command_is_not_success(self):
        with tempfile.TemporaryDirectory() as directory:
            runner = Runner(5, Path(directory))
            with self.assertRaises(RuntimeError):
                runner.run([sys.executable, "-c", "raise SystemExit(2)"])
            self.assertTrue((Path(directory) / "command-1.log").exists())

    def test_command_has_a_real_deadline(self):
        with tempfile.TemporaryDirectory() as directory:
            runner = Runner(0.1, Path(directory))
            with self.assertRaises(subprocess.TimeoutExpired):
                runner.run([sys.executable, "-c", "import time; time.sleep(10)"])

    def test_context_rejects_files_outside_headers(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaises(ValueError):
                make_context(["Makefile"], Path(directory) / "context.c", None, {})

    @unittest.skipUnless(shutil.which("arm-none-eabi-as"), "requires project ARM toolchain")
    def test_real_compiler_match_and_missing_target(self):
        scratch = ROOT / "scratch"
        scratch.mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=scratch) as directory:
            folder = Path(directory)
            source = folder / "fixture.c"
            source.write_text("void local_match_fixture(void) {}\n")
            runner = Runner(20, folder)
            flags = build_flags(runner)
            result = compile_candidate(source, "local_match_fixture", 0x08000000,
                                       b"\x70\x47\x00\x00", folder, runner, flags, {})
            self.assertEqual(result["status"], "span_match")
            with self.assertRaisesRegex(ValueError, "source must define"):
                compile_candidate(source, "missing_target", 0x08000000,
                                  b"\x70\x47\x00\x00", folder, runner, flags,
                                  {"missing_target": 0x08000001})

    @unittest.skipUnless(shutil.which("arm-none-eabi-as"), "requires project ARM toolchain")
    def test_reference_thumb_call_does_not_gain_an_interworking_veneer(self):
        with tempfile.TemporaryDirectory(dir=ROOT / "scratch") as directory:
            folder = Path(directory)
            source = folder / "fixture.c"
            source.write_text("extern void sub_80871A8(void);\n"
                              "void local_call_fixture(void) { sub_80871A8(); }\n")
            runner = Runner(20, folder)
            compile_candidate(source, "local_call_fixture", 0x08000000, b"\0" * 12,
                              folder, runner, build_flags(runner), {})
            assembly = (folder / "disassembly.txt").read_text()
            self.assertNotIn("_from_thumb", assembly)
            self.assertRegex(assembly, r"bl\s+80871a8\s+<sub_80871A8>")


if __name__ == "__main__":
    unittest.main()
