#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_early_visual_transitions." #name)))
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;

void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
s32 sub_8086858(struct RuntimeObject*, s32);
void sub_8063B80(struct RuntimeObject*);
void sub_8063C8C(struct RuntimeObject*);
void sub_8064614(struct RuntimeObject*);
void sub_8065310(struct RuntimeObject*);
void sub_806533C(struct RuntimeObject*);
void sub_806670C(struct RuntimeObject*);
void sub_8066E5C(struct RuntimeObject*);
void sub_806B5F8(struct RuntimeObject*);
void sub_806C9A4(struct RuntimeObject*);
void sub_8065FBC(struct RuntimeObject*);
void sub_806BC40(struct RuntimeObject*);
void sub_806D6A8(struct RuntimeObject*);
void sub_8070424(struct RuntimeObject*);
void sub_8070534(struct RuntimeObject*);
void sub_807F4FC(struct RuntimeObject*);
u32 sub_8199F30(void);

SEC(sub_8063BA8) void sub_8063BA8(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0xC, 0, 0);
        sub_8086858(object, 0x1485);
        object->secondaryUpdate = sub_8063B80;
        object->timer = 3;
        object->update = sub_8063C8C;
    }
}

SEC(sub_8064D20) void sub_8064D20(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (object->valueA0 == 0)
            sub_8082E1C(object, 5, 0, 0);
        else
            sub_8082E1C(object, 9, 0, 0);
        object->update = sub_8064614;
    }
}

SEC(sub_80651CC) void sub_80651CC(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 2, 0, 0);
        *(s32*)0x03000E3C = sub_8086858(object, 0x1509);
        object->secondaryUpdate = sub_8065310;
        object->update = sub_806533C;
    }
}

SEC(sub_80665AC) void sub_80665AC(struct RuntimeObject* object)
{
    struct RuntimeObject* linked;

    if (object->valueA0 == 1)
        linked = object->linkedObject->linkedObject;
    else
        linked = object->linkedObject;
    if (linked == NULL) {
        sound_effect_play(0x114, SOUND_VOLUME_UNCHANGED);
        if (object->behaviorState == 0)
            sub_8082E1C(object, 8, 0, 0);
        else
            sub_8082E1C(object, 0xC, 0, 0);
        object->update = sub_806670C;
    }
}

SEC(sub_8066E0C) void sub_8066E0C(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        if (object->behaviorState == 0)
            sub_8082E1C(object, 4, 0, 0);
        else
            sub_8082E1C(object, 5, 0, 0);
        object->timer = 4;
        object->update = sub_8066E5C;
        sound_effect_play(0xD5, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_806B5A8) void sub_806B5A8(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (object->valueA8 == 0)
            sub_8082E1C(object, object->valueA4 + 1, 0, 0);
        else
            sub_8082E1C(object, object->valueA4 + 4, 0, 0);
        object->update = sub_806B5F8;
    }
}

SEC(sub_806C94C) void sub_806C94C(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->valueA8 = (object->valueA8 + 1) & 1;
        object->behaviorState = 0;
        object->valueA4 = 0;
        if (object->valueA8 == 0)
            sub_8082E1C(object, 7, 0, 0);
        else
            sub_8082E1C(object, 0xD, 0, 0);
        object->update = sub_806C9A4;
    }
}

SEC(sub_8066780) void sub_8066780(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0x9C) == 0) {
            sub_8082E1C(arg0, 6, 0, 0);
        } else {
            sub_8082E1C(arg0, 0xA, 0, 0);
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8065FBC;
    }
}

SEC(sub_806BFD4) void sub_806BFD4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        if (FIELD_AT(arg0, s32*, 0xA8) == 0) {
            sub_8082E1C(arg0, 8, 0, 0);
        } else {
            sub_8082E1C(arg0, 0x10, 0, 0);
        }
        FIELD_AT(arg0, s16*, 0xAC) = 8;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806BC40;
    }
}

SEC(sub_806E98C) void sub_806E98C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 6, 0, 0);
        sub_8082E1C(FIELD_AT(arg0, void**, 0x30), 6, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806D6A8;
    }
}

SEC(sub_80705B4) void sub_80705B4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0x1B, 0, 0);
        FIELD_AT(arg0, s32*, 0xA8) = (s32)(1 & sub_8199F30());
        *(s32*)0x03000E3C = 0;
        sub_807F4FC(arg0);
        FIELD_AT(arg0, UnknownWord**, 0x60) = (UnknownWord*)&sub_8070424;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8070534;
    }
}
