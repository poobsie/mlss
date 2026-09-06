#!/usr/bin/env python3

import unittest
import tempfile
from pathlib import Path

from decomp_workflow import (
    ROOT,
    SWI,
    candidate_by_name,
    discover,
    family_candidates,
    git_tracked_assembly,
    parse_rejections,
    render_packet,
    token_count,
)


class DecompWorkflowTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.candidates = discover(ROOT / "mlss.map", git_tracked_assembly())
        cls.candidate = min(cls.candidates, key=lambda item: (item.score, item.size))

    def test_scanner_returns_real_non_swi_candidate(self):
        candidate, block = candidate_by_name(self.candidate.name, ROOT / "mlss.map")
        self.assertGreater(candidate.size, 0)
        self.assertFalse(SWI.search(block))

    def test_packet_contains_exact_rom_bytes(self):
        candidate, _ = candidate_by_name(self.candidate.name, ROOT / "mlss.map")
        packet = render_packet(candidate.name, "mlss.map", "mlss.gba", False)
        rom = (ROOT / "mlss.gba").read_bytes()
        offset = candidate.address - 0x08000000
        expected = rom[offset : offset + candidate.size].hex(" ")
        self.assertIn(f"Target bytes: `{expected}`", packet)

    def test_packet_requires_decomp_time_detangling(self):
        packet = render_packet(self.candidate.name, "mlss.map", "mlss.gba", False)
        self.assertIn("Matching and detangling use one progressive pipeline", packet)
        self.assertIn("Assembly callers:", packet)
        self.assertIn("Adjacent functions:", packet)
        self.assertIn("subsystem, evidence, semantic_names, retained_unknowns", packet)
        self.assertNotIn("Write clean C for this function only", packet)

    def test_packet_is_smaller_than_local_context(self):
        candidate, _ = candidate_by_name(self.candidate.name, ROOT / "mlss.map")
        packet = render_packet(candidate.name, "mlss.map", "mlss.gba", False)
        lines = (ROOT / candidate.source).read_text(encoding="utf-8").splitlines(True)
        start = max(0, candidate.start_line - 101)
        window = "".join(lines[start : start + 200])
        packet_tokens = token_count(packet, "o200k_base")
        window_tokens = token_count(window, "o200k_base")
        self.assertLess(packet_tokens, window_tokens * 0.2)

    def test_boundaries_use_unfiltered_symbols_and_include_last_function(self):
        with tempfile.TemporaryDirectory(dir=ROOT) as directory:
            folder = Path(directory)
            assembly = folder / "boundaries.s"
            assembly.write_text(
                """\tthumb_func_start first\nfirst:\n\tmov r0, r0\n\tthumb_func_end first\n\tthumb_func_start rejected\nrejected:\n\tswi 0\n\tthumb_func_end rejected\n\tthumb_func_start last\nlast:\n\tmov r1, r1\n\tthumb_func_end last\n""",
                encoding="utf-8",
            )
            map_file = folder / "boundaries.map"
            map_file.write_text(
                "0x08000000 first\n0x08000008 rejected\n0x08000010 last\n0x08000018 file_end\n",
                encoding="utf-8",
            )
            candidates = discover(map_file, [assembly])
            by_name = {item.name: item for item in candidates}
            self.assertEqual(by_name["first"].size, 8)
            self.assertEqual(by_name["last"].size, 8)
            self.assertNotIn("rejected", by_name)

    def test_family_selection_is_contiguous_and_bounded(self):
        family = family_candidates(self.candidates, self.candidate.name, 10)
        self.assertLessEqual(len(family), 10)
        self.assertIn(self.candidate.name, [item.name for item in family])
        self.assertTrue(all(item.source == self.candidate.source for item in family))

    def test_rejection_ledger_accepts_symbols_and_addresses(self):
        names, addresses = parse_rejections(
            {
                "entries": [
                    {"symbol": "sub_8000000", "status": "exhausted"},
                    {"address": "0x08000010", "status": "exhausted"},
                    {"symbol": "sub_8000020", "status": "active"},
                ]
            }
        )
        self.assertEqual(names, {"sub_8000000"})
        self.assertEqual(addresses, {0x08000010})


if __name__ == "__main__":
    unittest.main()
