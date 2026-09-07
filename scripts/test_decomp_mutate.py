#!/usr/bin/env python3
import os
from pathlib import Path
import sys
import shutil
import subprocess
import tempfile
import unittest

from decomp_mutate import bounded_process, compiler_script
from decomp_local import Runner, build_flags
from decomp_workflow import is_register_trampoline


class MutationSafetyTest(unittest.TestCase):
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
