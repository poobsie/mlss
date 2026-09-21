#ifndef GUARD_UI_MOVING_SPRITE_H
#define GUARD_UI_MOVING_SPRITE_H

#include "common.h"
#include "ui/object.h"

struct UiMovingSpriteObject {
    u8 unknown00[0x0C];
    const struct UiObjectVtable* vtable;
    struct Sprite* primarySprite;
    struct Sprite* secondarySprite;
    s32 positionX;
    s32 positionYOffset;
    s32 positionY;
    u8 unknown24[0x48];
    union {
        s32 value;
        struct {
            u16 flags;
            u16 unknown6E;
        } halfwords;
    } valueAndFlags6C;
    s32 motionX70;
    union {
        s32 motionYOffset;
        s32 orbitBaseY;
    } value74;
    s32 motionY78;
    s32 value7C;
    union {
        s32 radiusX;
        s32 timer;
    } value80;
};

struct UiOrbitingSpriteObject {
    struct UiMovingSpriteObject base;
    s32 radiusY84;
};

#define ui_moving_sprite_check_proximity sub_816B230

s32 ui_moving_sprite_check_proximity(
    struct UiMovingSpriteObject* object,
    struct UiMovingSpriteObject* other);

#endif
