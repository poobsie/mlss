#include "audio/sound_effects.h"
#include "field/object_status_transitions.h"

#define SEC(symbol) \
    __attribute__((section(".text.object_status_transitions." #symbol)))

struct FieldObjectStatusProcess {
    u8 unknown00[4];
    void (*update)(struct FieldObjectStatusProcess* process);
    struct FieldObjectStatus* owner;
    u8 unknown0C[4];
    s16 timer;
};

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
s32 sub_8082B00(void);
void sub_8082AAC(s32 command);
struct FieldObjectStatusProcess* sub_807FFB8(
    void (*update)(struct FieldObjectStatusProcess* process));
u32 sub_8199F30(void);
s32 sub_81DD77C(u32 limit, s32 value);
void* sub_8086E8C(struct RuntimeObject* object);

void field_object_finish_variant_action_when_visual_ready(
    struct FieldObjectStatusProcess* process);
void field_object_play_sound_151_after_delay(
    struct FieldObjectStatusProcess* process);
void field_object_start_variant_action_when_ready(
    struct FieldObjectStatusProcess* process);
void field_object_prepare_variant_action(
    struct FieldObjectStatusProcess* process);

SEC(sub_81083EC)
s32 field_object_try_activate_status_0400(
    struct FieldObjectStatus* object, s32 threshold)
{
    u16 previousFlags;
    u8* modeFlags;

    if ((object->flags11E & 0x400) ||
        threshold < sub_81DD77C(0x64, sub_8199F30()))
        return 0;

    previousFlags = object->flags11E;
    object->flags11E = previousFlags & 0xF3FF;
    if (!(previousFlags & 0x800)) {
        modeFlags = &object->control120.bytes.flags122;
        if (!(*modeFlags & 0x40)) {
            object->attachment118 =
                sub_8086E8C(field_object_status_runtime_object(object));
            *modeFlags |= 0x40;
        }
        object->value128 = 0xFF;
        object->value126 = 1;
        object->value12A = 1;
        object->flags11E |= 0x400;
        goto update_control;
    }
    if ((u8)(object->value12C - 0x13) <= 1) {
update_control:
        object->control120.value =
            (object->control120.value & 0xFFFC7FFF) | 0x20000;
    }
    return 1;
}

SEC(sub_81084B4)
s32 field_object_try_activate_status_0800(
    struct FieldObjectStatus* object, s32 threshold)
{
    u16 previousFlags;
    u8* modeFlags;

    if ((object->flags11E & 0x800) ||
        threshold < sub_81DD77C(0x64, sub_8199F30()))
        return 0;

    previousFlags = object->flags11E;
    object->flags11E = previousFlags & 0xF3FF;
    if (!(previousFlags & 0x400)) {
        modeFlags = &object->control120.bytes.flags122;
        if (!(*modeFlags & 0x40)) {
            object->attachment118 =
                sub_8086E8C(field_object_status_runtime_object(object));
            *modeFlags |= 0x40;
        }
        object->value128 = 0xFF;
        object->value126 = 1;
        object->value12A = 1;
        object->flags11E |= 0x800;
        goto update_control;
    }
    if ((u8)(object->value12C - 0x13) <= 1) {
update_control:
        object->control120.value =
            (object->control120.value & 0xFFFC7FFF) | 0x20000;
    }
    return 1;
}

#define DEFINE_STATUS_FLAG_CLAIM(symbol, flag)                            \
    SEC(symbol) s32 symbol(                                               \
        struct FieldObjectStatus* object, s32 threshold)                  \
    {                                                                     \
        s8* modeFlags;                                                    \
                                                                          \
        if (!(object->flags11E & (flag))                                  \
            && threshold >= sub_81DD77C(0x64, sub_8199F30())) {           \
            object->flags11E = (object->flags11E & 0x0FFF) | (flag);      \
            modeFlags = (s8*)&object->control120.bytes.flags122;          \
            *modeFlags = (*modeFlags & -0x1D) | 0x0C;                     \
            return 1;                                                     \
        }                                                                 \
        return 0;                                                         \
    }

DEFINE_STATUS_FLAG_CLAIM(sub_8108D8C, 0x4000)
DEFINE_STATUS_FLAG_CLAIM(sub_8108DE4, 0x2000)
DEFINE_STATUS_FLAG_CLAIM(sub_8108E3C, 0x1000)

SEC(sub_8108B50)
void field_object_play_sound_151_after_delay(
    struct FieldObjectStatusProcess* process)
{
    if (process->timer == 0 || --process->timer == 0) {
        sound_effect_play(0x151, -1);
        process->update = field_object_finish_variant_action_when_visual_ready;
    }
}

SEC(sub_8108CD0)
void field_object_consume_pending_action_request(struct FieldObjectStatus* owner)
{
    struct FieldObjectStatusProcess* process;
    u8* flags;

    if (owner->flags11E & 3) {
        if (owner->variantEC < 0 &&
            !(owner->control120.bytes.flags122 & 0x20)) {
            process = sub_807FFB8(field_object_prepare_variant_action);
            process->owner = owner;
            flags = &owner->control120.bytes.flags122;
            *flags |= 0x20;
        }
        owner->flags11E &= ~3;
    }
}
