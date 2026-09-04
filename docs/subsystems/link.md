# Link subsystem

The first recovered link slice configures the GBA serial hardware for multiplayer mode at 115,200 bits per second.

`multiplayer_serial_enable` installs the serial callback, resets the general-purpose communication register, selects multiplayer mode, writes the idle word `0xFEFE`, and enables the serial interrupt in both `SIOCNT` and `IE`. `multiplayer_serial_interrupt` refreshes that idle word. `multiplayer_serial_disable` disables and acknowledges the interrupt while leaving the port configured in multiplayer mode.

These routines previously lived at the end of `title_screen.c` because their known callers are title and option transitions. They now live under `src/link` with a shared interface under `include/link`.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports every linked C function exact, with zero mismatches.
`multiplayer_frame_update` is called from the frame interrupt path. While multiplayer is active and ready, it records a pending result, swaps the active transfer buffers, reads the serial status bit, writes the multiplayer idle word `0xFEFE`, starts serial I/O, and arms Timer 3. `multiplayer_mark_transfer_ready` sets the readiness byte only for an active link state.

The state overlay names only fields proven by those operations. The four buffer words are still distinguished by offsets because their payload directions are not yet established.
