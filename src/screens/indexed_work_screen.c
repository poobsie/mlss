#include "screens/indexed_work_screen.h"

#include "field/resource_loader.h"
#include "memory/heap.h"
#include "process/process.h"

#define SCREEN_SEC(name) \
    __attribute__((section(".text.indexed_work_screen." #name)))

struct IndexedWorkGameState {
    u8 unknown000[0x888];
    u8 displayFlags888;
};

extern struct IndexedWorkGameState gIndexedWorkGameState
    __asm__("gGameState");

void sub_8021FD4(void);
void sub_81166AC(void* object, s32 flags);

SCREEN_SEC(sub_8125464)
void indexed_work_screen_destroy(struct IndexedWorkScreen* screen, u32 flags)
{
    volatile u16* workHeader;
    register int displayFlags asm("r0");
    register int mask asm("r1");

    screen->process.definition = (struct ProcessDefinition*)0x08CDC3B8;
    workHeader = (volatile u16*)0x02000000;
    *workHeader = 0;
    workHeader += 0x24;
    *workHeader = 0;
    workHeader++;
    *workHeader = 0;
    workHeader += 3;
    *workHeader = 0;

    mask = gIndexedWorkGameState.displayFlags888;
    displayFlags = -0x21;
    displayFlags &= mask;
    mask = -0x09;
    displayFlags &= mask;
    mask -= 0x38;
    displayFlags &= mask;
    gIndexedWorkGameState.displayFlags888 = displayFlags;

    if (screen->resourceLoader160 != 0)
        field_resource_loader_destroy(
            screen->resourceLoader160, 3);

    sub_8021FD4();
    if (screen->ownedBuffer54 != 0)
        free_heap_8018D9C(screen->ownedBuffer54);
    if (screen->auxiliary15C != 0)
        sub_81166AC(screen->auxiliary15C, 3);
    if (screen->childProcess158 != 0)
        process_remove(screen->childProcess158, 3);
    process_remove(&screen->process, flags);
}
