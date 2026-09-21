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

void ui_object_set_visual(struct UiObject* object, const void* visual)
    __attribute__((section(".text.sub_81639D4")));
void ui_object_set_visual(struct UiObject* object, const void* visual) {
    object->visualDefinition = visual;
    object->visualStepIndex = 0;
}
__attribute__((section(".text.sub_81639D4")))
const u16 ui_object_set_visual_padding = 0;

u32 ui_object_reset_and_update(struct UiObject* object, const void* value)
    __attribute__((section(".text.sub_81639E0")));
u32 ui_object_reset_and_update(struct UiObject* object, const void* value) {
    object->visualDefinition = value;
    object->visualStepIndex = 0;
    object->visualState = 0;
    return sub_8161E38(object);
}
__attribute__((section(".text.sub_81639E0")))
const u16 sub_81639E0_padding = 0;

void ui_object_reset(struct UiObject* object, const void* value)
    __attribute__((section(".text.sub_81639F8")));
void ui_object_reset(struct UiObject* object, const void* value) {
    object->visualDefinition = value;
    object->visualStepIndex = 0;
    object->visualState = 0;
}
__attribute__((section(".text.sub_81639F8")))
const u16 sub_81639F8_padding = 0;

u32 ui_object_visual_is_idle(struct UiObject* object)
    __attribute__((section(".text.sub_8163A08")));
u32 ui_object_visual_is_idle(struct UiObject* object) {
    if (object->visualDefinition != 0 && object->visualState != 1)
        return 0;
    return 1;
}
__attribute__((section(".text.sub_8163A08")))
const u16 ui_object_visual_is_idle_padding = 0;

void ui_object_set_values_18_20(struct UiObject* object, s32 positionX,
                                s32 positionYOffset, s32 positionY)
    __attribute__((section(".text.sub_8163A64")));
void ui_object_set_values_18_20(struct UiObject* object, s32 positionX,
                                s32 positionYOffset, s32 positionY) {
    object->positionX = positionX;
    object->positionYOffset = positionYOffset;
    object->positionY = positionY;
}

void ui_object_copy_pair_values(struct UiObjectPairValues* object)
    __attribute__((section(".text.sub_8163A6C")));
void ui_object_copy_pair_values(struct UiObjectPairValues* object) {
    object->copiedValue54 = object->value52;
    object->copiedValue58 = object->value56;
}

u16 sub_81DA690(s16 x, s16 y);

void ui_object_update_direction_toward_point(void* unused,
                                             struct UiObject* object,
                                             s32 targetX, s32 targetY)
    __attribute__((section(".text.sub_8167D50")));
void ui_object_update_direction_toward_point(void* unused,
                                             struct UiObject* object,
                                             s32 targetX, s32 targetY) {
    u16 angle = sub_81DA690((object->positionX - targetX) << 8 >> 16,
                           (object->positionY - targetY) << 8 >> 16);
    object->directionIndex = *(s8*)(0x0821422C
        + (((u32)angle + 0x1000) >> 13));
}
