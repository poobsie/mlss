#include "global.h"
#include "field/random_tier.h"

void sub_81059D8(u32 identifier, u32 tier);
s32 sub_8199F30(void);
u32 sub_81DD77C(u32 limit, s32 value);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_8106928) void field_apply_random_200_tier(void)
{
    u32 value;
    u32 tier;

    value = sub_81DD77C(0x64, sub_8199F30());
    tier = ~value >> 31;
    if ((s32)value > 0x5B)
        tier += 1;
    if ((s32)value > 0x61)
        tier += 1;
    sub_81059D8(0x200, tier);
}
