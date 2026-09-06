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
    u8 unknown05C[0x5C];
    u8 updateFlagB8;
    u8 unknown0B9[4];
    u8 layoutModeBD;
    u8 flagsBE;
};

void sub_80184F4(void* address);
void sub_8021FD4(void);
void free_heap_8018D9C(void* allocation);
void free_heap_8018DA8(void* allocation);
void sub_80FAFD8(void* loader, s32 flags);
void sub_81166AC(void* object, s32 flags);
void sub_8020A78(void);
void sub_8021F7C(void);
void sub_812E0D0(struct ShopScreenRuntime* screen);
s32 sub_812CF54(struct ShopScreenRuntime* screen, s32 displayState);

struct ShopDisplayState {
    u8 unknown000[0x880];
    s32 activeState880;
};

struct ShopDisplayWorkspace {
    u8 unknown000[0x3C];
    s32 callbackState3C;
};

extern struct ShopDisplayState gShopDisplayState __asm__("gGameState");
extern struct ShopDisplayWorkspace gShopDisplayWorkspace __asm__("stru_203FFB8");
extern void (*dword_3000D48)(s32 first, s32 second);
extern s32 (*dword_3000D4C)(s32 first, s32 second);

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

SEC(sub_812F4A0)
void shop_screen_child_update(struct Process* child)
{
    struct ShopScreenRuntime* screen =
        (struct ShopScreenRuntime*)child->parentProcess;
    s32 displayState = gShopDisplayState.activeState880;

    if (screen->process.state > 3) {
        if (screen->updateFlagB8 != 0)
            sub_812E0D0(screen);

        sub_8021F7C();
        sub_8020A78();
        dword_3000D48(
            gShopDisplayWorkspace.callbackState3C,
            gShopDisplayWorkspace.callbackState3C + 0xA14);
        displayState = dword_3000D4C(
            gShopDisplayWorkspace.callbackState3C, displayState);
        displayState = sub_812CF54(screen, displayState);
        gShopDisplayState.activeState880 = displayState;
    }
}
