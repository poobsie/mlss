#include "battle/functions.h"
#include "battle/object.h"

void battle_tick_countdown_1f2a(struct BattleSceneRuntime* runtime)
    __attribute__((section(".text.text_late_helpers.sub_8158F60")));
void battle_tick_countdown_1f2a(struct BattleSceneRuntime* runtime) {
    --runtime->countdown1F2A;
    if (runtime->countdown1F2A < 0)
        runtime->value1F28 = 0;
}
