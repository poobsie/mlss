#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_late_visual_transitions." #name)))

void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
void sub_80883A0(struct RuntimeObject*, s32);
s32 sub_8086C64(void);
void sub_808843C(struct RuntimeObject*, s32, s32, s32, s32);
void sub_80880C4(struct RuntimeObject*, s32);
u8 sub_8087CE4(void);
void sub_807FB64(struct RuntimeObjectVisual*);
void sub_810F824(struct RuntimeObject*);
void sub_81109D0(struct RuntimeObject*);
void sub_8110A94(struct RuntimeObject*);
void sub_81127B8(struct RuntimeObject*);
void sub_81135C0(struct RuntimeObject*);

struct ObjectPositionSource {
    u8 unknown00[0xD8];
    s32 positionX;
    s32 positionY;
    s32 positionZ;
};

struct ObjectPositionOwner {
    u8 unknown00[0x28];
    struct ObjectPositionSource* positionSource;
};

SEC(sub_810FD10) void sub_810FD10(struct RuntimeObject* object)
{
    struct RuntimeObject* linked = object->linkedObject;

    if (linked->visual->flags & 8) {
        sub_8082E1C(linked, 0, 0, 0);
        sub_80883A0(object, 0xC);
        sound_effect_play(0x10F, SOUND_VOLUME_UNCHANGED);
        object->update = sub_810F824;
    }
}

SEC(sub_811090C) s32 sub_811090C(struct RuntimeObject* object)
{
    s32 result = sub_8086C64();
    struct RuntimeObject* linked;

    if (result == 0) {
        linked = object->linkedObject;
        if (linked != 0) {
            do {
                linked->valueA8 = 1;
                linked = linked->linkedObject;
            } while (linked != 0);
        }
        object->update = sub_81109D0;
        sound_effect_stop(0x10F);
        result = 0;
    }
    return result;
}

SEC(sub_81124D0) void sub_81124D0(struct RuntimeObject* object)
{
    sub_808843C(object, 0x8A, 0x6C, 0, 0x100);
    sub_80880C4(object, 0x380);
    sub_8082E1C(object, 0xA, 0, 0);
    object->update = sub_81127B8;
    sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_811448C) void sub_811448C(struct RuntimeObject* object)
{
    u8 result = sub_8087CE4();

    if (result == 0) {
        u8* runtime = *(u8**)0x03000FD8;
        runtime[0xC] |= 0x80;
        sub_8082E1C(object, -1, -1, 0);
        object->visual->parameter20 = 0x10;
        object->update = 0;
    }
}

SEC(sub_8110A30) void sub_8110A30(struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* source;
    s32 position;

    if (object->visual->flags & 8) {
        sub_80883A0(object, 0x20);
        owner = object->positionOwner;
        source = owner->positionSource;
        position = source->positionX + 0x2000;
        object->currentPositionX = position;
        object->positionX = position;
        position = source->positionY;
        object->currentPositionY = position;
        object->positionY = position;
        position = source->positionZ + 0x800;
        object->verticalPosition = position;
        object->positionZBase = position;
        sub_807FB64(object->visual);
        sound_effect_stop(0x119);
        object->update = sub_8110A94;
    }
}

SEC(sub_811458C) void sub_811458C(struct RuntimeObject* object)
{
    sub_8082E1C(object->linkedObject->linkedObject, 4, 0, 0);
    object->timer = 0x20;
    object->followup = sub_81135C0;
    object->update = (RuntimeObjectCallback)0x081141F5;
    sound_effect_play(0x120, SOUND_VOLUME_UNCHANGED);
}
