#ifndef GUARD_SCRIPT_COMMAND_CONTEXT_H
#define GUARD_SCRIPT_COMMAND_CONTEXT_H

#include "global.h"

enum {
    SCRIPT_OBJECT_SLOT_183 = 183,
    SCRIPT_OBJECT_SLOT_COUNT = 184,
};

struct ScriptObjectRegistry {
    u8 unknown00[0x28];
    void* objects[SCRIPT_OBJECT_SLOT_COUNT];
};

struct ScriptCommandContext {
    u8 unknown00[0x14];
    struct ScriptObjectRegistry* objectRegistry;
};

/* Preserve the original address calculation order required by agbcc. */
#define SCRIPT_OBJECT_AT(registry, index) \
    (((struct ScriptObjectRegistry*)((u8*)(registry) + (index) * sizeof(void*)))->objects[0])

#endif
