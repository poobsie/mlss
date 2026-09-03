#include "ui/functions.h"
#include "ui/object.h"

u32 sub_8161E38(void* object);

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
