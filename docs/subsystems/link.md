# Link subsystem

The first recovered link slice configures the GBA serial hardware for multiplayer mode at 115,200 bits per second.

`multiplayer_serial_enable` installs the serial callback, resets the general-purpose communication register, selects multiplayer mode, writes the idle word `0xFEFE`, and enables the serial interrupt in both `SIOCNT` and `IE`. `multiplayer_serial_interrupt` refreshes that idle word. `multiplayer_serial_disable` disables and acknowledges the interrupt while leaving the port configured in multiplayer mode.

These routines previously lived at the end of `title_screen.c` because their known callers are title and option transitions. They now live under `src/link` with a shared interface under `include/link`.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
