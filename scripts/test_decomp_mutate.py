#!/usr/bin/env python3
import os
from pathlib import Path
import sys
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from decomp_mutate import (
    TRANSMUTER_FINALIZATION_GRACE_SECONDS,
    bounded_process,
    checkpoint_best_source,
    compiler_script,
    run_transmuter_process,
    search_checkpoint_error,
    target_assembly,
)
from decomp_local import Runner, build_flags
from decomp_workflow import Candidate, is_register_trampoline


class MutationSafetyTest(unittest.TestCase):
    def test_target_assembly_excludes_later_section_and_asserts_mapped_size(self):
        candidate = Candidate(
            name="fixture", mode="thumb", source="fixture.s",
            start_line=1, end_line=12, address=0x08000000, size=24,
            calls=0, branches=0, raw_bytes=2, repeated_shape=1, score=24,
        )
        block = (
            "\tthumb_func_start fixture\nfixture:\n\t.byte 0x00, 0x00\n"
            "\t.section .text.after_c_owned, \"ax\", %progbits\n"
            "\t.if 0\n\tthumb_func_start c_owned\nc_owned:\n\tbx lr\n\t.endif\n"
            "\t.byte 0x01, 0x20, 0x70, 0x47\n"
        )

        source = target_assembly(candidate, block)

        self.assertNotIn("after_c_owned", source)
        self.assertNotIn("c_owned", source)
        self.assertIn(".if (. - fixture) != 24", source)
        self.assertIn(".size fixture, .-fixture", source)

    def test_best_source_checkpoint_prefers_lowest_score(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            first = root / 'work' / 'output-20'
            second = root / 'work' / 'output-5'
            first.mkdir(parents=True)
            second.mkdir(parents=True)
            (first / 'source.c').write_text('int value = 20;\n')
            (first / 'score.txt').write_text('20\n')
            (second / 'source.c').write_text('int value = 5;\n')
            (second / 'score.txt').write_text('5\n')
            checkpoint_best_source(root / 'work', root / 'durable')
            self.assertEqual((root / 'durable' / 'best.c').read_text(), 'int value = 5;\n')
            self.assertEqual((root / 'durable' / 'best-score.txt').read_text(), '5\n')

    def test_transmuter_allows_delayed_final_checkpoint_within_grace(self):
        command = ["mock-transmuter"]
        log = Path("engine.log")
        cwd = Path(".")
        completed = {"returncode": 0, "timed_out": False, "wall_seconds": 31}

        with patch("decomp_mutate.bounded_process", return_value=completed) as run:
            result = run_transmuter_process(command, 30, log, cwd)

        self.assertEqual(result, completed)
        run.assert_called_once_with(
            command, 30 + TRANSMUTER_FINALIZATION_GRACE_SECONDS, log, cwd,
            None)
        self.assertIsNone(search_checkpoint_error(
            "transmuter", {"timed_out": True}, 1409, True,
            {"baseScore": 13, "bestScore": 13}))

    def test_transmuter_timeout_after_launches_reports_missing_checkpoint(self):
        error = search_checkpoint_error(
            "transmuter", {"timed_out": True}, 7107, False, {})

        self.assertIn("timeout before final checkpoint", error)
        self.assertIn("7107 compiler launches", error)
        self.assertNotIn("failed to initialize", error)

    def test_missing_checkpoint_before_launches_remains_initialization_failure(self):
        error = search_checkpoint_error(
            "transmuter", {"timed_out": True}, 0, False, {})

        self.assertEqual(error, "search failed to initialize; see engine.log")

    @unittest.skipUnless(shutil.which('arm-none-eabi-as'), 'requires project ARM toolchain')
    def test_compile_wrapper_removes_temporary_assembly(self):
        with tempfile.TemporaryDirectory() as directory:
            folder = Path(directory)
            runner = Runner(10, folder)
            script = compiler_script(folder, build_flags(runner))
            source, output = folder/'base.c', folder/'base.o'
            source.write_text('int compile_fixture(void) { return 7; }\n')
            subprocess.run([str(script), str(source), '-o', str(output)], check=True, timeout=5)
            self.assertTrue(output.exists())
            self.assertFalse(Path(str(output)+'.s').exists())

    def test_normal_thumb_return_is_not_a_trampoline(self):
        self.assertFalse(is_register_trampoline('push {r4, lr}\npop {r4}\npop {r1}\nbx r1\n'))
        self.assertTrue(is_register_trampoline('thumb_func_start foo\nfoo:\nbx r0\n.byte 0, 0\n'))

    @unittest.skipUnless(os.name == 'posix', 'process groups require Unix')
    def test_timeout_stops_compiler_descendants(self):
        with tempfile.TemporaryDirectory() as directory:
            folder = Path(directory)
            code = ('import subprocess,sys,time; from pathlib import Path; '
                    'child=subprocess.Popen([sys.executable,"-c","import time; time.sleep(30)"]); '
                    'Path("child.pid").write_text(str(child.pid)); time.sleep(30)')
            result = bounded_process([sys.executable, '-c', code], 0.5, folder/'log', folder)
            self.assertTrue(result['timed_out'])
            pid = int((folder/'child.pid').read_text())
            status = Path(f'/proc/{pid}/status')
            if status.exists():
                self.assertIn('Z (zombie)', status.read_text())

    @unittest.skipUnless(os.name == 'posix', 'process groups require Unix')
    def test_failed_engine_is_reported(self):
        with tempfile.TemporaryDirectory() as directory:
            folder = Path(directory)
            result = bounded_process([sys.executable, '-c', 'raise SystemExit(3)'], 2, folder/'log', folder)
            self.assertEqual(result['returncode'], 3)
            self.assertFalse(result['timed_out'])


if __name__ == '__main__':
    unittest.main()
