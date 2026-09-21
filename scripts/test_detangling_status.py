#!/usr/bin/env python3

import json
import tempfile
import unittest
from pathlib import Path

from detangling_status import (
    ROOT,
    acceptance_errors,
    detangling_report,
    linked_c_functions_from_map,
)


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


class DetanglingMetricsTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        (self.root / "src" / "runtime").mkdir(parents=True)
        (self.root / "include" / "runtime").mkdir(parents=True)

    def tearDown(self):
        self.temporary.cleanup()

    def write_map(self, entries):
        lines = []
        address = 0x08001000
        for symbol, size, source in entries:
            obj = source.removesuffix(".c") + ".o"
            lines.extend(
                [
                    f" {obj}(.text.fixture.{symbol})",
                    f" .text.fixture.{symbol}",
                    f"                0x{address:08x}       0x{size:x} {obj}",
                    f"                0x{address:08x}                {symbol}",
                ]
            )
            address += max(size, 2)
        path = self.root / "mlss.map"
        path.write_text("\n".join(lines) + "\n", encoding="utf-8")
        return path

    @staticmethod
    def subsystems(*patterns):
        return [
            {
                "id": f"group{index}",
                "state": "detangled",
                "patterns": [pattern],
                "documentation": "",
                "next_action": "",
            }
            for index, pattern in enumerate(patterns)
        ] + [
            {
                "id": "unclassified",
                "state": "detangled",
                "patterns": ["src/**/*.c"],
                "documentation": "",
                "next_action": "",
            }
        ]

    def test_semantic_requires_public_prototype_and_owning_definition(self):
        source = self.root / "src" / "runtime" / "sample.c"
        source.write_text(
            "#include \"runtime/sample.h\"\n"
            "void useful_name(void) {}\n"
            "void sub_8001004(void) {}\n",
            encoding="utf-8",
        )
        (self.root / "include" / "runtime" / "sample.h").write_text(
            "#define useful_name sub_8001000\n"
            "void useful_name(void);\n"
            "#define invented_name sub_8001004\n"
            "void invented_name(void);\n",
            encoding="utf-8",
        )
        map_path = self.write_map(
            [
                ("sub_8001000", 4, "src/runtime/sample.c"),
                ("sub_8001004", 4, "src/runtime/sample.c"),
            ]
        )
        report = detangling_report(
            self.root, map_path, self.subsystems("src/runtime/*.c")
        )
        self.assertEqual(report.semantic, {"sub_8001000"})
        self.assertIn("sub_8001004", report.address_only)
        self.assertIn("sub_8001004", report.alias_unverified)

    def test_duplicate_alias_cannot_inflate_semantic_count(self):
        source = self.root / "src" / "runtime" / "sample.c"
        source.write_text(
            "void first_name(void) {}\nvoid second_name(void) {}\n",
            encoding="utf-8",
        )
        (self.root / "include" / "runtime" / "sample.h").write_text(
            "#define first_name sub_8001000\nvoid first_name(void);\n"
            "#define second_name sub_8001000\nvoid second_name(void);\n",
            encoding="utf-8",
        )
        report = detangling_report(
            self.root,
            self.write_map([("sub_8001000", 4, "src/runtime/sample.c")]),
            self.subsystems("src/runtime/*.c"),
        )
        self.assertFalse(report.semantic)
        self.assertEqual(report.alias_conflict, {"sub_8001000"})

    def test_debt_is_boolean_per_function_and_ignores_comments_strings_and_mmio(self):
        source = self.root / "src" / "runtime" / "sample.c"
        source.write_text(
            "struct Obj { int unknown10; };\n"
            "void neutral(struct Obj *obj) { obj->unknown10++; obj->unknown10++; }\n"
            "void raw(void *obj) { U16AT(obj, 4) = 0; U16AT(obj, 4) = 1; }\n"
            "void clean(void) { const char *s = \"obj->unknown10 U8AT(x, 2)\"; "
            "/* obj->field_20 */ *(unsigned short*)0x04000000 = 0; (void)s; }\n",
            encoding="utf-8",
        )
        header = self.root / "include" / "runtime" / "sample.h"
        header.write_text(
            "void neutral(struct Obj*);\nvoid raw(void*);\nvoid clean(void);\n",
            encoding="utf-8",
        )
        report = detangling_report(
            self.root,
            self.write_map(
                [
                    ("neutral", 4, "src/runtime/sample.c"),
                    ("raw", 4, "src/runtime/sample.c"),
                    ("clean", 4, "src/runtime/sample.c"),
                ]
            ),
            self.subsystems("src/runtime/*.c"),
        )
        self.assertEqual(report.neutral_member, {"neutral"})
        self.assertEqual(report.raw_object_offset, {"raw"})
        self.assertNotIn("clean", report.neutral_member | report.raw_object_offset)

    def test_unscanned_body_is_not_structured(self):
        source = self.root / "src" / "runtime" / "sample.c"
        source.write_text(
            "#define DEFINE(name) void name(void) {}\nDEFINE(generated)\n",
            encoding="utf-8",
        )
        (self.root / "include" / "runtime" / "sample.h").write_text(
            "void generated(void);\n", encoding="utf-8"
        )
        report = detangling_report(
            self.root,
            self.write_map([("generated", 4, "src/runtime/sample.c")]),
            self.subsystems("src/runtime/*.c"),
        )
        self.assertEqual(report.unscanned, {"generated"})
        self.assertFalse(report.strict)

    def test_placement_reports_zero_one_and_multiple_matches_independent_of_order(self):
        source = self.root / "src" / "runtime" / "sample.c"
        source.write_text("void placed(void) {}\n", encoding="utf-8")
        (self.root / "include" / "runtime" / "sample.h").write_text(
            "void placed(void);\n", encoding="utf-8"
        )
        map_path = self.write_map([("placed", 4, "src/runtime/sample.c")])
        one = detangling_report(self.root, map_path, self.subsystems("src/runtime/*.c"))
        zero = detangling_report(self.root, map_path, self.subsystems("src/audio/*.c"))
        multiple_a = detangling_report(
            self.root, map_path,
            self.subsystems("src/runtime/*.c", "src/**/*.c"),
        )
        multiple_b = detangling_report(
            self.root, map_path,
            list(reversed(self.subsystems("src/runtime/*.c", "src/**/*.c"))),
        )
        self.assertEqual(one.placed, {"placed"})
        self.assertEqual(zero.unplaced, {"placed"})
        self.assertEqual(multiple_a.ambiguous, {"placed"})
        self.assertEqual(multiple_a.ambiguous, multiple_b.ambiguous)

    def test_map_inventory_excludes_zero_padding_and_drafts(self):
        entries = [
            ("kept", 4, "src/runtime/sample.c"),
            ("zero", 0, "src/runtime/sample.c"),
            ("kept_padding", 2, "src/runtime/sample.c"),
            ("draft_shape", 2, "src/runtime/sample.c"),
            ("rejected_shape", 2, "src/runtime/sample.c"),
        ]
        inventory = linked_c_functions_from_map(self.write_map(entries))
        self.assertEqual([item.name for item in inventory], ["kept"])

    def test_map_inventory_keeps_every_function_in_aggregate_text_section(self):
        map_path = self.root / "mlss.map"
        map_path.write_text(
            " src/runtime/sample.o(.text)\n"
            " .text          0x08001000       0x10 src/runtime/sample.o\n"
            "                0x08001000                first\n"
            "                0x08001004                second\n"
            "                0x0800100c                second_padding\n"
            " asm/next.o(.text)\n",
            encoding="utf-8",
        )
        inventory = linked_c_functions_from_map(map_path)
        self.assertEqual(
            [(item.name, item.size) for item in inventory],
            [("first", 4), ("second", 8)],
        )

    def test_json_lists_are_sorted_and_occurrence_count_does_not_affect_counts(self):
        source = self.root / "src" / "runtime" / "sample.c"
        source.write_text(
            "struct Obj { int value10; };\n"
            "void beta(struct Obj *o) { o->value10++; o->value10++; }\n"
            "void alpha(void) {}\n",
            encoding="utf-8",
        )
        (self.root / "include" / "runtime" / "sample.h").write_text(
            "void beta(struct Obj*);\nvoid alpha(void);\n", encoding="utf-8"
        )
        report = detangling_report(
            self.root,
            self.write_map(
                [("beta", 4, "src/runtime/sample.c"), ("alpha", 4, "src/runtime/sample.c")]
            ),
            self.subsystems("src/runtime/*.c"),
        )
        payload = report.as_dict()
        self.assertEqual(payload["counts"]["neutral_member"], 1)
        self.assertEqual(payload["symbols"]["semantic"], ["alpha", "beta"])
        self.assertEqual(json.loads(json.dumps(payload, sort_keys=True)), payload)


if __name__ == "__main__":
    unittest.main()
