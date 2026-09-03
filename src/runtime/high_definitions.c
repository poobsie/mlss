#include "runtime/high_definitions.h"

#define SEC(name) __attribute__((section(".text.high." #name)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))
#define PTRAT(p, o) (*(void**)((u8*)(p) + (o)))

void free_heap_8018DA8(void*);
u16 sub_81DA870(u16 value, u32 argument, u32 mode);
void sub_8161330(void);

SEC(sub_81DA85C) u16 sub_81DA85C(u16 value, u32 argument) {
    return sub_81DA870(value, argument, 1);
}

SEC(sub_81DD2E0) void* sub_81DD2E0(void) {
    return *(void**)0x08CDBD64;
}

SEC(sub_81DD670) void sub_81DD670(void* object, u32 flags) {
    PTRAT(object, 4) = (void*)0x08CDCF50;
    if (flags & 1)
        free_heap_8018DA8(object);
}

SEC(sub_81DD690) void sub_81DD690(void) {
    sub_8161330();
}

SEC(sub_81DD69C) void sub_81DD69C(void* object) {
    PTRAT(object, 0xC) = (void*)0x08CDD0D0;
    U32AT(object, 4) = 0;
    U32AT(object, 0) = 0;
    U32AT(object, 8) = 0;
}

const u16 sub_81DD690_padding SEC(sub_81DD690) = 0;
