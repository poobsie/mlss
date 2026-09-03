#include "global.h"
#include "common.h"
#include "runtime/memory.h"

extern u8 runtimeCopyStart[] __asm__("sub_8000534");
extern u8 runtimeCopyEnd[] __asm__("sub_800063C");
extern u8 byte_3000C80;
extern u8 byte_3000D08;

void runtime_relocated_code_init(void) {
    int size;
    u8* copyStart;
    void* destination;

    size = (int)runtimeCopyEnd;
    copyStart = runtimeCopyStart;
    size -= (int)copyStart;
    destination = alloc_zero_8018DB4(size, FALSE, (char*)0x081DD7D0, FALSE);
    dword_3000C84 = (void (*)(int*, void*))destination;
    if (size < 0) {
        size += 3;
    }
    CpuSet(copyStart, destination, CPU_SET_32BIT | ((u32)(size << 9) >> 11));
    dword_3000C78 = (void (*)())0x0800063C;
    byte_3000D08 = 0;
    byte_3000C80 = 0;
}
