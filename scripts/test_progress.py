#!/usr/bin/env python3

import unittest

from progress import classify_linked_symbols, parse_function_symbols


class ProgressTest(unittest.TestCase):
    def test_parses_only_defined_function_symbols(self):
        symbols = parse_function_symbols(
            "1: 08000001 4 FUNC GLOBAL DEFAULT 1 c_func\n"
            "2: 00000000 0 FUNC GLOBAL DEFAULT UND external\n"
            "3: 08000004 4 OBJECT GLOBAL DEFAULT 1 data\n"
        )
        self.assertEqual(symbols, {"c_func": 4})

    def test_classifies_from_defining_objects_not_source_markers(self):
        linked = {"converted": 4, "still_asm": 8}
        linked_c, linked_asm = classify_linked_symbols(
            linked, {"converted"}, {"still_asm"}
        )
        self.assertEqual(linked_c, {"converted"})
        self.assertEqual(linked_asm, {"still_asm"})

    def test_ignores_discarded_and_rejected_c_symbols(self):
        linked = {"accepted": 4, "rejected_bad": 4}
        linked_c, _ = classify_linked_symbols(
            linked, {"accepted", "discarded", "rejected_bad"}, set()
        )
        self.assertEqual(linked_c, {"accepted"})

    def test_rejects_ambiguous_object_ownership(self):
        with self.assertRaisesRegex(RuntimeError, "both C and assembly"):
            classify_linked_symbols({"duplicate": 4}, {"duplicate"}, {"duplicate"})


if __name__ == "__main__":
    unittest.main()
