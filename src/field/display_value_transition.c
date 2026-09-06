#include "field/display_value_transition.h"
#include "field/runtime_nodes.h"
#include "graphics/functions.h"

#define SEC(symbol) __attribute__((section(".text.field_display_value_transition." #symbol)))
#define FIELD_RUNTIME (*(struct FieldDisplayValueRuntime**)0x03000FD8)

struct FieldDisplayValueRuntime {
    u8 unknown000[0x4C];
    struct FieldRuntimeNode* nodeList4C;
    u8 unknown050[0x2F2];
    u8 horizontalStep342;
};

void sub_807FB34(struct FieldDisplayValueVisual* visual);
s32 sub_810489C(struct FieldDisplayValueTransition* transition, s32 value);
void sub_8104A00(struct FieldDisplayValueTransition* transition);
void sub_8104A84(struct FieldDisplayValueTransition* transition);
void sub_8107248(struct FieldDisplayValueTransition* transition);
void sub_81072DC(void);
void sub_810D34C(s32 value, u8* end, s32 x, s32 y);

SEC(sub_8106A30)
void field_draw_value_until_visual_finishes(
    struct FieldDisplayValueTransition* transition)
{
    struct FieldDisplayValueVisual* visual;
    s32 x;
    s32 value;
    u8* end;

    x = (FIELD_RUNTIME->horizontalStep342 << 4) + 0x28;
    value = transition->value16;
    end = graphics_advance_by_nibble_width(value, (u8*)0xB8);
    sub_810D34C(value, end, x, 0);

    visual = transition->visual08;
    if (visual->flags12 & 8) {
        sub_807FB34(visual);
        transition->timer10 = 0;
        transition->callback = sub_8107248;
    }
}

SEC(sub_8106A88)
void field_advance_scaled_step_sequence(
    struct FieldDisplayValueTransition* transition)
{
    s32 step;
    s32 result;
    s32 lowBits;

    step = transition->step14;
    result = sub_810489C(transition, step * 3);
    transition->timer10 = result;
    lowBits = result & 0x7FF;
    if (lowBits == 0) {
        step = transition->step14++;
        if (step > 7) {
            transition->timer10 = lowBits;
            transition->callback = sub_8104A00;
        }
    }
}

SEC(sub_8107248)
void field_draw_value_then_push_callback_node(
    struct FieldDisplayValueTransition* transition)
{
    struct FieldDisplayValueRuntime** runtimeSlot;
    s32 x;
    s32 value;
    u8* end;

    runtimeSlot = (struct FieldDisplayValueRuntime**)0x03000FD8;
    x = ((*runtimeSlot)->horizontalStep342 << 4) + 0x28;
    value = transition->value16;
    end = graphics_advance_by_nibble_width(value, (u8*)0xB8);
    sub_810D34C(value, end, x, 0);

    if (++transition->timer10 > 9) {
        field_runtime_push_external_node(&(*runtimeSlot)->nodeList4C,
                                         sub_81072DC);
        transition->timer10 = 0;
        transition->callback = sub_8104A84;
    }
}
