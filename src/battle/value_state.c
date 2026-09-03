#include "battle/functions.h"
#include "battle/object.h"

void battle_clear_value_14(struct BattleValueObject* object)
    __attribute__((section(".text.sub_8158E10")));
void battle_clear_value_14(struct BattleValueObject* object) {
    object->value14 = 0;
}

__attribute__((section(".text.sub_8158E10")))
const u16 sub_8158E10_padding = 0;
