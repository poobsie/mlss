#!/usr/bin/env python3
from __future__ import annotations

import unittest

from decomp_telemetry import rate


class DecompTelemetryTest(unittest.TestCase):
    def test_rate_reports_time_and_usage_efficiency(self):
        first = {
            "timestamp": "2026-09-06T16:00:00Z",
            "functions": 100,
            "matched_text_bytes": 1000,
            "usage_used_percent": 10,
            "usage_resets_at": 123,
        }
        last = {
            "timestamp": "2026-09-06T18:00:00Z",
            "functions": 120,
            "matched_text_bytes": 1800,
            "usage_used_percent": 15,
            "usage_resets_at": 123,
        }
        measured = rate(first, last)
        self.assertIsNotNone(measured)
        self.assertEqual(measured["functions_per_hour"], 10)
        self.assertEqual(measured["bytes_per_hour"], 400)
        self.assertEqual(measured["functions_per_usage_percent"], 4)

    def test_rate_ignores_usage_across_windows(self):
        first = {
            "timestamp": "2026-09-06T16:00:00Z",
            "functions": 100,
            "matched_text_bytes": 1000,
            "usage_used_percent": 90,
            "usage_resets_at": 123,
        }
        last = {
            "timestamp": "2026-09-06T17:00:00Z",
            "functions": 110,
            "matched_text_bytes": 1200,
            "usage_used_percent": 2,
            "usage_resets_at": 456,
        }
        measured = rate(first, last)
        self.assertNotIn("functions_per_usage_percent", measured)


if __name__ == "__main__":
    unittest.main()
