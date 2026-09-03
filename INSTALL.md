# Prerequisites and installation

The canonical build uses a Unix-like shell, GNU Make, Python 3, Git, matching
`agbcc`, and ARM GNU binutils. Linux can run it directly. Windows users can use
WSL; the PowerShell wrappers under `scripts/` are optional conveniences.

Install `arm-none-eabi-as`, `arm-none-eabi-ld`, `arm-none-eabi-objcopy`,
`arm-none-eabi-objdump`, `arm-none-eabi-nm`, `arm-none-eabi-readelf`, Git,
Make, Python 3, and Python virtual-environment support through the host package
manager. If the ARM tools use a custom prefix, set `DEVKITARM` to the directory
containing their `bin/` directory before running setup or Make.

The game ROM is copyrighted and is not distributed with this repository.
Supply a clean US ROM when installing the local analysis tools. The setup
script installs the pinned matching compiler and analysis tools, then validates
the ROM's SHA-1 before copying it under the ignored
`.decomp-tools/reference/` directory:

```sh
scripts/setup-tools.sh /path/to/clean-us-rom.gba
```

The path may instead be supplied through `MLSS_REFERENCE_ROM`:

```sh
MLSS_REFERENCE_ROM=/path/to/clean-us-rom.gba scripts/setup-tools.sh
```

From the repository root, verify the installation:

```sh
make verify
```

The build must finish with `mlss.gba: OK`, followed by zero mismatched linked
C functions.
