#include "ui/functions.h"
#include "ui/object.h"
#include "common.h"

#define DEFINE_SPRITE_PAIR_ACTION(name, sectionName, action)                   \
    void name(struct UiSpritePair* object)                                     \
        __attribute__((section(sectionName)));                                 \
    void name(struct UiSpritePair* object)                                     \
    {                                                                          \
        struct Sprite* sprite = object->firstSprite;                            \
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

#define UNSET_SPRITE_PARAMETER -1

void ui_sprite_pair_create_second_sprite(
    struct UiSpritePair* object, s32 kind, s32 packedPosition, s32 priority,
    s32 animationId, u32 attributePair)
    __attribute__((section(".text.ui_sprite_pair.sub_8163A80")));
void ui_sprite_pair_create_second_sprite(
    struct UiSpritePair* object, s32 kind, s32 packedPosition, s32 priority,
    s32 animationId, u32 attributePair)
{
    object->secondSprite = sub_8020DD0(
        kind, packedPosition, priority,
        UNSET_SPRITE_PARAMETER, UNSET_SPRITE_PARAMETER,
        UNSET_SPRITE_PARAMETER, UNSET_SPRITE_PARAMETER);

    sub_801E150(object->secondSprite, animationId,
                UNSET_SPRITE_PARAMETER, 0, 0);
    sprite_show_8020CBC(object->secondSprite);
    object->secondSprite->field_1F_0 = attributePair & 3;
    object->secondSprite->field_E = 0xFFFF;
}
