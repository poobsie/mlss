#include "global.h"
#include "field/state.h"

#define SECTION(name) __attribute__((section(".text.field_state_preservation")))

extern void sub_8047804(void *, u8);
extern void sub_8047858(void *, u8);
extern void sub_80494D4(void *);
extern void sub_804FCD4(void *);

#define DEFINE_STATE_DISPATCH(name, finish) \
    SECTION(name) void name(struct FieldStateObject *object, u8 mode) \
    { \
        u16 state; \
        u32 saved214 = ((struct FieldLowThreeBits *)&object->flags214)->value; \
        u32 saved24 = ((struct FieldLowThreeBits *)&object->flags024)->value; \
        state = object->state; \
        if ((u32)(u16)(state - 5) <= 4) \
            sub_804FCD4(object); \
        else if ((u32)(u16)(state - 10) <= 2) \
            sub_80494D4(object); \
        ((struct FieldLowThreeBits *)&object->flags214)->value = saved214; \
        ((struct FieldLowThreeBits *)&object->flags024)->value = saved24; \
        finish(object, mode); \
    }

DEFINE_STATE_DISPATCH(sub_804FD80, sub_8047804)
DEFINE_STATE_DISPATCH(sub_804FDF4, sub_8047858)

__attribute__((section(".text.field_state_preservation"))) const u16 field_state_padding = 0;
