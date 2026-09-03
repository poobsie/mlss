#ifndef GUARD_SCREENS_BACKUP_CLEAR_H
#define GUARD_SCREENS_BACKUP_CLEAR_H

#include "process/types.h"
#include "screens/options.h"

struct Sprite;
struct struc_15;

enum BackupClearScreenState {
    BACKUP_CLEAR_STATE_OPEN_INITIAL_PROMPT,
    BACKUP_CLEAR_STATE_CONFIRM,
    BACKUP_CLEAR_STATE_OPEN_RESULT,
    BACKUP_CLEAR_STATE_WRITE_BACKUP,
    BACKUP_CLEAR_STATE_WRITE_ERROR,
    BACKUP_CLEAR_STATE_CLOSE,
};

struct BackupClearScreen {
    struct Process process;
    u8 confirmClear : 1;
    u8 unknownFlags : 7;
    u8 phaseTimer;
    u8 padding1[2];
    u8* graphicsWorkAllocation;
    u8* messageTiles;
    u16* dialogTilemaps;
    int* textEngineCode;
    struct struc_15* textContext;
    struct Process* renderProcess;
    int* windowAnimationTilemap;
    u16 writeProgress;
    u8 padding2[2];
    struct WindowAnimation dialogWindow;
    u8 padding3[2];
    struct Sprite* cursor;
};

extern struct ProcessDefinition gBackupClearScreenProcessDefinition __asm__("stru_8CDC1D8");
extern struct ProcessDefinition gBackupClearRenderProcessDefinition __asm__("stru_8CDC1E8");

struct BackupClearScreen* backup_clear_screen_create(
    struct BackupClearScreen* backupClear,
    u8 priority,
    char* label);
void backup_clear_screen_update(struct BackupClearScreen* backupClear);
void backup_clear_screen_destroy(struct BackupClearScreen* backupClear, u32 flags);
void backup_clear_render_process_update(void);
void backup_clear_screen_prepare_dialog(
    struct BackupClearScreen* backupClear,
    int width,
    int height);

#endif
