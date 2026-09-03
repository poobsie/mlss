#ifndef GUARD_SCRIPT_COMMAND_HANDLERS_H
#define GUARD_SCRIPT_COMMAND_HANDLERS_H

#include "global.h"

struct ScriptBattleReturnContext;

#define script_command_return_from_battle script_cmd_btl_return

u8 script_command_return_from_battle(
    struct ScriptBattleReturnContext* context,
    s32 state,
    s32* shouldMarkReturn);

#endif
