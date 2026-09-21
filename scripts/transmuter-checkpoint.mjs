import { renameSync, writeFileSync } from 'node:fs';

function atomicWrite(path, contents) {
  const temporary = `${path}.tmp-${process.pid}`;
  writeFileSync(temporary, contents);
  renameSync(temporary, path);
}

function unverifiedMetrics(metrics) {
  const { perfectMatch, ...rest } = metrics;
  return {
    ...rest,
    enginePerfectMatch: Boolean(perfectMatch || rest.bestScore === 0),
    perfectMatch: false,
    canonicalVerification: 'pending',
  };
}

export function checkpointSearch(config, search, baseScore, reason = 'checkpoint') {
  if (baseScore === null) {
    return false;
  }

  const state = search.getState();
  const metrics = unverifiedMetrics({
    perfectMatch: state.bestScore === 0,
    bestScore: state.bestScore,
    baseScore,
    totalIterations: state.iteration,
    elapsed: state.elapsed,
    reason,
    checkpoint: true,
  });
  atomicWrite(config.bestSource, state.bestSource);
  atomicWrite(config.result, JSON.stringify(metrics, null, 2) + '\n');
  return true;
}

export function writeFinalResult(config, result) {
  const { bestSource, ...metrics } = result;
  atomicWrite(config.bestSource, bestSource);
  atomicWrite(config.result, JSON.stringify(
    unverifiedMetrics({ ...metrics, checkpoint: false }), null, 2) + '\n');
}
