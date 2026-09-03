#include "global.h"

#define AT(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define SECTION(name) __attribute__((section(".text.field_configuration." #name)))

extern void sub_8047DC8(void *, u8);
extern void sub_801E150(void *, u8, s32, s32, s32);

SECTION(sub_8047E50) void sub_8047E50(void *object, s16 value)
{
    AT(object, s16, 0x26C) = value;
    AT(object, u8, 0x20E) |= 0x40;
    sub_8047DC8(object, AT(object, u8, 0x26E));
}

SECTION(sub_8047928) void sub_8047928(void *object)
{
    void *source = AT(object, void *, 0x294);
    sub_801E150(source, AT(source, u8, 0x21), 0, 0, 0);
}

__attribute__((section(".text.field_configuration.sub_8047928"))) const u16 field_configuration_padding = 0;
