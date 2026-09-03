#include "runtime/high_state.h"

#define SEC(name) __attribute__((section(".text.high." #name)))

SEC(sub_8199470) u8 sub_8199470(u8* output)
{
    *output = *(vu16*)0x04000006;
    return *output;
}

SEC(sub_8199D48) u32 sub_8199D48(struct RuntimePointerSelection* selection, u32 index)
{
    selection->selectedEntry = ((void**)*(void**)0x03001070)[index];
    return 0;
}

SEC(sub_8199F24) void sub_8199F24(void* pointer)
{
    *(void**)0x03001074 = pointer;
}

SEC(sub_819A694) void sub_819A694(struct RuntimeLatchedState* state)
{
    state->flags &= 0xCFFF;
    state->latchedValue16 = state->value16;
}

SEC(sub_819A718) void sub_819A718(struct RuntimeLatchedState* state)
{
    state->flags &= 0xF9FF;
    state->latchedValue1A = state->value1A;
}
