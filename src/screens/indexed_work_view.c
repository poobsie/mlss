#include "screens/indexed_work_view.h"

#include "field/resource_loader.h"
#include "memory/heap.h"
#include "process/process.h"

#define VIEW_SEC(name) \
    __attribute__((section(".text.indexed_work_view." #name)))

struct IndexedWorkViewGameState {
    u8 unknown000[0x888];
    u8 displayFlags888;
};

extern struct IndexedWorkViewGameState gIndexedWorkViewGameState
    __asm__("gGameState");

void sub_8021FD4(void);
void sub_81166AC(void* object, s32 flags);

VIEW_SEC(sub_8127FC4)
void indexed_work_view_destroy(struct IndexedWorkView* view, u32 flags)
{
    volatile u16* workHeader;
    register int displayFlags asm("r0");
    register int mask asm("r1");

    view->process.definition = (struct ProcessDefinition*)0x08CDC3D8;
    workHeader = (volatile u16*)0x02000000;
    *workHeader = 0;
    workHeader += 0x24;
    *workHeader = 0;
    workHeader++;
    *workHeader = 0;
    workHeader += 3;
    *workHeader = 0;

    mask = gIndexedWorkViewGameState.displayFlags888;
    displayFlags = -0x21;
    displayFlags &= mask;
    mask = -0x09;
    displayFlags &= mask;
    mask -= 0x38;
    displayFlags &= mask;
    gIndexedWorkViewGameState.displayFlags888 = displayFlags;

    if (view->resourceLoader24 != 0)
        field_resource_loader_destroy(view->resourceLoader24, 3);
    sub_8021FD4();
    if (view->ownedBufferC8 != 0)
        free_heap_8018D9C(view->ownedBufferC8);
    if (view->auxiliary20 != 0)
        sub_81166AC(view->auxiliary20, 3);
    if (view->childProcess1C != 0)
        process_remove(view->childProcess1C, 3);
    process_remove(&view->process, flags);
}
