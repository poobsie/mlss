# Memory subsystem

The heap implementation now lives in `src/memory/heap.c`, with shared declarations in `include/memory/heap.h`. The low-level assembly remains in `asm/heap.s` because the build currently treats assembly as a single flat source directory.

The allocator manages separate arenas in IWRAM and EWRAM. Each block has a 16-byte header containing neighboring block links, its size and free bit, and a four-byte allocation label. Allocation rounds requested sizes to four-byte alignment, splits sufficiently large free blocks, and records the caller's label. Freeing marks a block available and coalesces it with adjacent free blocks.

| Address | Previous name | Recovered name | Evidence |
| --- | --- | --- | --- |
| `0x08018BC0` | `init_heap` | `heap_init` | Initializes the IWRAM and EWRAM arena headers and their first free blocks. |
| `0x08018C68` | `free_heap_memory_8018C68` | `heap_free_block` | Marks the allocation header free and merges neighboring free blocks. |
| `0x08018CEC` | `alloc_heap_8018CEC` | `heap_alloc_block` | Selects an arena, finds and optionally splits a free block, writes its label, and returns the payload. |

`alloc_Zero` and `alloc_zero_8018DB4` remain distinct names because the ROM contains two separate but currently identical entry points. The same is true of `free_heap_8018D9C` and `free_heap_8018DA8`. Caller groups differ, but no behavioral distinction has been recovered yet.

The C wrappers intentionally call `heap_alloc_block` through a two-argument matching declaration. The allocation label arrives in register `r2` as the wrapper's third argument. Expressing the complete three-argument call changes register allocation under the original compiler and breaks the ROM match; the public header records the actual interface.

## Verification

The full ROM passes its SHA-1 comparison. The exact-function verifier reports 1,301 linked C functions checked, 1,301 exact, and zero mismatches.
