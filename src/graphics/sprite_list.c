#include "common.h"

#define SEC(name) __attribute__((section(".text." #name)))

void sub_801E68C(struct Sprite* sprite);
void sub_8021308(struct Sprite* sprite);

#define sprite_update_active_list sub_8021F7C

SEC(sub_8021F7C)
void sprite_update_active_list(void)
{
    struct Sprite* sprite = stru_203FFB8.firstActiveSprite;

    while (sprite != 0) {
        struct Sprite* next = sprite->nextActive;

        if (sprite->updateFlags29 & 0x40) {
            sub_801E68C(sprite);
            if (sprite->field_12_3) {
                if (sprite->field_12_1 == 2)
                    sprite_hide_8021F20(sprite);
                else if (sprite->field_12_1 == 3)
                    sub_8021308(sprite);
            }
        }
        sprite = next;
    }
}
SEC(sub_8021F7C)
const u16 sprite_update_active_list_padding = 0;
