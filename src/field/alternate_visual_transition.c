#include "field/alternate_visual_transition.h"

#define SEC(symbol) __attribute__((section(".text.field_alternate_visual_transition." #symbol)))
#define FIELD_RUNTIME (*(struct FieldAlternateVisualRuntime**)0x03000FD8)

struct FieldAlternateVisual {
    u8 unknown00[0x12];
    u8 flags12;
};

struct FieldAlternateVisualOwner {
    u8 unknown00[0x10];
    struct FieldAlternateVisual* visual10;
};

struct FieldAlternateVisualRuntime {
    u8 unknown000[0x80];
    struct FieldAlternateVisualOwner* owners80[2];
    u8 unknown088[0x238];
    u8 unknown2C0_0 : 2;
    u8 selectedOwner2C0 : 1;
    u8 unknown2C0_3 : 5;
};

void sub_80FD6D4(struct FieldAlternateVisualTransition* transition);

SEC(sub_8106FFC)
void field_continue_when_alternate_visual_finishes(
    struct FieldAlternateVisualTransition* transition)
{
    struct FieldAlternateVisualRuntime* runtime = FIELD_RUNTIME;
    struct FieldAlternateVisual* visual;
    s32 index;

    index = runtime->selectedOwner2C0 ^ 1;
    visual = runtime->owners80[index]->visual10;
    if (visual->flags12 & 8) {
        transition->callback = sub_80FD6D4;
        transition->callback(transition);
    }
}
