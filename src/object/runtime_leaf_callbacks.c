#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_leaf_callbacks.h"

#define SEC(name) \
    __attribute__((section(".text.runtime_leaf_callbacks." #name)))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_8065E2C(struct RuntimeObject* object);
void sub_8068E60(struct RuntimeObject* object);
void sub_8069014(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
s32 sub_8082B00(struct RuntimeObject* object);
s32 sub_80871A8(struct RuntimeObject* object);
s32 sub_8086C64();
s32 sub_8086D80(struct RuntimeObject* object);
s32 sub_8086858(struct RuntimeObject* object, s32 effect);
s32 sub_8199F30(void);
void sub_807F47C(struct RuntimeObject* object);
void sub_807F4FC(struct RuntimeObject* object);
void sub_8085B38(struct RuntimeObject* object);
struct RuntimeObject* sub_807C0D0(
    struct RuntimeObject* object, s32 command, s32 argument);
void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);

void sub_80695E4(struct RuntimeObject* object);
void sub_8062188(struct RuntimeObject* object);
void sub_806A47C(struct RuntimeObject* object);
void sub_8071244(struct RuntimeObject* object);
void sub_806EDBC(struct RuntimeObject* object);
void sub_80712B0(struct RuntimeObject* object);
void sub_8071424(struct RuntimeObject* object);
void sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);

SEC(sub_8071390)
void object_start_paired_animation_3_and_owner_motion(
    struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* source;
    s32* motionTargetX;
    u8 flags;

    if (object->visual->flags & OBJECT_VISUAL_COMPLETE) {
        sound_effect_play(0x6C, SOUND_VOLUME_UNCHANGED);
        sub_8082E1C(object, 3, 0x40B4, 0);
        sub_8082E1C(object->linkedObject, 3, 0, 0);
        motionTargetX = &object->value84;
        owner = object->positionOwner;
        source = owner->positionSource;
        *motionTargetX = source->positionX + 0xA000;
        object->value88 = source->positionY;
        object->value8C = object->positionZBase;
        object->motionSpeed = 0x100;
        flags = object->motionFlags;
        flags |= 0x20;
        object->motionFlags = flags;
        object->motionDurationOverride = 0;
        sub_8085B38(object);
        object->timer = 8;
        object->update = sub_8071424;
    }
}

SEC(sub_80711A4)
void object_emit_effect_207a_then_start_countdown_on_visual_complete(
    struct RuntimeObject* object)
{
    if (object->visual->flags & OBJECT_VISUAL_COMPLETE) {
        sub_80DF024(0x207A, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        sub_810DD7C(object, object->positionOwner, 0xFF);
        object->timer = 5;
        object->update = sub_80712B0;
    }
}

SEC(sub_8070E4C)
void object_prepare_owner_motion_animation_2_and_sound_11b(
    struct RuntimeObject* object)
{
    struct ObjectPositionOwner* owner;
    struct ObjectPositionSource* source;
    s32* motionTargetX;
    u8 flags;

    sub_8082E1C(object, 2, 0, 0);
    motionTargetX = &object->value84;
    owner = object->positionOwner;
    source = owner->positionSource;
    *motionTargetX = source->positionX + 0x5000;
    object->value88 = source->positionY;
    object->value8C = object->positionZBase;
    object->motionSpeed = 0x180;
    flags = object->motionFlags;
    flags |= 0x20;
    object->motionFlags = flags;
    object->motionDurationOverride = 0;
    sub_8085B38(object);
    sound_effect_play(0x11B, SOUND_VOLUME_UNCHANGED);
    object->update = object_start_animation_3_dual_callbacks_when_value80_clears;
}

SEC(sub_8071110)
void object_start_animation_3_dual_callbacks_when_value80_clears(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11B);
        sound_effect_play(0xD2, SOUND_VOLUME_UNCHANGED);
        sub_8082E1C(object, 3, 0, 0);
        object->timer = 10;
        object->behaviorState = 10;
        sub_807F4FC(object);
        object->auxiliaryUpdate = sub_8071244;
        object->tertiaryUpdate =
            (RuntimeObjectCallback)object_finish_sound_d2_and_begin_animation_1_when_ready;
        object->update = sub_806EDBC;
    }
}

void sub_806CBA0(struct RuntimeObject* object);
void sub_806FC68(struct RuntimeObject* object);
void sub_8070534(struct RuntimeObject* object);
void sub_80706E8(struct RuntimeObject* object);
void sub_8070CF0(struct RuntimeObject* object);
void sub_807F47C(struct RuntimeObject* object);
void sub_80775A4(struct RuntimeObject* object);
void sub_80799B4(struct RuntimeObject* object);
void sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);

/* Effect IDs and unnamed continuations stay numeric until their owners are known.
 * RuntimeObject fields at 0x7A and 0x7C are confirmed halfword storage, but their
 * behavioral meaning is still unknown. */
