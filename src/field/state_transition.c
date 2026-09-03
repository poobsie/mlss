#include "global.h"
#include "field/functions.h"
#include "field/state.h"

#define SECTION(name) __attribute__((section(".text.field_state_transition." #name)))

extern void sub_8049000(void *, s32);

SECTION(sub_804FCD4) void field_state_apply_mode_transition(struct FieldStateObject *object)
{
    s32 value;
    ((struct FieldLowThreeBits *)&object->flags214)->value = 3;
    if (object->mode054 == 0) {
        u8 *flag = &object->flags35B;
        s32 bit = *flag & 8;
        value = 0x1001;
        if (bit)
            value += 0x27;
    } else {
        value = 0x1002;
    }
    sub_8049000(object, value);
    object->state = 0;
    ((struct FieldBitSix *)&object->flags212)->value = 0;
}
