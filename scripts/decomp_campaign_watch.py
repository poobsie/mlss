#!/usr/bin/env python3
"""Supervise an existing CPU campaign without model calls; restart once on failure."""
import argparse
import fcntl
import json
from pathlib import Path
import subprocess
import time

from decomp_campaign import save


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    root = args.directory.resolve()
    guard = (root/'supervisor.lock').open('a')
    fcntl.flock(guard, fcntl.LOCK_EX | fcntl.LOCK_NB)
    if not args.command:
        parser.error('supply the campaign resume command')
    restarts = 0
    child = None
    while True:
        state = json.loads((root/'state.json').read_text())
        with (root/'lock').open('a') as lock:
            try:
                fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
                alive = False
            except BlockingIOError:
                alive = True
        if child is not None:
            child.poll()
        status = 'watching'
        if not alive:
            if state['status'] in ('draft_queue_exhausted', 'paused') or (root/'STOP').exists():
                status = 'finished'
            elif restarts:
                status = 'failed'
            else:
                with (root/'resume.log').open('a') as log:
                    child = subprocess.Popen(args.command, stdout=log, stderr=subprocess.STDOUT,
                                             stdin=subprocess.DEVNULL, start_new_session=True)
                restarts += 1
                status = 'restarting'
        save(root/'supervisor.json', {'status': status, 'restarts': restarts,
                                     'checked_at': time.time()})
        if status in ('finished', 'failed'):
            return
        time.sleep(60)


if __name__ == '__main__':
    main()
