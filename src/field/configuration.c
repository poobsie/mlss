#include "global.h"
#include "field/state.h"

#define SECTION(name) __attribute__((section(".text.field_configuration." #name)))

extern void sub_8047DC8(void *, u8);
extern void sub_801E150(void *, u8, s32, s32, s32);

SECTION(sub_8047E50) void sub_8047E50(struct FieldStateObject *object, s16 value)
{
    u8 flagValue;
    object->configurationValue = value;
    flagValue = object->flags20E;
    flagValue |= 0x40;
    object->flags20E = flagValue;
    sub_8047DC8(object, object->configurationSelector);
}

SECTION(sub_8047928) void sub_8047928(struct FieldStateObject *object)
{
    struct FieldConfigurationSource *source = object->configurationSource;
    sub_801E150(source, source->kind, 0, 0, 0);
}

__attribute__((section(".text.field_configuration.sub_8047928"))) const u16 field_configuration_padding = 0;
