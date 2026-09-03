#ifndef GUARD_MARIO_BROS_RUNTIME_H
#define GUARD_MARIO_BROS_RUNTIME_H

#include "global.h"

struct MarioBrosEventSource {
    u8 unknown00[8];
    void* eventArgument;
};

struct MarioBrosRuntimeRoot {
    u8 unknown00[0x54];
    struct MarioBrosEventSource* eventSource;
};

struct MarioBrosRuntime {
    u8 unknown0000[0xC5A];
    u8 sequenceIndex;
    u8 unknown0C5B[0x3821];
    struct MarioBrosRuntimeRoot* root;
};

extern struct MarioBrosRuntime gMarioGlobal_03000F50;

#endif
