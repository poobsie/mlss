#ifndef GUARD_RUNTIME_HIGH_STATE_H
#define GUARD_RUNTIME_HIGH_STATE_H

#include "global.h"

struct RuntimePointerSelection {
    u8 unknown00[4];
    void* selectedEntry;
};

struct RuntimeLatchedState {
    u16 flags;
    u8 unknown02[0x12];
    u8 magnitude14;
    u8 period15;
    u8 value16;
    u8 countdown17;
    u8 magnitude18;
    u8 period19;
    u8 value1A;
    u8 countdown1B;
};

struct RuntimeLatchCallbacks {
    u8 unknown00[8];
    void (*toggleValue16)(struct RuntimeLatchedState* state);
    u8 unknown0C[4];
    void (*toggleValue1A)(struct RuntimeLatchedState* state);
};

struct RuntimeDisplayEntry {
    u16 flags;
    u8 value02;
    u8 value03;
    const void* definition;
    u16 value08;
    u8 value0A;
    u8 unknown0B;
    u8 value0C;
    u8 value0D;
    u8 value0E;
    u8 value0F;
    u8 value10;
    u8 value11;
};

#define runtime_capture_vcount_byte sub_8199470
#define runtime_select_pointer_table_entry sub_8199D48
#define runtime_set_pointer_slot_1074 sub_8199F24
#define runtime_latch_value_16 sub_819A694
#define runtime_latch_value_1a sub_819A718
#define runtime_calculate_packed_byte sub_8199480
#define runtime_tick_latched_value_16 sub_819A6A8
#define runtime_get_latched_value_16_delta sub_819A6EC
#define runtime_tick_latched_value_1a sub_819A72C
#define runtime_get_latched_value_1a_delta sub_819A770
#define runtime_refresh_display_channels sub_819AF88
#define runtime_display_entry_initialize sub_819B040
#define runtime_refresh_display_state sub_819B95C

u8 runtime_capture_vcount_byte(u8* output);
u32 runtime_select_pointer_table_entry(struct RuntimePointerSelection* selection, u32 index);
void runtime_set_pointer_slot_1074(void* pointer);
void runtime_latch_value_16(struct RuntimeLatchedState* state);
void runtime_latch_value_1a(struct RuntimeLatchedState* state);
u8 runtime_calculate_packed_byte(s16 first, s16 second);
void runtime_tick_latched_value_16(struct RuntimeLatchedState* state,
                                  const struct RuntimeLatchCallbacks* callbacks);
s32 runtime_get_latched_value_16_delta(const struct RuntimeLatchedState* state);
void runtime_tick_latched_value_1a(struct RuntimeLatchedState* state,
                                  const struct RuntimeLatchCallbacks* callbacks);
s32 runtime_get_latched_value_1a_delta(const struct RuntimeLatchedState* state);
void runtime_refresh_display_channels(void);
void runtime_display_entry_initialize(struct RuntimeDisplayEntry* entry,
                                      const void* definition);
void runtime_refresh_display_state(void);

#endif
