#!/usr/bin/env bash
set -euo pipefail

# Keep dependency trees on a native Unix filesystem when using WSL.
tool_root="${MLSS_MUTATION_TOOLS:-${XDG_CACHE_HOME:-$HOME/.cache}/mlss-mutation}"
transmuter_revision=0ab756707e04f4a401a2884d0c9e50001446a1df
permuter_revision=fb516c435c6f362fbced66e171545324306b607b
bun_version=1.3.12
pnpm_version=9.14.4

if [[ "$(uname -s)" != Linux || "$(uname -m)" != x86_64 ]]; then
    printf 'This setup currently supports Linux x86_64, including WSL.\n' >&2
    exit 1
fi
for command_name in curl unzip git npm python3; do
    command -v "$command_name" >/dev/null || { printf 'Missing %s\n' "$command_name" >&2; exit 1; }
done
mkdir -p "$tool_root"

checkout() {
    local name="$1" url="$2" revision="$3"
    if [[ ! -d "$tool_root/$name/.git" ]]; then
        git clone "$url" "$tool_root/$name"
    fi
    if [[ -n "$(git -C "$tool_root/$name" status --porcelain --untracked-files=no)" ]]; then
        printf 'Refusing to replace modified tool checkout: %s\n' "$name" >&2
        exit 1
    fi
    git -C "$tool_root/$name" fetch --quiet origin "$revision"
    git -C "$tool_root/$name" checkout --quiet --detach "$revision"
}

checkout transmuter https://github.com/macabeus/transmuter.git "$transmuter_revision"
checkout decomp-permuter https://github.com/simonlindholm/decomp-permuter.git "$permuter_revision"
if [[ ! -x "$tool_root/bun-linux-x64/bun" ]] || [[ "$("$tool_root/bun-linux-x64/bun" --version)" != "$bun_version" ]]; then
    curl -fL "https://github.com/oven-sh/bun/releases/download/bun-v$bun_version/bun-linux-x64.zip" -o "$tool_root/bun.zip"
    unzip -qo "$tool_root/bun.zip" -d "$tool_root"
fi
npm install --prefix "$tool_root/runtime" "pnpm@$pnpm_version" > "$tool_root/pnpm-install.log" 2>&1
export PATH="$tool_root/bun-linux-x64:$tool_root/runtime/node_modules/.bin:$PATH"
(
    cd "$tool_root/transmuter"
    pnpm install --frozen-lockfile > "$tool_root/transmuter-install.log" 2>&1
    pnpm --filter @transmuter/core run build:esm > "$tool_root/transmuter-build.log" 2>&1
    pnpm --filter @transmuter/cli run build >> "$tool_root/transmuter-build.log" 2>&1
)
python3 -m venv "$tool_root/venv"
"$tool_root/venv/bin/pip" install 'toml==0.10.2' 'pycparser==2.22' > "$tool_root/permuter-install.log" 2>&1
"$tool_root/venv/bin/python" "$tool_root/decomp-permuter/permuter.py" --help > "$tool_root/permuter-help.txt"
bun "$tool_root/transmuter/packages/cli/dist/index.js" --help > "$tool_root/transmuter-help.txt"
printf 'Mutation tools ready: %s\n' "$tool_root"
