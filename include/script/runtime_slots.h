#ifndef GUARD_SCRIPT_RUNTIME_SLOTS_H
#define GUARD_SCRIPT_RUNTIME_SLOTS_H

#include "global.h"

struct ScriptRuntimeSlotSprite {
    u16 coordinateX;
    u16 coordinateY;
    u8 unknown04[0x0A];
    u16 invertedCoordinateY;
};

struct ScriptRuntimeSlot {
    struct ScriptRuntimeSlotSprite* sprite;
    u16 baseX;
    u16 baseY;
    u16 offsetX;
    u16 offsetY;
    u8 identifier;
    u8 hideTimer;
    u8 unknown0E;
    u8 active;
};

struct ScriptRuntimeSlotOwner {
    struct ScriptRuntimeSlot* slots;
};

#define script_runtime_slot_hide sub_80E8EE0

void script_runtime_slot_hide(struct ScriptRuntimeSlotOwner* owner, u8 slot);

#endif
