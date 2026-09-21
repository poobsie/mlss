#include "battle/number_display.h"

#define SEC(name) \
    __attribute__((section(".text.battle_number_display." #name)))

extern void sub_8158258(struct BattleNumberDisplay* display);

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
