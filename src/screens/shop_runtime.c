#include "global.h"
#include "process/process.h"
#include "screens/shop_runtime.h"

#define SEC(name) __attribute__((section(".text.upper." #name)))

struct ShopScreenRuntime {
    struct Process process;
    struct Process* childProcess1C;
    void* auxiliary20;
    void* resourceLoader24;
    void* workspace28;
    u8 unknown02C[0x0C];
    void* buffer38;
    u8 unknown03C[4];
    void* buffer40;
    void* buffer44;
    void* buffer48;
    void* buffer4C;
    void* buffer50;
    void* buffer54;
    void* buffer58;
    u8 unknown05C[0x61];
    u8 layoutModeBD;
    u8 flagsBE;
};

void sub_80184F4(void* address);
void sub_8021FD4(void);
void free_heap_8018D9C(void* allocation);
void free_heap_8018DA8(void* allocation);
void sub_80FAFD8(void* loader, s32 flags);
void sub_81166AC(void* object, s32 flags);

SEC(sub_812AA78)
void shop_screen_destroy(struct ShopScreenRuntime* screen, u32 flags)
{
    screen->process.definition = (struct ProcessDefinition*)0x08CDC3F8;
    {
        u16* work = (u16*)0x02000000;
        *work = 0;
        work += 0x24;
        *work = 0;
        work++;
        *work = 0;
        work += 3;
        *work = 0;
    }
    sub_80184F4((void*)0x0600D000);
    sub_8021FD4();

    if (screen->resourceLoader24 != 0)
        sub_80FAFD8(screen->resourceLoader24, 3);
    if (screen->buffer38 != 0)
        free_heap_8018D9C(screen->buffer38);

    if (screen->layoutModeBD == 0) {
        if (screen->buffer58 != 0)
            free_heap_8018D9C(screen->buffer58);
        if (screen->buffer54 != 0)
            free_heap_8018D9C(screen->buffer54);
        if (screen->buffer40 != 0)
            free_heap_8018D9C(screen->buffer40);
    } else if (screen->flagsBE & 1) {
        if (screen->buffer50 != 0)
            free_heap_8018D9C(screen->buffer50);
        if (screen->buffer4C != 0)
            free_heap_8018D9C(screen->buffer4C);
        if (screen->buffer48 != 0)
            free_heap_8018D9C(screen->buffer48);
        if (screen->buffer44 != 0)
            free_heap_8018D9C(screen->buffer44);
    } else {
        if (screen->buffer58 != 0)
            free_heap_8018D9C(screen->buffer58);
        if (screen->buffer40 != 0)
            free_heap_8018D9C(screen->buffer40);
    }

    free_heap_8018DA8(screen->workspace28);
    screen->workspace28 = 0;
    if (screen->auxiliary20 != 0)
        sub_81166AC(screen->auxiliary20, 3);
    screen->auxiliary20 = 0;
    if (screen->childProcess1C != 0)
        process_remove(screen->childProcess1C, 3);
    screen->childProcess1C = 0;
    process_remove(&screen->process, flags);
}
