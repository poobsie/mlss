#!/usr/bin/env python3

import unittest
from pathlib import Path

from detangling_status import ROOT, acceptance_errors


class DetanglingAcceptanceTest(unittest.TestCase):
    def test_accepts_detangled_and_actionable_deferred_subsystems(self):
        subsystems = [
            {"id": "known", "state": "detangled", "next_action": ""},
            {"id": "blocked", "state": "deferred", "next_action": "Trace runtime owner"},
            {"id": "unclassified", "state": "detangled", "next_action": ""},
        ]
        assignments = {item["id"]: [] for item in subsystems}
        self.assertEqual(acceptance_errors(subsystems, assignments), [])

    def test_rejects_work_queue_and_unclassified_source(self):
        subsystems = [
            {"id": "known", "state": "active", "next_action": "Finish it"},
            {"id": "unclassified", "state": "detangled", "next_action": ""},
        ]
        assignments = {
            "known": [],
            "unclassified": [ROOT / Path("src/unknown.c")],
        }
        errors = acceptance_errors(subsystems, assignments)
        self.assertIn("known is still active", errors)
        self.assertTrue(any("unclassified source remains" in error for error in errors))

    def test_rejects_deferred_subsystem_without_evidence_action(self):
        subsystems = [{"id": "blocked", "state": "deferred", "next_action": ""}]
        self.assertEqual(
            acceptance_errors(subsystems, {"blocked": []}),
            ["blocked is deferred without a concrete next action"],
        )


if __name__ == "__main__":
    unittest.main()
