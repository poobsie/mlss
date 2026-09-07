#ifndef GUARD_SCREENS_INDEXED_WORK_SCREEN_H
#define GUARD_SCREENS_INDEXED_WORK_SCREEN_H

#include "process/types.h"

struct FieldResourceLoaderProcess;

struct IndexedWorkScreen {
    struct Process process;
    u8 unknown01C[0x38];
    void* ownedBuffer54;
    u8 unknown058[0x100];
    struct Process* childProcess158;
    void* auxiliary15C;
    struct FieldResourceLoaderProcess* resourceLoader160;
};

#define indexed_work_screen_destroy sub_8125464
void indexed_work_screen_destroy(struct IndexedWorkScreen* screen, u32 flags);

#endif
