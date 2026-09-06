#ifndef GUARD_GRAPHICS_SPRITE_VISIBILITY_H
#define GUARD_GRAPHICS_SPRITE_VISIBILITY_H

#include "global.h"

#define graphics_refresh_sprite_visibility sub_813489C
#define graphics_refresh_sprite_visibility_callback sub_81348BC
#define graphics_release_visibility_sprite sub_8134928
#define graphics_release_owned_sprite sub_8134940
#define graphics_initialize_sprite_visibility_controller sub_81349CC
#define graphics_destroy_sprite_visibility_controller sub_8134A14

struct SpriteVisibilityController {
    u32 unknown00;
    u32 unknown04;
    void* ownedSprite08;
    void* visibilitySprite0C;
    const void* resourceTable10;
    const void* resourceTable14;
    u32 unknown18;
    s8 selection1C;
    u8 visualId1D;
    u16 unknown1E;
    u16 unknown20;
    u8 unknown22;
    u8 unknown23;
    u8 unknown24;
    u8 unknown25[3];
    u32 unknown28;
    u32 unknown2C;
    u32 unknown30;
    s32 comparisonValue34;
    u8 unknown38[8];
    const void* descriptor40;
};

s32 graphics_refresh_sprite_visibility(
    struct SpriteVisibilityController* controller);
s32 graphics_refresh_sprite_visibility_callback(
    struct SpriteVisibilityController* controller);
void graphics_release_visibility_sprite(
    struct SpriteVisibilityController* controller);
void graphics_release_owned_sprite(
    struct SpriteVisibilityController* controller);
void graphics_initialize_sprite_visibility_controller(
    struct SpriteVisibilityController* controller);
void graphics_destroy_sprite_visibility_controller(
    struct SpriteVisibilityController* controller, u32 flags);

#endif
