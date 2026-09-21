#include "battle/number_display.h"

#define SEC(name) \
    __attribute__((section(".text.battle_number_display." #name)))

extern void sub_8158258(struct BattleNumberDisplay* display);

typedef void* (*BattleWorkspaceAllocate)(u32 size);

#define BATTLE_WORKSPACE_ALLOCATE (*(BattleWorkspaceAllocate*)0x03001038)

SEC(sub_8158220)
struct BattleNumberDisplay* battle_number_display_initialize(
    struct BattleNumberDisplay* display)
{
    u32 digitCount = 30;

    display->displayedValue = digitCount;
    display->positionX = 0;
    display->positionY = 0x3C00;
    display->digitWorkspace =
        BATTLE_WORKSPACE_ALLOCATE((digitCount * 15) << 12);
    display->value.packed = 0;
    display->tens.sprite = 0;
    display->hundreds.lowHandle = 0;
    display->ones.lowHandle = 0;
    return display;
}

SEC(sub_81582CC)
void battle_number_display_adjust_value(
    struct BattleNumberDisplay* display, s16 adjustment)
{
    u16 adjustmentBits = adjustment;
    s32 value = display->displayedValue + adjustment;

    if (value < 0)
        value = 0;
    display->displayedValue = value;

    if ((s16)adjustmentBits < 0) {
        display->adjustmentTimer = 100;
        display->adjustmentDirection = 1;
    } else if ((s16)adjustmentBits > 0) {
        display->adjustmentTimer = 100;
        display->adjustmentDirection = 2;
    }
    sub_8158258(display);
}
