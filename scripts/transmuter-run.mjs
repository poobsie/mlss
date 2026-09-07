// A bounded, machine-readable adapter for the pinned local Transmuter library.
import { readFileSync, writeFileSync } from 'node:fs';
import { pathToFileURL } from 'node:url';
import path from 'node:path';

const config = JSON.parse(readFileSync(process.argv[2], 'utf8'));
const { MutationSearch } = await import(pathToFileURL(path.join(
  config.toolRoot, 'transmuter/packages/core/dist/index.js')).href);
const search = new MutationSearch({
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
});
const result = await search.start();
writeFileSync(config.bestSource, result.bestSource);
const { bestSource, ...metrics } = result;
writeFileSync(config.result, JSON.stringify(metrics, null, 2) + '\n');
console.log(JSON.stringify(metrics));
