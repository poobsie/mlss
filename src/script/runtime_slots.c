#include "script/runtime_slots.h"

#include "common.h"

#define SEC(symbol) \
    __attribute__((section(".text.script_runtime_slots." #symbol)))

SEC(sub_80E8EE0)
void script_runtime_slot_hide(struct ScriptRuntimeSlotOwner* owner, u8 slot)
{
    struct ScriptRuntimeSlot* entry = &owner->slots[slot];

    sprite_hide_8021F20((struct Sprite*)entry->sprite);
    entry->active = 0;
}

SEC(sub_80E8EE0)
const u16 script_runtime_slot_hide_padding = 0;

SEC(sub_80E9310)
u32 script_runtime_read_indexed_pair(void* context, const u8* const* table)
{
    struct ScriptRuntimeTableSelector {
        u8 unknown000[0x8C0];
        u8 index;
    };
    const u8* entry;
    u8 index = ((struct ScriptRuntimeTableSelector*)&gGameState)->index;

    (void)context;
    entry = table[index];
    return (entry[0] << 16) | entry[1];
}
