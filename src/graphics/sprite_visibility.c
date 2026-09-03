#include "graphics/sprite_visibility.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))

void sub_8134560(void);
void sub_81345E8(
    struct SpriteVisibilityController* controller, s32 value, s32 mode);
void sub_813481C(struct SpriteVisibilityController* controller);
void sub_8021308(void* sprite);

SEC(graphics_refresh_sprite_visibility)
s32 graphics_refresh_sprite_visibility(
    struct SpriteVisibilityController* controller)
{
    sub_8134560();
    sub_813481C(controller);
    sub_81345E8(controller, 0, 0);
    return 0;
}

SEC(graphics_release_visibility_sprite)
void graphics_release_visibility_sprite(
    struct SpriteVisibilityController* controller)
{
    if (controller->sprite0C != 0) {
        sub_8021308(controller->sprite0C);
        controller->sprite0C = 0;
    }
}
