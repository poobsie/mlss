# Indexed work runtime

This slice covers setup and teardown around a selected work-record buffer and
the screen process that owns its supporting resources.

`indexed_work_buffer_initialize` allocates a `0x1BC`-byte destination, selects
one of four `0x6F8`-byte source records from the active runtime block, and
copies the `0x1BC`-byte payload beginning at source offset `0x30`. It also
publishes the destination subregion at offset `0x78`. The selector is proven to
come from bits 2 and 3 of the word at `0x03000D40`; the gameplay meaning of
those bits and the full record layout remain unknown.

`field_capture_music_channels` records the two active song identifiers,
applies a caller-provided volume transition duration to both music channels,
and returns a two-bit mask describing which channels were playing before the
transition. The byte-sized output is intentional because only the low byte of
each global song identifier is retained.

`indexed_work_screen_destroy` clears the known halfwords in the work header at
`0x02000000`, removes three proven display-state flags, and releases the owned
resource loader, buffer, auxiliary object, and child process before removing
the screen itself. The process definition address is retained because the
screen class has not yet been identified by a stable game-facing name.
