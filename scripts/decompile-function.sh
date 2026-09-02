#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 2 ]]; then
    printf 'Usage: %s <assembly-file> <function-name> [m2c options...]\n' "$0" >&2
    exit 2
fi

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
assembly_file="$1"
function_name="$2"
shift 2

exec "$project_root/.decomp-tools/venv/bin/m2c" \
    --target gba \
    --function "$function_name" \
    --valid-syntax \
    "$@" \
    "$assembly_file"
