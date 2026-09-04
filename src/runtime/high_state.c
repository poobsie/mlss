#include "runtime/high_state.h"

#define SEC(name) __attribute__((section(".text.high." #name)))

int sub_81DA690(s16 first, s16 second);
void sub_819AC84(u32 channel);
void sub_819AF18(void);
void sub_819B31C(void);
void sub_819B864(void);

SEC(sub_8199480) u8 runtime_calculate_packed_byte(s16 first, s16 second)
{
    return (sub_81DA690(first, second) << 16) >> 24;
}
SEC(sub_8199480) const u16 runtime_calculate_packed_byte_padding = 0;

SEC(sub_819A6A8) void runtime_tick_latched_value_16(
    struct RuntimeLatchedState* state,
    const struct RuntimeLatchCallbacks* callbacks)
{
    if (state->countdown17 != 0) {
        state->countdown17--;
    } else {
        state->countdown17 = state->period15;
        if (state->flags & 0x1000) {
            state->flags ^= 0x2000;
            callbacks->toggleValue16(state);
        } else {
            state->flags |= 0x1000;
        }
    }
}

SEC(sub_819A6EC) s32 runtime_get_latched_value_16_delta(
    const struct RuntimeLatchedState* state)
{
    s32 result;
    if (state->flags & 0x1000) {
        if (state->flags & 0x2000) {
            result = -state->magnitude14;
            goto done;
        }
        result = state->magnitude14;
        goto done;
    }
    result = 0;
done:
    return result;
}
SEC(sub_819A6EC) const u16 runtime_get_latched_value_16_delta_padding = 0;

SEC(sub_819A72C) void runtime_tick_latched_value_1a(
    struct RuntimeLatchedState* state,
    const struct RuntimeLatchCallbacks* callbacks)
{
    if (state->countdown1B != 0) {
        state->countdown1B--;
    } else {
        state->countdown1B = state->period19;
        if (state->flags & 0x0200) {
            state->flags ^= 0x0400;
            callbacks->toggleValue1A(state);
        } else {
            state->flags |= 0x0200;
        }
    }
}

SEC(sub_819A770) s32 runtime_get_latched_value_1a_delta(
    const struct RuntimeLatchedState* state)
{
    s32 result;
    if (state->flags & 0x0200) {
        if (state->flags & 0x0400) {
            result = -state->magnitude18;
            goto done;
        }
        result = state->magnitude18;
        goto done;
    }
    result = 0;
done:
    return result;
}
SEC(sub_819A770) const u16 runtime_get_latched_value_1a_delta_padding = 0;

SEC(sub_819AF88) void runtime_refresh_display_channels(void)
{
    sub_819AC84(0);
    sub_819AC84(1);
    sub_819AF18();
    sub_819AC84(3);
}

SEC(sub_819B040) void runtime_display_entry_initialize(
    struct RuntimeDisplayEntry* entry, const void* definition)
{
    entry->flags = 0x83;
    entry->definition = definition;
    entry->value08 = 0;
    entry->value02 = 0x78;
    entry->value03 = 0;
    entry->value0C = 0;
    entry->value0E = 0x7F;
    entry->value0A = 1;
    entry->value0D = 0xC8;
    entry->value10 = 0;
    entry->value0F = 2;
    entry->value11 = 0;
}

SEC(sub_819B95C) void runtime_refresh_display_state(void)
{
    sub_819B31C();
    sub_819B864();
    sub_819AF88();
}
SEC(sub_819B95C) const u16 runtime_refresh_display_state_padding = 0;


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
    state->countdown17 = state->value16;
}

SEC(sub_819A718) void sub_819A718(struct RuntimeLatchedState* state)
{
    state->flags &= 0xF9FF;
    state->countdown1B = state->value1A;
}
