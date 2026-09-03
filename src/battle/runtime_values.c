#include "global.h"
#include "battle/functions.h"
#include "battle/object.h"

void battle_set_runtime_value_52c(struct BattleRuntimeValues* object, u32 value)
    __attribute__((section(".text.sub_8159904")));
void battle_set_runtime_value_52c(struct BattleRuntimeValues* object, u32 value) {
    object->value52C = value;
}

void battle_enable_runtime_value_514(struct BattleRuntimeValues* object, u16 value)
    __attribute__((section(".text.sub_8159984")));
void battle_enable_runtime_value_514(struct BattleRuntimeValues* object, u16 value) {
    object->enabled518 = 1;
    object->value514 = value;
}
