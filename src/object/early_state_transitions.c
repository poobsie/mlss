#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_early_state_transitions." #name)))
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;

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
void sub_806A348(struct RuntimeObject* object);
u8 sub_801B1C8(void* handle, s32* positionX, s32* positionY);
void free_heap_8018DA8(void* handle);
void sub_807C298();
s32 sub_8082B00(void);
void sub_810DD7C(struct RuntimeObject* object, void* owner, s32 value);
u32 sub_8199F30(void);
void sub_807F4FC(struct RuntimeObject* object);
void sub_806D048(struct RuntimeObject*);
void sub_806D104(struct RuntimeObject*);
void sub_806D1D4(struct RuntimeObject*);
void sub_806D290(struct RuntimeObject*);
void sub_806E8E8(struct RuntimeObject*);
void sub_806F47C(struct RuntimeObject*);
void sub_80711A4(struct RuntimeObject*);
void sub_80706B0(struct RuntimeObject*);
void sub_8079284(struct RuntimeObject*);
void sub_80797E0(struct RuntimeObject*);
void sub_80798C4(struct RuntimeObject*);
void sub_807F47C(struct RuntimeObject* object);

struct ObjectConditionOwner {
    u8 unknown00[0x40];
    s32 conditionValue;
};

struct ObjectPositionSourceX {
    u8 unknown00[0xD8];
    s32 positionX;
};

struct ObjectPositionSourceOwner {
    u8 unknown00[0x28];
    struct ObjectPositionSourceX* source;
};

struct ObjectPositionHistoryNode {
    struct ObjectPositionHistoryNode* next;
    s32 positionX;
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

SEC(sub_8062C48) void sub_8062C48(struct RuntimeObject* object)
{
    s32 stateValue;
    u16 timer;
    struct RuntimeObject* owner;
    struct RuntimeObjectState* state;

    owner = object->positionOwner;
    if (!(owner->flags76 & 0x80) && (owner->verticalPosition == 0)) {
        sub_810DD7C(object, owner, 0xFF);
    }
    timer = (u16)object->timer;
    object->timer = timer - 1;
    if ((s32)(timer << 0x10) <= 0) {
        state = object->state;
        stateValue = state->value38;
        if (stateValue == 0) {
            state->valueB4 = stateValue;
        }
        sub_807C298(object);
    }
}

SEC(sub_8068798) void sub_8068798(struct RuntimeObject* object)
{
    s32 height;
    s32 loweredHeight;
    s32 roundedPosition;

    object->currentPositionX += -0x133;
    height = object->verticalPosition;
    if (height > 0x800) {
        loweredHeight = height - 0x100;
        object->verticalPosition = loweredHeight;
        if (loweredHeight <= 0x800) {
            object->verticalPosition = 0x800;
            sub_8082E1C(object, 1, 0, 0);
        }
    }
    roundedPosition = object->currentPositionX;
    if (roundedPosition < 0)
        roundedPosition += 0xFF;
    if ((roundedPosition >> 8) <= -0x20) {
        sub_807C298(object);
    }
}

SEC(sub_806A24C) void sub_806A24C(struct RuntimeObject* object)
{
    u32 range;

    if (object->value80 == 0) {
        sound_effect_stop(0x81);
        range = object->valueA4 - object->valueA0;
        object->valueA8 = object->valueA0 + (sub_8199F30() % range);
        object->update = sub_806A348;
    }
}

SEC(sub_8070670) s32 sub_8070670(struct RuntimeObject* object, void* owner)
{
    struct ObjectPositionSourceOwner* positionOwner;

    sub_810DD7C(object, owner, 0xFF);
    sub_807F47C(object);
    positionOwner = object->positionOwner;
    object->currentPositionX = positionOwner->source->positionX;
    sub_8082E1C(object, 8, 0, 0);
    object->timer = 2;
    object->update = sub_80706B0;
    return 0;
}

SEC(sub_8079348) void sub_8079348(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_8082E1C(object, 4, 0x4029, 0);
        sound_effect_play(0xE6, SOUND_VOLUME_UNCHANGED);
        object->timer = 4;
        object->update = sub_8079284;
        sub_807F4FC(object);
        object->tertiaryUpdate = sub_80797E0;
    }
}

SEC(sub_807940C) void sub_807940C(struct RuntimeObject* object)
{
    if (*(s32*)0x03000F6C == 0)
        sub_8082E1C(object, 2, 0x4029, 0);
    else
        sub_8082E1C(object, 7, 0x4029, 0);
    object->update = sub_80798C4;
}

SEC(sub_80794FC) void sub_80794FC(struct RuntimeObject* object)
{
    s32 previousPosition;
    s32 nextPosition;
    s32 roundedPosition;
    struct ObjectPositionHistoryNode* node;

    previousPosition = object->currentPositionX;
    object->currentPositionX = previousPosition - 0x280;
    node = object->positionHistory;
    if (node != NULL) {
        do {
            nextPosition = node->positionX;
            node->positionX = previousPosition;
            previousPosition = nextPosition;
            node = node->next;
        } while (node != NULL);
    }
    roundedPosition = object->currentPositionX;
    if (roundedPosition < 0)
        roundedPosition += 0xFF;
    if ((roundedPosition >> 8) <= -0x28) {
        sub_807C298(object);
    }
}

SEC(sub_806D548) s32 sub_806D548(void* arg0, UnknownWord arg1) {
    UnknownWord* var_r0;
    s32 temp_r0;

    sub_810DD7C(arg0, (void*)arg1, 0xFF);
    temp_r0 = FIELD_AT(arg0, s32*, 0xA8);
    switch (temp_r0) {
        case 0:
            var_r0 = (UnknownWord*)&sub_806D048;
            break;
        case 1:
            var_r0 = (UnknownWord*)&sub_806D104;
            break;
        case 2:
            var_r0 = (UnknownWord*)&sub_806D1D4;
            break;
        default:
            var_r0 = (UnknownWord*)&sub_806D290;
            break;
    }
    FIELD_AT(arg0, UnknownWord**, 0x4C) = var_r0;
    return 0;
}

SEC(sub_806E624) void sub_806E624(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x99);
        sub_8082E1C(arg0, 4, 0, 0);
        sub_807F4FC(arg0);
        sound_effect_play(0x118, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806E8E8;
    }
}

SEC(sub_8070D88) void sub_8070D88(struct RuntimeObject* object)
{
    s32 remaining;

    object->verticalPosition += object->value8C;
    object->value8C -= 0x80;
    if (object->verticalPosition <= 0) {
        object->verticalPosition = 0;
        remaining = object->behaviorState - 1;
        object->behaviorState = remaining;
        if (remaining == 0) {
            object->value8C = 0x300;
            return;
        }
        object->update = sub_806F47C;
    }
}

SEC(sub_8071018) s32 sub_8071018(void* arg0) {
    sound_effect_stop(0xA7);
    sub_8082E1C(arg0, 4, 0x40E7, 0);
    FIELD_AT(arg0, s32*, 0x80) = 0;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80711A4;
    sound_effect_play(0x55, SOUND_VOLUME_UNCHANGED);
    return 0;
}

SEC(sub_80745A8) void sub_80745A8(void* arg0) {
    void* temp_r4;
    void* temp_r5;
    void* temp_r6;

    temp_r6 = FIELD_AT(arg0, void**, 0x30);
    temp_r5 = FIELD_AT(temp_r6, void**, 0x30);
    temp_r4 = FIELD_AT(temp_r5, void**, 0x30);
    sub_807C298(FIELD_AT(temp_r4, void**, 0x30));
    sub_807C298(temp_r4);
    sub_807C298(temp_r5);
    sub_807C298(temp_r6);
    sound_effect_stop(0x5E);
    FIELD_AT(arg0, s32*, 0x4C) = 0;
}

SEC(sub_8075DF4) void sub_8075DF4(void* arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r1;
    void* temp_r1_2;

    if (FIELD_AT(arg0, s32*, 0x9C) == 2) {
        temp_r1 = FIELD_AT(arg0, s32*, 0xA0) + 0xFFFFFA00;
        FIELD_AT(arg0, s32*, 0xA0) = temp_r1;
        FIELD_AT(FIELD_AT(arg0, void**, 8), s16*, 0xC) = (s16)temp_r1;
    }
    temp_r0 = FIELD_AT(arg0, s32*, 0xA4);
    if (temp_r0 > 0) {
        temp_r0_2 = temp_r0 - 8;
        FIELD_AT(arg0, s32*, 0xA4) = temp_r0_2;
        temp_r1_2 = FIELD_AT(arg0, void**, 8);
        FIELD_AT(temp_r1_2, s16*, 6) = (s16)temp_r0_2;
        FIELD_AT(temp_r1_2, s16*, 4) = (s16)temp_r0_2;
    }
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_807C298(arg0);
    }
}
