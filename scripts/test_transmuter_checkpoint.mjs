import assert from 'node:assert/strict';
import { existsSync, mkdtempSync, readFileSync, readdirSync } from 'node:fs';
import { tmpdir } from 'node:os';
import path from 'node:path';
import test from 'node:test';
import { checkpointSearch, writeFinalResult } from './transmuter-checkpoint.mjs';

function fixture() {
  const folder = mkdtempSync(path.join(tmpdir(), 'transmuter-checkpoint-'));
  const config = {
    bestSource: path.join(folder, 'best.c'),
    result: path.join(folder, 'engine.json'),
  };
  const state = {
    bestScore: 9,
    bestSource: 'int value = 1;\n',
    iteration: 17,
    elapsed: 250,
  };
  return { folder, config, state, search: { getState: () => state } };
}

test('checkpoint waits until the baseline score is known', () => {
  const { config, search } = fixture();
  assert.equal(checkpointSearch(config, search, null), false);
  assert.equal(existsSync(config.bestSource), false);
  assert.equal(existsSync(config.result), false);
});

test('checkpoint atomically refreshes recoverable best source and metrics', () => {
  const { folder, config, state, search } = fixture();
  assert.equal(checkpointSearch(config, search, 12, 'running'), true);
  assert.equal(readFileSync(config.bestSource, 'utf8'), 'int value = 1;\n');
  assert.deepEqual(JSON.parse(readFileSync(config.result, 'utf8')), {
    perfectMatch: false,
    bestScore: 9,
    baseScore: 12,
    totalIterations: 17,
    elapsed: 250,
    reason: 'running',
    checkpoint: true,
  });

  state.bestScore = 4;
  state.bestSource = 'int value = 2;\n';
  state.iteration = 33;
  checkpointSearch(config, search, 12, 'signal-sigterm');
  assert.equal(readFileSync(config.bestSource, 'utf8'), 'int value = 2;\n');
  assert.equal(JSON.parse(readFileSync(config.result, 'utf8')).reason, 'signal-sigterm');
  assert.equal(readdirSync(folder).some((name) => name.includes('.tmp-')), false);
});

test('final result replaces the checkpoint marker', () => {
  const { config } = fixture();
  writeFinalResult(config, {
    perfectMatch: false,
    bestScore: 3,
    bestSource: 'int final_value = 3;\n',
    baseScore: 12,
    totalIterations: 40,
    elapsed: 300,
    reason: 'timeout',
  });
  assert.equal(readFileSync(config.bestSource, 'utf8'), 'int final_value = 3;\n');
  assert.equal(JSON.parse(readFileSync(config.result, 'utf8')).checkpoint, false);
});
