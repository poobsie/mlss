#include "global.h"
#include "common.h"
#include "gba/syscall.h"
#include "process.h"

#define SECTION(name) __attribute__((section(".text.early_system_helpers." #name)))

SECTION(sub_801AE1C) void sub_801AE1C(void)
{
    s32 zero = 0;
    CpuSet(&zero, (void *)0x03000D28, 0x05000002);
}

SECTION(sub_801B85C) void sub_801B85C(struct Process *process, u32 flags)
{
    process->definition = (struct ProcessDefinition *)0x08CDBD98;
    process_remove(process, flags);
}
