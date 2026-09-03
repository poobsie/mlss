#include "ui/visibility.h"

void sprite_hide_8021F20(void* sprite);
void sprite_show_8020CBC(void* sprite);

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

SEC(sub_81218C8) void ui_hide_owned_sprite(struct UiSingleSpriteOwner* owner)
{
    sprite_hide_8021F20(owner->sprite);
}

SEC(sub_81218D4) void ui_show_owned_sprite(struct UiSingleSpriteOwner* owner)
{
    sprite_show_8020CBC(owner->sprite);
}

SEC(sub_81218E0) int ui_visibility_callback_false(void)
{
    return 0;
}
