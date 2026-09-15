#ifndef GUARD_BATTLE_SCRIPT_RUNTIME_H
#define GUARD_BATTLE_SCRIPT_RUNTIME_H

#include "global.h"
#include "script/execution_state.h"

struct BattleControlObject;

struct BattleScriptRuntime {
    u8 unknown000[0x1F8];
    struct ScriptExecutionState rootChannel1F8;
};

struct BattleScriptProcessData {
    u8 unknown00[0x14];
    struct BattleControlObject* control14;
    u8 unknown18[4];
    u8 commandContext1C;
};

struct BattleScriptProcess {
    struct BattleScriptProcessData* data;
};

#define battle_script_update_root_channel sub_80F03C8

void battle_script_update_root_channel(struct BattleScriptProcess* process);

#endif
