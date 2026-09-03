#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_early_state_transitions." #name)))

void sub_807F4FC(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 value, s32 flags);
void sub_8060360(struct RuntimeObject* object);
void sub_806048C(struct RuntimeObject* object);
void sub_80610D4(struct RuntimeObject* object);
void sub_8062548(struct RuntimeObject* object);
void sub_8062F40(struct RuntimeObject* object);
void sub_8063524(struct RuntimeObject* object);
void sub_8060CB8(struct RuntimeObject* object);
void sub_80618A4(struct RuntimeObject* object);
u8 sub_801B1C8(void* handle, s32* positionX, s32* positionY);
void free_heap_8018DA8(void* handle);
void sub_807C298(void);
s32 sub_8082B00(void);

struct ObjectConditionOwner {
    u8 unknown00[0x40];
    s32 conditionValue;
};

SEC(sub_8060324) void sub_8060324(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x5C);
        sub_807F4FC(object);
        object->tertiaryUpdate = sub_8060360;
        sub_8082E1C(object, 4, 0, 0);
        object->update = sub_806048C;
    }
}

SEC(sub_80612FC) void sub_80612FC(struct RuntimeObject* object)
{
    struct ObjectConditionOwner* owner;

    if ((u32)(u16)object->timer <= 0x3FFFU) {
        owner = object->positionOwner;
        if (owner->conditionValue > 0)
            object->valueA8 = 1;
    }
    object->timer = (u16)object->timer + 1;
    if (object->value80 == 0) {
        sub_8082E1C(object, 3, 0, 0);
        object->visual->parameter20 = 0x10;
        object->update = sub_80610D4;
    }
}

SEC(sub_80624FC) void sub_80624FC(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        if (object->behaviorState == 0)
            sub_8082E1C(object, 5, 0, 0);
        else
            sub_8082E1C(object, 7, 0, 0);
        object->timer = 4;
        object->update = sub_8062548;
    }
}

SEC(sub_8062F00) void sub_8062F00(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        if (object->behaviorState == 0)
            sub_8082E1C(object, 4, 0, 0);
        else
            sub_8082E1C(object, 7, 0, 0);
        object->update = sub_8062F40;
    }
}

SEC(sub_80634DC) void sub_80634DC(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        if (object->behaviorState == 0)
            sub_8082E1C(object, 4, 0, 0);
        else
            sub_8082E1C(object, 5, 0, 0);
        object->timer = 1;
        object->update = sub_8063524;
    }
}

SEC(sub_8060B68) void sub_8060B68(struct RuntimeObject* object)
{
    void** handle = (void**)0x03000E18;
    void* currentHandle;
    s32* positionX;
    s32* positionY;

    currentHandle = *handle;
    positionX = (s32*)0x03000E1C;
    positionY = (s32*)0x03000E20;
    if (sub_801B1C8(currentHandle, positionX, positionY) == 1) {
        object->currentPositionX = *positionX;
        object->currentPositionY = *positionY;
        return;
    }
    object->currentPositionX = *positionX;
    object->currentPositionY = *positionY;
    free_heap_8018DA8(*handle);
    object->update = sub_8060CB8;
}

SEC(sub_8062188) void sub_8062188(struct RuntimeObject* object)
{
    s32 variant;

    if (object->linkedObject != 0) {
        sub_807C298();
    }
    if (sub_8082B00() == 0) {
        variant = object->behaviorState & 1;
        switch (variant) {
        case 0:
            sub_8082E1C(object, 2, 0, 0);
            break;
        case 1:
            sub_8082E1C(object, 6, 0, 0);
            break;
        }
        object->update = sub_80618A4;
    }
}
