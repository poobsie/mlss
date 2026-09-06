#include "graphics/sprite_visibility.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))

void sub_8134560(void);
void sub_81345E8(
    struct SpriteVisibilityController* controller, s32 value, s32 mode);
void sub_813481C(struct SpriteVisibilityController* controller);
void sub_8021308(void* sprite);
void free_heap_8018DA8(void* allocation);
extern const u8 gUnknown_0821253C[];
extern const u8 gUnknown_08212544[];

SEC(graphics_refresh_sprite_visibility)
s32 graphics_refresh_sprite_visibility(
    struct SpriteVisibilityController* controller)
{
    sub_8134560();
    sub_813481C(controller);
    sub_81345E8(controller, 0, 0);
    return 0;
}

SEC(graphics_refresh_sprite_visibility_callback)
s32 graphics_refresh_sprite_visibility_callback(
    struct SpriteVisibilityController* controller)
{
    return graphics_refresh_sprite_visibility(controller);
}
SEC(graphics_refresh_sprite_visibility_callback)
const u16 graphics_refresh_sprite_visibility_callback_padding = 0;

SEC(graphics_release_visibility_sprite)
void graphics_release_visibility_sprite(
    struct SpriteVisibilityController* controller)
{
    if (controller->visibilitySprite0C != 0) {
        sub_8021308(controller->visibilitySprite0C);
        controller->visibilitySprite0C = 0;
    }
}

SEC(graphics_release_owned_sprite)
void graphics_release_owned_sprite(
    struct SpriteVisibilityController* controller)
{
    if (controller->ownedSprite08 != 0) {
        sub_8021308(controller->ownedSprite08);
        controller->ownedSprite08 = 0;
    }
}

SEC(graphics_initialize_sprite_visibility_controller)
void graphics_initialize_sprite_visibility_controller(
    struct SpriteVisibilityController* controller)
{
    controller->unknown00 = 0;
    controller->unknown04 = 0;
    controller->ownedSprite08 = 0;
    controller->visibilitySprite0C = 0;
    controller->resourceTable10 = gUnknown_0821253C;
    controller->resourceTable14 = gUnknown_08212544;
    controller->unknown18 = 0;
    controller->unknown20 = 0;
    controller->unknown1E = 0;
    controller->visualId1D = 0xFF;
    controller->selection1C = -1;
    controller->unknown24 = 0;
    controller->unknown28 = 0;
    controller->unknown2C = 0;
    controller->unknown30 = 0;
    controller->comparisonValue34 = 0;
    controller->unknown22 = 0;
    controller->unknown23 = 0;
}

SEC(graphics_destroy_sprite_visibility_controller)
void graphics_destroy_sprite_visibility_controller(
    struct SpriteVisibilityController* controller, u32 flags)
{
    controller->descriptor40 = (const void*)0x08CDC448;
    graphics_release_owned_sprite(controller);
    graphics_release_visibility_sprite(controller);
    if (flags & 1)
        free_heap_8018DA8(controller);
}
