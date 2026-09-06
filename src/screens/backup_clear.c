#include "global.h"
#include "buffer_io_reg.h"
#include "common.h"
#include "process/process.h"
#include "screens/backup_clear.h"

#define SEC(name) __attribute__((section(".text.backup_clear." #name)))

SEC(destroy)
void backup_clear_screen_destroy(struct BackupClearScreen* backupClear, u32 flags)
{
    backupClear->process.definition = &gBackupClearScreenProcessDefinition;
    if (backupClear->renderProcess != 0)
        process_remove(backupClear->renderProcess, 3);
    if (backupClear->windowAnimationTilemap != 0)
        free_heap_8018D9C(backupClear->windowAnimationTilemap);
    if (backupClear->graphicsWorkAllocation != 0)
        free_heap_8018D9C(backupClear->graphicsWorkAllocation);
    if (backupClear->dialogTilemaps != 0)
        free_heap_8018D9C(backupClear->dialogTilemaps);
    if (backupClear->textEngineCode != 0)
        free_heap_8018D9C(backupClear->textEngineCode);
    free_heap_8018DA8(backupClear->textContext);

    sub_8021FD4();
    gGameState.field_888_5 = 0;
    gGameState.field_888_6 = 0;
    gGameState.field_888_3 = 0;
    gGameState.field_31 = 2;
    BUFFER_REG_DISPCNT = 0;
    BUFFER_REG_BLDCNT = 0;
    process_remove(&backupClear->process, flags);
}
