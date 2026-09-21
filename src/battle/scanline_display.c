#include "global.h"
#include "gba/io_reg.h"

enum {
    BATTLE_SCANLINE_COUNT = 228,
};

struct BattleScanlineTables {
    u16 unknown00[2];
    u16 windowBounds[BATTLE_SCANLINE_COUNT];
    u16 backdropColors[BATTLE_SCANLINE_COUNT];
};

struct BattleDisplayRuntime {
    u8 unknown0000[0x1CC4];
    u16 displayFlags1CC4;
};

#define BG_PALETTE0 (*(volatile u16*)0x05000000)
#define BATTLE_SCANLINE_TABLES \
    ((struct BattleScanlineTables*)*(volatile u32*)0x03001014)
#define BATTLE_DISPLAY_RUNTIME \
    ((struct BattleDisplayRuntime*)*(volatile u32*)0x03001018)
#define battle_apply_current_scanline_state sub_815928C

__attribute__((section(".text.battle_scanline.sub_815928C")))
void battle_apply_current_scanline_state(void)
{
    u16 scanline = REG_VCOUNT;
    volatile u16* displayRegister = (volatile u16*)REG_ADDR_BG2HOFS;
    struct BattleScanlineTables* tables;

    *displayRegister = 0;
    displayRegister++;
    *displayRegister = 128 - scanline;
    displayRegister += (REG_OFFSET_WIN0H - REG_OFFSET_BG2VOFS) / 2;
    tables = BATTLE_SCANLINE_TABLES;
    *displayRegister = tables->windowBounds[scanline];
    if (!(BATTLE_DISPLAY_RUNTIME->displayFlags1CC4 & 4))
        BG_PALETTE0 = tables->backdropColors[scanline];
}
