#include "global.h"
#include "battle/functions.h"
#include "battle/object.h"

void battle_effect_hide_sprite_and_reset(struct BattleEffectObject* object)
    __attribute__((section(".text.sub_815EC3C")));
void battle_effect_hide_sprite_and_reset(struct BattleEffectObject* object) {
    u8* sprite = (u8*)object->sprite;
    sprite[0x12] |= 0x20;
    ((u8*)object)[0x1A] = 0;
}
