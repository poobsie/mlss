#ifndef GUARD_GRAPHICS_SPRITE_VISIBILITY_H
#define GUARD_GRAPHICS_SPRITE_VISIBILITY_H

#include "global.h"

#define graphics_refresh_sprite_visibility sub_813489C
#define graphics_release_visibility_sprite sub_8134928

struct SpriteVisibilityController {
    u8 unknown00[0x0C];
    void* sprite0C;
    u8 unknown10[0x24];
    s32 comparisonValue34;
};

s32 graphics_refresh_sprite_visibility(
    struct SpriteVisibilityController* controller);
void graphics_release_visibility_sprite(
    struct SpriteVisibilityController* controller);

#endif
