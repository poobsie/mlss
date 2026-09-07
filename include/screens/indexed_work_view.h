#ifndef GUARD_SCREENS_INDEXED_WORK_VIEW_H
#define GUARD_SCREENS_INDEXED_WORK_VIEW_H

#include "process/types.h"

struct FieldResourceLoaderProcess;

struct IndexedWorkView {
    struct Process process;
    struct Process* childProcess1C;
    void* auxiliary20;
    struct FieldResourceLoaderProcess* resourceLoader24;
    u8 unknown028[0xA0];
    void* ownedBufferC8;
};

#define indexed_work_view_destroy sub_8127FC4
void indexed_work_view_destroy(struct IndexedWorkView* view, u32 flags);

#endif
