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
