#!/usr/bin/env python3
"""Resume CPU searches over retained drafts, extending only improving candidates."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import fcntl
import hashlib
import json
from pathlib import Path
from types import SimpleNamespace

import decomp_workflow as workflow
from decomp_mutate import run_search


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def save(path, value):
    temporary = path.with_suffix('.tmp')
    temporary.write_text(json.dumps(value, indent=2) + '\n')
    temporary.replace(path)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--draft-root', type=Path, action='append', required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--symbols-elf', type=Path, required=True,
                        help='snapshot from an exact accepted build')
    parser.add_argument('--jobs', type=int, default=12)
    parser.add_argument('--stages', type=int, nargs='+', default=[30, 300, 1800])
    parser.add_argument('--tools', default=str(Path.home()/'.cache/mlss-mutation'))
    args = parser.parse_args()
    if args.jobs < 2 or args.jobs > 32 or args.jobs % 2 or any(s < 1 for s in args.stages):
        parser.error('use even 2..32 jobs and positive stages')
    root = args.output.resolve()
    root.mkdir(parents=True, exist_ok=True)
    lock = (root/'lock').open('w')
    fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
    state_path = root/'state.json'
    identity = {'aliases': digest(args.symbols_elf),
                'reference': digest(workflow.ROOT/'.decomp-tools/reference/mlss.gba'),
                'stages': args.stages}
    state = json.loads(state_path.read_text()) if state_path.exists() else {
        'identity': identity, 'runs': {}, 'matches': [], 'status': 'running'}
    if state['identity'] != identity:
        raise ValueError('baseline or stages changed; use a new output directory')
    paths = workflow.git_tracked_assembly()
    candidates = {c.name: c for c in workflow.discover(workflow.ROOT/'mlss.map', paths)
                  if c.mode == 'thumb'}
    blocks = {name: block for path in paths
              for name, _, _, _, block in workflow.function_blocks(path)}
    cases = {}
    for directory in args.draft_root:
        for source in directory.rglob('*.c'):
            if source.stem in candidates:
                cases[(source.stem, digest(source))] = source.resolve()
    state['eligible_functions'] = len(candidates)
    state['draft_functions'] = len({name for name, _ in cases})
    state['draft_variants'] = len(cases)
    state['status'] = 'running'
    save(state_path, state)
    print('QUEUE', state['eligible_functions'], 'eligible functions,', len(cases), 'drafts', flush=True)
    with ThreadPoolExecutor(max_workers=2) as pool:
        for (name, source_hash), source in sorted(cases.items(), key=lambda item: candidates[item[0][0]].size):
            if name in state['matches']:
                continue
            sources = dict.fromkeys(('transmuter', 'permuter'), source)
            for stage, seconds in enumerate(args.stages):
                if (root/'STOP').exists():
                    state['status'] = 'paused'
                    save(state_path, state)
                    return
                pending = {}
                results = {}
                for engine, current_source in sources.items():
                    key = f'{name}:{source_hash}:{engine}:{stage}'
                    if key in state['runs']:
                        results[engine] = state['runs'][key]
                    else:
                        pending[engine] = (key, pool.submit(run_search, SimpleNamespace(
                            function=name, source=str(current_source), engine=engine,
                            seconds=seconds, jobs=args.jobs//2, seed=stage+1,
                            tools=args.tools, work_root=str(root/'searches'),
                            max_compiles=1000000, prepare_only=False,
                            target=(candidates[name], blocks[name]), symbols_elf=args.symbols_elf)))
                for engine, (key, future) in pending.items():
                    result = future.result()
                    results[engine] = result
                    state['runs'][key] = result
                    if result['status'] in ('span_match', 'already_matching'):
                        if name not in state['matches']:
                            state['matches'].append(name)
                    save(state_path, state)
                    # Only compiler scratch files inside this owned search directory.
                    # Preserve source, target object, reports and logs for review.
                    folder = Path(result['artifacts']).resolve()
                    folder.relative_to(root/'searches')
                    for artifact in folder.rglob('*.elf'):
                        artifact.unlink()
                    print(name, engine, seconds, result['status'],
                          result.get('search', {}), flush=True)
                if name in state['matches']:
                    break
                sources = {engine: Path(result['best_source']) for engine, result in results.items()
                           if result.get('best_source') and
                           result.get('search', {}).get('bestScore') is not None and
                           result['search']['bestScore'] < result['search']['baseScore']}
                if not sources:
                    break
    state['status'] = 'draft_queue_exhausted'
    save(state_path, state)
    print('DONE', len(state['runs']), 'searches;', len(state['matches']), 'matches needing review', flush=True)


if __name__ == '__main__':
    main()
