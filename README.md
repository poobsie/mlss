# Mario & Luigi Superstar Saga

This is a decompilation of Mario & Luigi Superstar Saga (US).

It builds the following ROM:
* mlss.gba `sha1: 7c303cdde5061ee329296948060b875cb50ba410`

The project requires an exact match. `make verify` rebuilds the ROM and checks every linked C function;
`make progress` also prints the current C/assembly split.

## Reading the source

Files named for game systems, such as `process.c`, `option_screens.c`, and `title_screen.c`, contain code
whose role is understood. Files named `text_*_helpers.c` are neutral holding areas for exact C matches
whose subsystem is not yet established. Functions retain address names such as `sub_8057568` until call
sites, data, or runtime evidence justify a semantic name.

See [docs/reading-the-source.md](docs/reading-the-source.md) for the conventions used in partially
understood code, [INSTALL.md](INSTALL.md) for setup, and [DECOMP.md](DECOMP.md) for the matching workflow.
The continuous cleanup queue and slice acceptance rules are described in
[docs/detangling-workflow.md](docs/detangling-workflow.md).
