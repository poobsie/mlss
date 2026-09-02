#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tool_root="$project_root/.decomp-tools"
source_root="$tool_root/src"
venv_root="$tool_root/venv"

m2c_commit="a73bfba20a00db8a546ec84d6ebec76063ebcf60"
asm_differ_commit="c80ea4e3d16ecc8f4c21923633f3f9b1fb534c53"
permuter_commit="fb516c435c6f362fbced66e171545324306b607b"

required_commands=(
    arm-none-eabi-as
    arm-none-eabi-ld
    arm-none-eabi-objcopy
    arm-none-eabi-objdump
    git
    make
    python3
    sha1sum
)

missing=()
for command_name in "${required_commands[@]}"; do
    if ! command -v "$command_name" >/dev/null 2>&1; then
        missing+=("$command_name")
    fi
done

if ((${#missing[@]})); then
    printf 'Missing commands: %s\n' "${missing[*]}" >&2
    printf 'On Ubuntu, install: build-essential binutils-arm-none-eabi git python3 python3-venv\n' >&2
    exit 1
fi

mkdir -p "$source_root"

checkout_tool() {
    local name="$1"
    local url="$2"
    local commit="$3"
    local destination="$source_root/$name"

    if [[ ! -d "$destination/.git" ]]; then
        git clone "$url" "$destination"
    fi
    git -C "$destination" fetch --quiet origin "$commit"
    git -C "$destination" checkout --quiet --detach "$commit"
}

checkout_tool m2c https://github.com/matt-kempster/m2c.git "$m2c_commit"
checkout_tool asm-differ https://github.com/simonlindholm/asm-differ.git "$asm_differ_commit"
checkout_tool decomp-permuter https://github.com/simonlindholm/decomp-permuter.git "$permuter_commit"

if [[ ! -x "$venv_root/bin/python" ]]; then
    python3 -m venv "$venv_root"
fi

"$venv_root/bin/python" -m pip install --quiet --upgrade pip
"$venv_root/bin/python" -m pip install --quiet \
    -e "$source_root/m2c" \
    -e "$source_root/asm-differ" \
    pynacl toml tiktoken==0.12.0

make -C "$project_root" DEVKITARM=/usr -j"$(nproc)"
mkdir -p "$tool_root/reference"
if [[ ! -f "$tool_root/reference/mlss.elf" ]]; then
    cp "$project_root/mlss.elf" "$tool_root/reference/mlss.elf"
fi
if [[ ! -d "$tool_root/expected/src" ]]; then
    mkdir -p "$tool_root/expected/src" "$tool_root/expected/asm"
    cp "$project_root"/build/src/*.o "$tool_root/expected/src/"
    cp "$project_root"/build/asm/*.o "$tool_root/expected/asm/"
fi

printf 'Tooling is ready.\n'
printf 'Build:     make\n'
printf 'Diff:      .decomp-tools/venv/bin/asm-differ -mwo <existing-C-symbol>\n'
printf 'Decompile: scripts/decompile-function.sh <asm-file> <symbol>\n'
printf 'Candidates: .decomp-tools/venv/bin/python scripts/decomp_workflow.py scan\n'
printf 'Packet:     .decomp-tools/venv/bin/python scripts/decomp_workflow.py packet <symbol>\n'
printf 'Benchmark:  .decomp-tools/venv/bin/python scripts/decomp_workflow.py benchmark <symbol>\n'
printf 'Self-test:  .decomp-tools/venv/bin/python scripts/test_decomp_workflow.py\n'
printf 'Progress:  .decomp-tools/venv/bin/python scripts/progress.py\n'
