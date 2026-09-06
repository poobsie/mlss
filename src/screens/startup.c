#include "common.h"
#include "screens/backup_clear.h"
#include "screens/startup.h"
#include "screens/title_screen.h"

#define SEC(name) __attribute__((section(".text.screens_startup." #name)))

SEC(sub_801B034)
void startup_create_initial_screen(void)
{
    if (gGameState.inputPressed == 0x307) {
        char* label = (char*)0x081E23A0;
        backup_clear_screen_create(alloc_Zero(0x4C, 0, label, 0), 8, label);
    } else {
        char* label = (char*)0x081E23A8;
        company_intro_create(alloc_Zero(0x4C, 0, label, 0), 8, label);
    }
}
