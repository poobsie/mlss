#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))

void sub_805FF30(struct RuntimeObject* object);
void sub_80605CC(struct RuntimeObject* object);
void sub_8060090(struct RuntimeObject* object);
void sub_806062C(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);
void sub_8060D4C(struct RuntimeObject* object);
void sub_8060DEC(struct RuntimeObject* object);
void sub_807F4FC(struct RuntimeObject* object);
s32 sub_8082B00(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_807FC08(s32* x, s32* y, s32* z, s32 argument);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80DF024(s32 effect, s32 x, s32 y, s32 z,
                 struct RuntimeObject* object);

SEC(sub_805FD40)
void object_finish_when_state_value_ba_clear(struct RuntimeObject* object)
{
    if (object->state->valueBA == 0)
        sub_807C298(object);
}
SEC(sub_805FD40)
const u16 object_finish_when_state_value_ba_clear_padding = 0;

SEC(sub_805FD5C)
void object_accelerate_left_to_behavior_position(struct RuntimeObject* object)
{
    if ((s16)object->stateValueB0 != 0)
        object->secondaryTimer += 0x10;
    else
        object->secondaryTimer += 0x13;

    object->currentPositionX -= object->secondaryTimer;
    if (object->currentPositionX < object->behaviorState) {
        object->verticalVelocity = 0;
        object->currentPositionX = object->behaviorState;
        sub_8082E1C(object, 8, 0, 0);
        object->update = sub_805FF30;
    }
}

SEC(sub_805FE74)
void object_update_offset_motion_then_finish_outside_transformed_bounds(
    struct RuntimeObject* object)
{
    s32 transformedX;
    s32 transformedY;
    s32 transformedZ;
    s32 position;

    object->currentPositionX = object->positionX - object->secondaryTimer;
    object->verticalPosition = object->positionZBase - object->verticalVelocity;
    object->verticalVelocity += 0x20;
    position = object->currentPositionX;
    if (position < 0)
        position += 0xFF;
    transformedX = position >> 8;
    position = object->currentPositionY;
    if (position < 0)
        position += 0xFF;
    transformedY = position >> 8;
    position = object->verticalPosition;
    if (position < 0)
        position += 0xFF;
    transformedZ = position >> 8;
    sub_807FC08(&transformedX, &transformedY, &transformedZ, 0);
    if (transformedY > 0x110)
        sub_807C298(object);
    else if (transformedX < -0x10)
        sub_807C298(object);
}

SEC(sub_805FEF4)
void object_when_value80_clear_snap_to_behavior_position(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        struct RuntimeObjectVisual* visual = object->visual;
        u8 flags = visual->flags11;

        flags |= 0x40;
        visual->flags11 = flags;
        object->verticalVelocity = 0;
        object->currentPositionX = object->behaviorState;
        sub_8082E1C(object, 8, 0, 0);
        object->update = sub_805FF30;
    }
}

SEC(sub_8060500)
void object_on_visual_complete_countdown_then_animation_13(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer < 0) {
            sub_8082E1C(object, 13, 0, 0);
            sound_effect_play(0x83, SOUND_VOLUME_UNCHANGED);
            object->update = object_on_visual_complete_animation_2_variant_a;
        }
    }
}

SEC(sub_8060544)
void sub_8060544(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer = 4;
        sub_8082E1C(object, 9, 0, 0);
        sub_80DF024(0x10F5, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->update = sub_806062C;
    }
}

SEC(sub_806062C)
void object_on_visual_complete_countdown_emit_effect_1107(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        object->timer--;
        if (object->timer < 0) {
            sub_8082E1C(object, 10, 0, 0);
            sub_80DF024(0x1107, object->positionX / 0x100,
                        object->positionY / 0x100,
                        object->positionZBase / 0x100, object);
            object->update = sub_8060090;
        }
    }
}

SEC(sub_8060CE8)
void sub_8060CE8(struct RuntimeObject* object)
{
    if (sub_8082B00(object) == 0) {
        sub_807F4FC(object);
        object->tertiaryUpdate = sub_8060D4C;
        object->verticalVelocity = object->verticalPosition / 0x100;
        object->secondaryTimer = object->currentPositionX / 0x100;
        object->stateValueB0 = object->currentPositionY / 0x100;
        sub_8082E1C(object, 2, 0, 0);
        object->update = sub_8060DEC;
    }
}

__attribute__((section(".text.misc_helpers_02.sub_8060DEC")))
void sub_8060DEC(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 3, 0, 0);
        sub_80DF024(0x124C, object->positionX / 0x100,
                    object->positionY / 0x100,
                    object->positionZBase / 0x100, object);
        object->value8C = object->positionZBase;
        object->update = (RuntimeObjectCallback)0x08060E7D;
    }
}

__attribute__((section(".text.misc_helpers_02.sub_8060E4C")))
void sub_8060E4C(struct RuntimeObject* object)
{
    s32 value = (u16)object->timer - 1;

    object->timer = value;
    if ((value << 16) <= 0) {
        sub_8082E1C(object, 4, 0, 0);
        object->update = sub_808750C;
    }
}

__attribute__((section(".text.small_functions_02.sub_8060BB8")))
void sub_8060BB8(struct RuntimeObject* object)
{
    s32 value = (u16)object->timer - 1;

    object->timer = value;
    if ((value << 16) <= 0) {
        sub_8082E1C(object, 7, 0, 0);
        object->update = sub_808750C;
    }
}
