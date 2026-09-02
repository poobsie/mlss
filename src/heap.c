#include "global.h"
#include "common.h"

void free_heap_memory_8018C68(void* allocation);

/* The label is already in r2. The original two-argument declaration leaves it there for the callee. */
s32 alloc_heap_8018CEC(s32 useEwramHeap, s32 size);

void free_heap_8018D9C(void* allocation) {
    free_heap_memory_8018C68(allocation);
}

void free_heap_8018DA8(void* allocation) {
    free_heap_memory_8018C68(allocation);
}

void* alloc_zero_8018DB4(int size, bool32 useEwramHeap, char* label, int clear) {
    int savedSize;
    u8 shouldClear;
    s32 allocation;
    u32 zero;

    savedSize = size;
    shouldClear = clear;
    allocation = alloc_heap_8018CEC(useEwramHeap, savedSize);
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
    allocation = alloc_heap_8018CEC(useEwramHeap, savedSize);
    if (shouldClear != 0) {
        zero = 0;
        CpuSet(&zero, (void*)allocation,
               CPU_SET_32BIT | CPU_SET_SRC_FIXED | ((u32)(savedSize << 9) >> 11));
    }

    return (void*)allocation;
}
