#include "global.h"
#include "battle/functions.h"
#include "battle/object.h"

void sub_8021308(void* resource);
void free_heap_8018DA8(void* object);

void battle_effect_hide_sprite_and_reset(struct BattleEffectObject* object)
    __attribute__((section(".text.sub_815EC3C")));
void battle_effect_hide_sprite_and_reset(struct BattleEffectObject* object) {
    u8* sprite = (u8*)object->sprite;
    sprite[0x12] |= 0x20;
    ((u8*)object)[0x1A] = 0;
}

#define EFFECT_SEC(name) __attribute__((section(".text.battle_effect_leaf." #name)))

EFFECT_SEC(sub_815EC8C)
s32 sub_815EC8C(struct BattleEffectObject* object) {
    return object->value18;
}
EFFECT_SEC(sub_815EC8C) const u16 sub_815EC8C_padding = 0;

void battle_destroy_resource_quad(struct BattleResourceQuadOwner* object, s32 flags)
    __attribute__((section(".text.sub_815ECA8")));
void battle_destroy_resource_quad(struct BattleResourceQuadOwner* object, s32 flags) {
    if (object->resources[0] != 0)
        sub_8021308(object->resources[0]);
    if (object->resources[1] != 0)
        sub_8021308(object->resources[1]);
    if (object->resources[2] != 0)
        sub_8021308(object->resources[2]);
    sub_8021308(object->resources[3]);
    if (flags & 1)
        free_heap_8018DA8(object);
}

__attribute__((section(".text.sub_815ECA8")))
const u16 battle_destroy_resource_quad_padding = 0;
