# Math runtime

`InterpolationState` is the 16-byte value record configured by `interpolation_configure` and reset by `interpolation_clear`. Current callers prove an initial value, signed 16-bit duration, target value, and an accumulator initialized to `0xFFFF0000`.

The exact interpolation step formula remains in assembly. The field names are therefore mechanical and stop short of assigning units such as pixels or fixed-point scale.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
