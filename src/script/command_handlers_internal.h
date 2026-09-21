#ifndef GUARD_SCRIPT_COMMAND_HANDLERS_INTERNAL_H
#define GUARD_SCRIPT_COMMAND_HANDLERS_INTERNAL_H

#include "global.h"

struct ScriptObjectSelectionContext {
    u8 unknown00[0x2C];
    u8* fieldState2C;
};

void sub_80E9C4C(void*, void*, void*, s32, s32, s32);

#endif
