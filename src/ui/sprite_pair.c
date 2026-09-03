#include "ui/functions.h"
#include "ui/object.h"

void sprite_hide_8021F20(void* sprite);
void sprite_show_8020CBC(void* sprite);

#define DEFINE_SPRITE_PAIR_ACTION(name, sectionName, action)                   \
    void name(struct UiSpritePair* object)                                     \
        __attribute__((section(sectionName)));                                 \
    void name(struct UiSpritePair* object)                                     \
    {                                                                          \
        void* sprite = object->firstSprite;                                     \
        if (sprite != 0)                                                        \
            action(sprite);                                                     \
        sprite = object->secondSprite;                                          \
        if (sprite != 0)                                                        \
            action(sprite);                                                     \
    }                                                                          \
    __attribute__((section(sectionName))) const u16 name##_padding = 0;

DEFINE_SPRITE_PAIR_ACTION(ui_sprite_pair_hide,
                          ".text.child_actions.sub_8163A24",
                          sprite_hide_8021F20)
DEFINE_SPRITE_PAIR_ACTION(ui_sprite_pair_show,
                          ".text.child_actions.sub_8163A44",
                          sprite_show_8020CBC)
