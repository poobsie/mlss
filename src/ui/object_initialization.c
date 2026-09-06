#include "common.h"

#define SEC(name) __attribute__((section(".text.ui_object_init." #name)))
struct UiIntroSpriteMotion {
    struct Sprite* sprite;
    s32 phase;
    u32 state;
    s32 delay;
};

SEC(sub_8161A58)
struct UiIntroSpriteMotion* sub_8161A58(struct UiIntroSpriteMotion* motion) {
    motion->sprite = sub_8020DD0(4, 0x5005, 1, -1, -1, -1, -1);
    sub_801E150(motion->sprite, 0x21, -1, 0, 0);
    sprite_show_8020CBC(motion->sprite);
    motion->sprite->xPosition = 0x78;
    motion->sprite->yPosition = 0x50;
    motion->delay = 0;
    motion->phase = 0x100;
    motion->state = 0;
    return motion;
}
