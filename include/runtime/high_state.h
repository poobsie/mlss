#ifndef GUARD_RUNTIME_HIGH_STATE_H
#define GUARD_RUNTIME_HIGH_STATE_H

#include "global.h"

struct RuntimePointerSelection {
    u8 unknown00[4];
    void* selectedEntry;
};

struct RuntimeLatchedState {
    u16 flags;
    u8 unknown02[0x14];
    u8 value16;
    u8 latchedValue16;
    u8 unknown18[2];
    u8 value1A;
    u8 latchedValue1A;
};

#define runtime_capture_vcount_byte sub_8199470
#define runtime_select_pointer_table_entry sub_8199D48
#define runtime_set_pointer_slot_1074 sub_8199F24
#define runtime_latch_value_16 sub_819A694
#define runtime_latch_value_1a sub_819A718

u8 runtime_capture_vcount_byte(u8* output);
u32 runtime_select_pointer_table_entry(struct RuntimePointerSelection* selection, u32 index);
void runtime_set_pointer_slot_1074(void* pointer);
void runtime_latch_value_16(struct RuntimeLatchedState* state);
void runtime_latch_value_1a(struct RuntimeLatchedState* state);

#endif
