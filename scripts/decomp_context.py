#!/usr/bin/env python3
"""Build reusable preprocessed m2c context from a narrow set of project headers."""

import argparse
import hashlib
import json
from pathlib import Path

from decomp_local import ROOT, Runner, build_flags, make_context


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("headers", nargs="+", help="include/... paths")
    args = parser.parse_args()
    headers = sorted(set(args.headers))
    key = hashlib.sha256(json.dumps(headers).encode()).hexdigest()[:16]
    folder = ROOT / "scratch" / "contexts" / key
    folder.mkdir(parents=True, exist_ok=True)
    # The path is stable for m2c's parse cache; preprocessing refreshes header changes.
    runner = Runner(30, folder)
    output = make_context(headers, folder / "context.c", runner, build_flags(runner))
    print(output.relative_to(ROOT).as_posix())


if __name__ == "__main__":
    main()
