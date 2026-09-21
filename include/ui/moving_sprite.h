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
        s32 baseX;
        s32 state;
        struct {
            u16 flags;
            u16 unknown6E;
        } halfwords;
    } valueAndFlags6C;
    union {
        struct {
            s32 x;
            s32 yOffset;
            s32 y;
        } motion;
        struct {
            s32 unknown70;
            s32 baseY;
            s32 unknown78;
        } orbit;
    } values70;
    union {
        u32 directionIndex;
        s32 directionScale;
    } value7C;
    union {
        s32 radiusX;
        s32 timer;
    } value80;
};

struct UiOrbitingSpriteObject {
    struct UiMovingSpriteObject base;
    s32 radiusY;
};

#define ui_moving_sprite_update_orbit_target sub_816B1A8
#define ui_moving_sprite_check_proximity sub_816B230
#define ui_moving_sprite_begin_relative_motion sub_816B288

void ui_moving_sprite_update_orbit_target(
    struct UiOrbitingSpriteObject* object);

s32 ui_moving_sprite_check_proximity(
    struct UiMovingSpriteObject* object,
    struct UiMovingSpriteObject* other);
void ui_moving_sprite_begin_relative_motion(
    struct UiMovingSpriteObject* object,
    struct UiMovingSpriteObject* reference);

#endif
