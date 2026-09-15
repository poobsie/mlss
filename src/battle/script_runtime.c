#include "battle/script_runtime.h"
#include "battle/functions.h"
#include "battle/object.h"

#define BATTLE_SCRIPT_RUNTIME (*(struct BattleScriptRuntime**)0x03000FD0)

#define BATTLE_SCRIPT_SECTION(symbol) \
    __attribute__((section(".text.battle_script_runtime." #symbol)))

BATTLE_SCRIPT_SECTION(sub_80F03C8)
void battle_script_update_root_channel(struct BattleScriptProcess* process)
{
    struct BattleScriptRuntime* runtime = BATTLE_SCRIPT_RUNTIME;
    struct ScriptExecutionState* channel = &runtime->rootChannel1F8;
    u16* flags = &runtime->rootChannel1F8.primaryFlags;

    if ((*flags & 0x100) &&
        (u8)sub_8028E70(process->data->control14) == 0) {
        *flags ^= 0x100;
    }

    if (channel->primaryFlags & 0x10) {
        script_state_tick_wait_timer(
            &process->data->commandContext1C, channel);
    }
}
