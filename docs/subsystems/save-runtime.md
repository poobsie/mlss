# Save runtime

`gSaveState` is the save-state pointer stored at the original symbol `dword_3000FFC`. Its first recovered byte after the eight-character name contains the easy-sleep, rumble, and auto-sleep settings used by the options screen. The low three bits remain `value8_0` because their meaning is not proven.

`save_get_title_summary` returns the structure at offset `0x1FF8` in that save state. Both title-screen construction paths copy its first word and following byte into `gTitleSaveSummary`, then combine current settings and Game Boy Player detection into its final flag byte. The copied values retain offset-based names until the score-display arguments are understood.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
`save_local_flag_read` and `save_local_flag_write` expose a local flag namespace beginning at global save ID `0x1B90`. Both apply the same base translation before delegating to the shared byte-valued save store. The local IDs remain numeric because the individual flags have not yet been tied to named events or settings.
