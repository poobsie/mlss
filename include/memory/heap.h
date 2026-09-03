#ifndef GUARD_MEMORY_HEAP_H
#define GUARD_MEMORY_HEAP_H

#include "global.h"

void heap_init(void);
void heap_free_block(void* allocation);
void* heap_alloc_block(bool32 useEwramHeap, int size, const char* label);

/* Distinct original entry points with behavior that is currently identical. */
void free_heap_8018D9C(void* allocation);
void free_heap_8018DA8(void* allocation);
void* alloc_zero_8018DB4(int size, bool32 useEwramHeap, char* label, int clear);
void* alloc_Zero(int size, bool32 useEwramHeap, char* label, u8 clear);

#endif
