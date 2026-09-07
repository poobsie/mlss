#!/usr/bin/env python3
"""Print a compact campaign checkpoint, including an independent process-lock check."""
import argparse
from collections import Counter
import fcntl
import json
from pathlib import Path
from decomp_campaign_monitor import estimate


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    args = parser.parse_args()
    state = json.loads((args.directory/'state.json').read_text())
    with (args.directory/'lock').open('a') as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
            alive = False
        except BlockingIOError:
            alive = True
    results = list(state['runs'].values())
    print(json.dumps({'status': state['status'], 'worker_running': alive,
                      'completed_searches': len(results),
                      'outcomes': dict(Counter(r['status'] for r in results)),
                      'draft_variants': state['draft_variants'],
                      'estimate': estimate(state),
                      'matches_needing_review': state['matches'],
                      'last_result': {key: results[-1].get(key) for key in
                                      ('function', 'engine', 'status', 'seconds')} if results else None,
                      'checkpoint_mtime': (args.directory/'state.json').stat().st_mtime}, indent=2))


if __name__ == '__main__':
    main()
