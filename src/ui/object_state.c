#include "ui/functions.h"
#include "ui/object.h"

u32 sub_8161E38(void* object);
void sub_816391C(void* object, u32 mode, s32 value);

void ui_object_configure_mode6(struct UiObject* object, s32 value)
    __attribute__((section(".text.sub_81639C4")));
void ui_object_configure_mode6(struct UiObject* object, s32 value) {
    sub_816391C(object, 6, value);
}
__attribute__((section(".text.sub_81639C4")))
const u16 ui_object_configure_mode6_padding = 0;

void ui_object_set_visual(struct UiObject* object, void* visual)
    __attribute__((section(".text.sub_81639D4")));
void ui_object_set_visual(struct UiObject* object, void* visual) {
    object->value44 = visual;
    object->counter48 = 0;
}
__attribute__((section(".text.sub_81639D4")))
const u16 ui_object_set_visual_padding = 0;

u32 ui_object_reset_and_update(struct UiObject* object, void* value)
    __attribute__((section(".text.sub_81639E0")));
u32 ui_object_reset_and_update(struct UiObject* object, void* value) {
    object->value44 = value;
    object->counter48 = 0;
    object->state40 = 0;
    return sub_8161E38(object);
}
__attribute__((section(".text.sub_81639E0")))
const u16 sub_81639E0_padding = 0;

void ui_object_reset(struct UiObject* object, void* value)
    __attribute__((section(".text.sub_81639F8")));
void ui_object_reset(struct UiObject* object, void* value) {
    object->value44 = value;
    object->counter48 = 0;
    object->state40 = 0;
}
__attribute__((section(".text.sub_81639F8")))
const u16 sub_81639F8_padding = 0;

void ui_object_set_values_18_20(struct UiObject* object, u32 value18,
                                u32 value1C, u32 value20)
    __attribute__((section(".text.sub_8163A64")));
void ui_object_set_values_18_20(struct UiObject* object, u32 value18,
                                u32 value1C, u32 value20) {
    object->value18 = value18;
    object->value1C = value1C;
    object->value20 = value20;
}

void ui_object_copy_pair_values(struct UiObjectPairValues* object)
    __attribute__((section(".text.sub_8163A6C")));
void ui_object_copy_pair_values(struct UiObjectPairValues* object) {
    object->copiedValue54 = object->value52;
    object->copiedValue58 = object->value56;
}
