# UI runtime

The current C boundary contains a compact generic UI object API. `UiObject` exposes three caller-supplied values at offsets `0x18` through `0x20`, plus reset state at offsets `0x40` through `0x48`. One reset entry also forwards to the still-address-named update routine `sub_8161E38`.

`UiSpritePair` owns two optional sprite pointers at offsets `0x10` and `0x14`. Its paired callbacks hide or show every present sprite. These operations were previously mixed with an unrelated recursive object-tree traversal.

The same layout has a vtable pointer at offset `0x0C`. Its base destructor temporarily installs vtable `0x08CDD0F8`, releases both present sprites, restores vtable `0x08CDD118`, and optionally frees the object. A second destructor installs the terminal vtable and performs the optional free without releasing sprites.

Names retain offsets where current C proves storage but not domain meaning. The update routine and callers must be recovered before those value names can be narrowed.

Four late UI state helpers now expose their exact sound and flag effects. One clears mask `0x08` in the word at `0x490`; two start or stop sound `0x97` while maintaining an active word at `0x88`; the fourth clears the halfword at `0xEA` before stopping the same sound. Offset-bearing names are retained because the larger UI owner layouts remain unknown.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,330 linked C functions checked, 1,330 exact, and zero mismatches.
`UiStyleState` initializes a two-halfword style block to flags `0x10` and value zero. `UiDefinitionNode` initializes a four-word node with definition `0x08CDD0E8`; its recovered return type matches callers that retain the initialized pointer.

The same construction layer now exposes an empty-pointer query, a shared-halfword reset at `0x0300102C`, and structural setters for a layout object's origin at `0x24/0x28` and data word at `0x64`. The data word remains offset-named until its consumers establish whether it holds text, graphics, or another descriptor.

`ui_set_flag_490_08` names the sole recovered operation on a larger late UI owner. Its object layout and flag meaning remain unresolved, so both the offset and mask stay explicit.

`UiSingleSpriteOwner` exposes the sprite pointer at offset `0x30`. Its paired callbacks hide and show that sprite, while the adjacent false-returning entry remains named as a visibility callback until its callback table is recovered.

`TextContext` replaces the former catch-all `struc_15` name for the text parser shared by the options and related screens. `text_context_set_cursor` installs the source cursor and its column and row, clears the restart and completion flag bits `0x01` and `0x20`, and returns the previous cursor. The options label builder now advances `cursor` explicitly when it encounters the observed `FF 0B 01` control sequence.
