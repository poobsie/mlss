# Reading partially decompiled source

Matching decompilation has two independent questions: does the C reproduce the original machine code, and
do we understand what that code means? This project records those answers separately. An exact match may
still have provisional types and names.

## Names

- `sub_8057568` identifies a function by its original ROM address. It means the function's purpose is not
  established yet.
- `field_24` or `FIELD_AT(object, u16 *, 0x24)` identifies a layout offset whose meaning is still unknown.
- `UnknownWord` is a 32-bit value whose signedness, pointer status, or domain has not been proved.
- A descriptive name such as `play_sfx_80195B4` keeps the address suffix while the project is still checking
  callers and related functions. Once a subsystem has stable headers, the suffix can be reconsidered.

These placeholders are evidence markers, not an invitation to guess. Rename them when callers, callees,
data tables, or runtime observation establish a role.

## Source layout

Semantic modules contain understood systems. Current examples include process management, heap handling,
option screens, the title screen, and several Mario Bros. helpers.

Neutral holding modules contain exact matches that still cross several unknown systems:

- `early_code_helpers*.c` covers isolated functions from the early ROM region.
- `text_middle_helpers.c`, `text_high_helpers.c`, and `text_late_helpers.c` group
  provisional helpers by their location in the original monolithic assembly.
- `text_small_functions_*.c` and `text_misc_helpers_*.c` hold unrelated exact functions pending subsystem
  identification.
- `text_upper_functions/` keeps one provisional function per file where combining them would make later
  subsystem moves harder.

The word `text` refers to the executable `.text` section, not necessarily dialogue or font handling.

## Matching-only structure

Section attributes and explicit padding constants preserve the original order and alignment. Repeated
function-generating macros represent genuinely identical code shapes. Keep them when they make the source
clearer, but do not let a macro erase meaningful behavioral differences merely because several functions
happen to compile alike.

When improving a function, preserve exact output first, then replace raw offsets and unknown values with a
shared structure or enum as the surrounding evidence becomes reliable.

Disabled or rejected drafts belong in the ignored `scratch/` directory. Keeping them out of `src/` prevents
empty objects and abandoned experiments from muddying build and progress reports.
