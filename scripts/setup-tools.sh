#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
tool_root="$project_root/.decomp-tools"
source_root="$tool_root/src"
venv_root="$tool_root/venv"
reference_rom="${1:-${MLSS_REFERENCE_ROM:-}}"

m2c_commit="a73bfba20a00db8a546ec84d6ebec76063ebcf60"
asm_differ_commit="c80ea4e3d16ecc8f4c21923633f3f9b1fb534c53"
permuter_commit="fb516c435c6f362fbced66e171545324306b607b"
agbcc_commit="59b966ed1b8f371856dcf99f1546c2fe89c678ca"

required_commands=(
    arm-none-eabi-as
    arm-none-eabi-ld
    arm-none-eabi-objcopy
    arm-none-eabi-objdump
    arm-none-eabi-nm
    arm-none-eabi-readelf
    git
    make
    python3
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

if [[ -z "$reference_rom" ]]; then
    printf 'Usage: %s /path/to/clean-us-rom.gba\n' "$0" >&2
    printf 'Alternatively set MLSS_REFERENCE_ROM. The ROM is copied into ignored local tooling storage.\n' >&2
    exit 2
fi
if [[ ! -f "$reference_rom" ]]; then
    printf 'Reference ROM not found: %s\n' "$reference_rom" >&2
    exit 1
fi

if command -v sha1sum >/dev/null 2>&1; then
    actual_hash="$(sha1sum "$reference_rom" | awk '{print $1}')"
elif command -v shasum >/dev/null 2>&1; then
    actual_hash="$(shasum -a 1 "$reference_rom" | awk '{print $1}')"
else
    printf 'Missing SHA-1 tool: install sha1sum or shasum.\n' >&2
    exit 1
fi
expected_hash="$(awk '{print $1}' "$project_root/rom.sha1")"
if [[ "$actual_hash" != "$expected_hash" ]]; then
    printf 'Reference ROM SHA-1 mismatch. Expected %s, got %s.\n' "$expected_hash" "$actual_hash" >&2
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
checkout_tool agbcc https://github.com/jiangzhengwenjz/agbcc.git "$agbcc_commit"

(
    cd "$source_root/agbcc"
    ./build.sh
    ./install.sh "$project_root"
)

if [[ ! -x "$venv_root/bin/python" ]]; then
    python3 -m venv "$venv_root"
fi

"$venv_root/bin/python" -m pip install --quiet --upgrade pip
"$venv_root/bin/python" -m pip install --quiet \
    -e "$source_root/m2c" \
    -e "$source_root/asm-differ" \
    pynacl toml tiktoken==0.12.0

toolchain_bin="$(dirname "$(command -v arm-none-eabi-as)")"
toolchain_root="${DEVKITARM:-$(dirname "$toolchain_bin")}"
if command -v nproc >/dev/null 2>&1; then
    jobs="$(nproc)"
else
    jobs="$(getconf _NPROCESSORS_ONLN 2>/dev/null || printf '1')"
fi
make -C "$project_root" DEVKITARM="$toolchain_root" -j"$jobs"
mkdir -p "$tool_root/reference"
if ! cmp -s "$reference_rom" "$tool_root/reference/mlss.gba"; then
    cp "$reference_rom" "$tool_root/reference/mlss.gba"
fi
if [[ ! -f "$tool_root/reference/mlss.elf" ]]; then
    cp "$project_root/mlss.elf" "$tool_root/reference/mlss.elf"
fi
if [[ ! -d "$tool_root/expected/src" ]]; then
    mkdir -p "$tool_root/expected/src" "$tool_root/expected/asm"
    while IFS= read -r -d '' object; do
        relative="${object#"$project_root/build/"}"
        destination="$tool_root/expected/$relative"
        mkdir -p "$(dirname "$destination")"
        cp "$object" "$destination"
    done < <(find "$project_root/build/src" "$project_root/build/asm" -name '*.o' -print0)
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
