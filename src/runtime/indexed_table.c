#include "runtime/indexed_table.h"

#include "gba/syscall.h"
#include "memory/heap.h"

#define TABLE_SEC(name) \
    __attribute__((section(".text.indexed_table." #name)))

TABLE_SEC(sub_812335C)
void indexed_work_buffer_initialize(void)
{
    register const u8* sourceBase asm("r5") = *(const u8**)0x03000FFC;
    register void** workBufferSlot asm("r4") = (void**)0x03000FF4;
    register u32 selector asm("r2");
    u32 sourceOffset;
    void* workBuffer;

    workBuffer = alloc_Zero(0x1BC, TRUE, (char*)0x08210F00, FALSE);
    *workBufferSlot = workBuffer;

    selector = *(u32*)0x03000D40;
    selector = (selector << 28) >> 30;
    sourceOffset = selector * 8 - selector;
    sourceOffset <<= 5;
    sourceOffset -= selector;
    sourceOffset <<= 3;
    sourceOffset += (u32)sourceBase;
    sourceOffset += 0x30;
    CpuSet((const void*)sourceOffset, workBuffer, 0xDE);
    *(u8**)0x03000FF8 = (u8*)*workBufferSlot + 0x78;
}
