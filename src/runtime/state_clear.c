#include "runtime/functions.h"
#include "gba/syscall.h"

void runtime_clear_state_3000d28(void)
    __attribute__((section(".text.early_system_helpers.sub_801AE1C")));
void runtime_clear_state_3000d28(void) {
    s32 zero = 0;
    CpuSet(&zero, (void*)0x03000D28, 0x05000002);
}
