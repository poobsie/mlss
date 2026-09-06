#include "object/runtime_leaf_callbacks.h"

#define SEC(symbol) \
    __attribute__((section(".text.object_small_runtime." #symbol)))

s32 sub_80871A8(struct RuntimeObject* object);
s32 sub_8086D80(struct RuntimeObject* object);
s32 sub_810DD7C(struct RuntimeObject* object, void* owner, s32 command);

void sub_80643DC(struct RuntimeObject* object);
void sub_8064424(struct RuntimeObject* object);
void sub_8065384(struct RuntimeObject* object);
void sub_80722F8(struct RuntimeObject* object);
void sub_8074508(struct RuntimeObject* object);
void sub_8086090(struct RuntimeObject* object);
void sub_8089F44(struct RuntimeObject* object);
void sub_8086700(void* state);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command,
                 s32 argument);
void sub_809C954(struct RuntimeObject* object);
void sub_80A2BC0(struct RuntimeObject* object);

SEC(sub_8064274)
s32 object_continue_slow_exit_motion_when_ready(
    struct RuntimeObject* object)
{
    s32 result = sub_80871A8(object);
    if (result != 0)
        return result;
    object->update = sub_80643DC;
    return 0;
}

SEC(sub_8064290)
s32 object_emit_effect_1081_when_ready(struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result != 0)
        return result;
    object->update = sub_8064424;
    return 0;
}

SEC(sub_8065214)
s32 object_emit_effect_eff_when_ready(struct RuntimeObject* object)
{
    s32 result = sub_8086D80(object);
    if (result != 0)
        return result;
    object->update = sub_8065384;
    return 0;
}

SEC(sub_80722E0)
s32 object_attach_owner_then_begin_horizontal_motion(
    struct RuntimeObject* object, void* owner)
{
    s32 result = sub_810DD7C(object, owner, 0xFF);
    object->update = sub_80722F8;
    return result;
}

SEC(sub_807413C)
void object_advance_valueA8_then_wait_for_child(struct RuntimeObject* object)
{
    object->valueA8++;
    if (object->valueA8 > 0x71) {
        object->valueA8 = 0x72;
        object->timer = 0x12C;
        object->update = sub_8074508;
    }
}

SEC(sub_80875B8)
void object_count_down_timer_then_resume(struct RuntimeObject* object)
{
    if (object->timer > 0)
        object->timer--;
    else
        object->update = sub_8086090;
}

SEC(sub_8087BA4)
void object_finish_saved_update_countdown(struct RuntimeObject* object)
{
    object->timer--;
    if (object->timer <= 1) {
        object->visual->parameter20 = 0x10;
        object->update = object->followup;
        object->followup = 0;
    }
}
SEC(sub_8087BA4)
const u16 object_finish_saved_update_countdown_padding = 0;

struct ObjectRuntimePollTarget {
    u8 unknown00[0x111];
    u8 flags111;
};

struct ObjectRuntimePollOwner {
    u32 unknown00;
    s32 pending04;
    struct ObjectRuntimePollTarget* target08;
};

SEC(sub_8087C20)
void object_runtime_finish_when_target_flag_2_clears(
    struct ObjectRuntimePollOwner* owner)
{
    struct ObjectRuntimePollTarget* target = owner->target08;
    u8 pending = target->flags111 & 2;

    if (pending == 0) {
        sub_8086700((u8*)target + 8);
        owner->pending04 = pending;
    }
}

SEC(sub_8088508)
void object_finish_motion_and_restore_saved_update(
    struct RuntimeObject* object)
{
    s8* flags;

    if (object->flags79 & 0x20) {
        if ((object->flags76 & 6) == 2 || (object->flags76 & 6) == 4) {
            sub_8082E1C(object, 0, -1, 0);
            flags = (s8*)&object->visual->flags11;
            *flags &= -0x41;
            flags = (s8*)&object->visual->flags;
            *flags &= -7;
        }
        object->update = object->followup;
        object->followup = 0;
    }
}
SEC(sub_8088508)
const u16 object_finish_motion_and_restore_saved_update_padding = 0;

SEC(sub_8089BD4)
void object_update_x_offset_until_timer_expires(struct RuntimeObject* object)
{
    object->currentPositionX = object->positionX + object->secondaryTimer;
    object->timer--;
    if (object->timer <= 0)
        object->update = sub_8089F44;
}

SEC(sub_809C960)
s32 object_continue_when_linked_object_clears(struct RuntimeObject* object)
{
    if (object->linkedObject != 0)
        return 0;
    object->update = sub_809C954;
    return 1;
}
SEC(sub_809C960)
const u16 object_continue_when_linked_object_clears_padding = 0;

SEC(sub_80A2C80)
void object_begin_fixed_vertical_descent(struct RuntimeObject* object)
{
    object->verticalVelocity = -0x1B3;
    object->update = sub_80A2BC0;
}
