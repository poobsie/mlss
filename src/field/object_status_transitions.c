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
        if (owner->variantEC < 0 && !(owner->flags122 & 0x20)) {
            process = sub_807FFB8(field_object_prepare_variant_action);
            process->owner = owner;
            flags = &owner->flags122;
            *flags |= 0x20;
        }
        owner->flags11E &= ~3;
    }
}
