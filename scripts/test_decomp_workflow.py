#!/usr/bin/env python3

import unittest

from decomp_workflow import (
    ROOT,
    SWI,
    candidate_by_name,
    discover,
    git_tracked_assembly,
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

    def test_packet_is_smaller_than_local_context(self):
        candidate, _ = candidate_by_name(self.candidate.name, ROOT / "mlss.map")
        packet = render_packet(candidate.name, "mlss.map", "mlss.gba", False)
        lines = (ROOT / candidate.source).read_text(encoding="utf-8").splitlines(True)
        start = max(0, candidate.start_line - 101)
        window = "".join(lines[start : start + 200])
        packet_tokens = token_count(packet, "o200k_base")
        window_tokens = token_count(window, "o200k_base")
        self.assertLess(packet_tokens, window_tokens * 0.2)


if __name__ == "__main__":
    unittest.main()
