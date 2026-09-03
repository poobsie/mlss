#include "global.h"
#include "common.h"

void heap_free_block(void* allocation);

/* The label is already in r2. This matching declaration must leave it there. */
s32 heap_alloc_block(s32 useEwramHeap, s32 size);

void free_heap_8018D9C(void* allocation) {
    heap_free_block(allocation);
}

void free_heap_8018DA8(void* allocation) {
    heap_free_block(allocation);
}

void* alloc_zero_8018DB4(int size, bool32 useEwramHeap, char* label, int clear) {
    int savedSize;
    u8 shouldClear;
    s32 allocation;
    u32 zero;

    savedSize = size;
    shouldClear = clear;
    allocation = heap_alloc_block(useEwramHeap, savedSize);
    if (shouldClear != 0) {
        zero = 0;
        CpuSet(&zero, (void*)allocation,
               CPU_SET_32BIT | CPU_SET_SRC_FIXED | ((u32)(savedSize << 9) >> 11));
    }

    return (void*)allocation;
}

void* alloc_Zero(int size, bool32 useEwramHeap, char* label, u8 clear) {
    int savedSize;
    u8 shouldClear;
    s32 allocation;
    u32 zero;

    savedSize = size;
    shouldClear = clear;
    allocation = heap_alloc_block(useEwramHeap, savedSize);
    if (shouldClear != 0) {
        zero = 0;
        CpuSet(&zero, (void*)allocation,
               CPU_SET_32BIT | CPU_SET_SRC_FIXED | ((u32)(savedSize << 9) >> 11));
    }

    return (void*)allocation;
}
