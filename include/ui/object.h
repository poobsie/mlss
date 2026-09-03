#ifndef GUARD_UI_OBJECT_H
#define GUARD_UI_OBJECT_H

#include "global.h"

struct UiObject {
    u8 unknown00[0x18];
    u32 value18;
    u32 value1C;
    u32 value20;
    u8 unknown24[0x1C];
    u32 state40;
    void* value44;
    u16 counter48;
};

struct UiSpritePair {
    u8 unknown00[0x10];
    void* firstSprite;
    void* secondSprite;
};

#endif
