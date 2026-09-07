#!/usr/bin/env python3
"""Local, automatically refreshed queue estimate. No model or network service required."""
import argparse
from collections import defaultdict
from datetime import datetime, timedelta
import html
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import random
import statistics


def improved(result):
    score = result.get('search', {})
    return (result.get('best_source') is not None and score.get('bestScore') is not None
            and score.get('baseScore') is not None and score['bestScore'] < score['baseScore'])


def seconds_used(result):
    folder = Path(result['artifacts'])
    try:
        start = min(p.stat().st_mtime for p in folder.glob('command-*.log'))
        return max(0, (folder/'result.json').stat().st_mtime - start)
    except (OSError, ValueError):
        return result.get('process', {}).get('wall_seconds', 0) + 5


def estimate(state):
    budgets = state['identity']['stages']
    groups = defaultdict(lambda: defaultdict(dict))
    for key, result in state['runs'].items():
        name, digest, engine, stage = key.split(':')
        groups[(name, digest)][int(stage)][engine] = result
    reached = [0]*len(budgets)
    advance = [0]*len(budgets)
    durations = [[] for _ in budgets]
    completed = 0
    active_budget = 0
    for (name, _), stages in groups.items():
        expected_engines = {'transmuter', 'permuter'}
        finished = name in state['matches']
        for stage in range(len(budgets)):
            pair = stages.get(stage, {})
            if not expected_engines:
                finished = True
                break
            if not expected_engines.issubset(pair):
                active_budget += budgets[stage] + 10
                break
            reached[stage] += 1
            durations[stage].append(max(seconds_used(r) for r in pair.values()))
            expected_engines = {engine for engine, r in pair.items() if improved(r)}
            if name in state['matches']:
                expected_engines = set()
            if expected_engines:
                advance[stage] += 1
            else:
                finished = True
                break
            if stage == len(budgets)-1:
                finished = True
        completed += finished
    total = state['draft_variants']
    unstarted = max(0, total-len(groups))
    rng = random.Random(0)
    forecasts = []
    for _ in range(1000):
        probability = 1.0
        per_case = 0.0
        for stage, budget in enumerate(budgets):
            values = durations[stage]
            # A short initial sample must not assume later functions are equally easy.
            observed = statistics.mean(rng.choices(values, k=len(values))) if values else budget+10
            weight = len(values)/(len(values)+8)
            duration = weight*observed + (1-weight)*(budget+10)
            per_case += probability*duration
            probability *= rng.betavariate(advance[stage]+1,
                                            reached[stage]-advance[stage]+3)
        forecasts.append(unstarted*per_case + active_budget)
    forecasts.sort()
    done = state['status'] == 'draft_queue_exhausted'
    return {'scope': 'Current retained-draft queue only', 'total_drafts': total,
            'completed_drafts': total if done else completed, 'started_drafts': len(groups),
            'completed_searches': len(state['runs']), 'exact_candidates': len(state['matches']),
            'remaining_seconds': 0 if done else forecasts[500],
            'range_low_seconds': 0 if done else forecasts[100]*0.75,
            'range_high_seconds': 0 if done else forecasts[900]*1.5,
            'stage_samples': reached, 'stage_extensions': advance,
            'confidence': 'early estimate' if reached[0] < 50 else 'learning from observed throughput',
            'status': state['status']}


def duration(seconds):
    if seconds < 60:
        return 'under a minute'
    if seconds < 3600:
        return f'{seconds/60:.0f} minutes'
    if seconds < 172800:
        return f'{seconds/3600:.1f} hours'
    return f'{seconds/86400:.1f} days'


def render(result, running):
    now = datetime.now().astimezone()
    finish = now + timedelta(seconds=result['remaining_seconds'])
    progress = 100*result['completed_drafts']/max(1,result['total_drafts'])
    eta = duration(result['remaining_seconds']) if running else 'Waiting for worker'
    if result['status'] == 'draft_queue_exhausted':
        eta = 'Queue complete'
    return f'''<!doctype html><html><head><meta charset="utf-8">
<meta http-equiv="refresh" content="30"><title>Decompilation progress</title>
<style>body{{font:18px system-ui;background:#101820;color:#e8eef2;max-width:900px;margin:60px auto;padding:24px}}
h1{{font-size:24px}}.eta{{font-size:56px;margin:20px 0}}.muted{{color:#acbdc9}}progress{{width:100%;height:22px}}
.cards{{display:flex;gap:36px;flex-wrap:wrap;margin:32px 0}}b{{display:block;font-size:30px}}p{{line-height:1.6}}</style></head><body>
<h1>Decompilation queue</h1><div class="eta">{eta}</div>
<p class="muted">Estimated remaining time · {result['confidence']}<br>
Planning range: {duration(result['range_low_seconds'])} to {duration(result['range_high_seconds'])}<br>
Approximate finish: {finish:%a %b %d, %I:%M %p %Z} (if continuously running)</p>
<progress value="{progress}" max="100"></progress>
<div class="cards"><div><b>{result['completed_drafts']:,} / {result['total_drafts']:,}</b>drafts finished</div>
<div><b>{result['completed_searches']:,}</b>searches completed</div>
<div><b>{result['exact_candidates']:,}</b>exact candidates found</div></div>
<p>Worker: {'running' if running else 'stopped'} · Queue: {html.escape(result['status'])}</p>
<p class="muted">This estimates the current draft queue, including longer searches for improving candidates.
It does not estimate completion of the entire game or time needed to review and integrate results.
The range is a planning allowance, not a statistical guarantee. Larger functions later in the queue,
new drafts, pauses, and CPU contention can change it. Matching a function can skip other drafts for
that function, so progress may jump forward.</p>
<p class="muted">Refreshes automatically every 30 seconds using local measurements. No OpenAI tokens.
Last refreshed: {now:%I:%M:%S %p %Z}. <a style="color:#85c5ff" href="/status.json">Raw estimate</a></p>
</body></html>'''


def main():
    import fcntl
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('--port', type=int, default=8765)
    args = parser.parse_args()
    class Handler(BaseHTTPRequestHandler):
        def do_GET(self):
            if self.path not in ('/', '/status.json'):
                self.send_error(404)
                return
            try:
                result = estimate(json.loads((args.directory/'state.json').read_text()))
                with (args.directory/'lock').open('a') as lock:
                    try:
                        fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
                        running = False
                    except BlockingIOError:
                        running = True
                result['worker_running'] = running
                content = json.dumps(result, indent=2) if self.path == '/status.json' else render(result, running)
                encoded = content.encode()
                self.send_response(200)
                self.send_header('Content-Type', 'application/json' if self.path.endswith('.json') else 'text/html; charset=utf-8')
                self.send_header('Cache-Control', 'no-store')
                self.send_header('Content-Length', str(len(encoded)))
                self.end_headers()
                self.wfile.write(encoded)
            except (OSError, ValueError) as error:
                self.send_error(503, str(error))
        def log_message(self, *args):
            pass
    ThreadingHTTPServer(('127.0.0.1', args.port), Handler).serve_forever()


if __name__ == '__main__':
    main()
