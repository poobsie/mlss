#include "global.h"
#include "common.h"
#include "screens/backup_clear.h"

void backup_clear_render_process_update(void) {
    int value = gGameState.field_880;

    sub_8020A78();
    dword_3000D48(stru_203FFB8.field_3C, stru_203FFB8.field_3C + 0xA14);
    value = dword_3000D4C(stru_203FFB8.field_3C, value);
    gGameState.field_880 = value;
}

void backup_clear_screen_prepare_dialog(
    struct BackupClearScreen* backupClear, int width, int height) {
    int x = 15 - width / 2;
    int y = 10 - height / 2;

    window_animation_prepare(
        &backupClear->dialogWindow,
        backupClear->windowAnimationTilemap,
        x,
        y,
        width,
        height,
        0xE000);
    *(u8*)(*(u32*)0x0839EC80 + 0x4A) |= 0x10;
}
