#ifndef GUARD_MARIO_BROS_COMMAND_CONTEXT_H
#define GUARD_MARIO_BROS_COMMAND_CONTEXT_H

#include "global.h"

struct MarioBrosCommandContext {
    u8 unknown00[0x1E];
    u8 byte1E;
    u8 byte1F;
    u8 unknown20[4];
    u8 byte24;
    u8 unknown25;
    u8 byte26;
    u8 byte27;
    u8 unknown28[4];
    u8 byte2C;
    u8 byte2D;
    u8 byte2E;
    u8 byte2F;
    u8 unknown30[0x10];
    const u8* cursor;
};

#endif
