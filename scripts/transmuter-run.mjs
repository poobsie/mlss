// A bounded, machine-readable adapter for the pinned local Transmuter library.
import { readFileSync } from 'node:fs';
import { pathToFileURL } from 'node:url';
import path from 'node:path';
import { checkpointSearch, writeFinalResult } from './transmuter-checkpoint.mjs';

const config = JSON.parse(readFileSync(process.argv[2], 'utf8'));
const { MutationSearch } = await import(pathToFileURL(path.join(
  config.toolRoot, 'transmuter/packages/core/dist/index.js')).href);
let baseScore = null;
let stopping = false;
let search;

function checkpoint(reason) {
  return checkpointSearch(config, search, baseScore, reason);
}

function onEvent(event) {
  if (event.type === 'started') {
    baseScore = event.baseScore;
  }
  if (event.type === 'started' || event.type === 'forked' || event.type === 'stats'
      || event.type === 'completed') {
    checkpoint(event.type === 'completed' ? event.reason : 'running');
  }
}

function stop(signal) {
  if (stopping) {
    return;
  }
  stopping = true;
  checkpoint(`signal-${signal.toLowerCase()}`);
  search.stop();
}

search = new MutationSearch({
  source: readFileSync(config.source, 'utf8'),
  functionName: config.function,
  targetObjectPath: config.target,
  compilerCommand: config.compiler,
  cwd: config.cwd,
  profile: 'agbcc',
  concurrency: config.jobs,
  timeoutMs: config.seconds * 1000,
  maxCompiles: config.maxCompiles,
  seed: config.seed,
  disabledRules: ['asm-register-swap'],
  onEvent,
});
process.once('SIGTERM', () => stop('SIGTERM'));
process.once('SIGINT', () => stop('SIGINT'));

try {
  const result = await search.start();
  writeFinalResult(config, result);
  const { bestSource, ...metrics } = result;
  console.log(JSON.stringify(metrics));
} catch (error) {
  checkpoint('error');
  throw error;
}
