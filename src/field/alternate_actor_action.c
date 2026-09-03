#include "audio/sound_effects.h"
#include "field/selection_sequence.h"
#include "object/runtime_object.h"

void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808842C(struct RuntimeObject* object, s32 value, s32 duration);
void sub_808843C(struct RuntimeObject* object, s32 x, s32 y, s32 z, s32 scale);
void sub_8106F8C(struct FieldSelectionProcess* process);
void sub_810C950(void);

#define SEC(symbol) __attribute__((section(".text.small_functions_12." #symbol)))
#define FIELD_RUNTIME (*(struct FieldSelectionRuntime**)0x03000FD8)

SEC(sub_80FD8BC)
void field_start_alternate_actor_action(struct FieldSelectionProcess* process)
{
    s32 command;
    s32 targetAddress;
    s32 y;
    s32 x;
    struct FieldSelectionRuntime* runtime;

    if (!(FIELD_RUNTIME->flags00B & 4)) {
        sub_810C950();
        runtime = FIELD_RUNTIME;
        if (runtime->flags2C0 & 4) {
            targetAddress = (s32)runtime->object80 + 8;
            x = 0x28;
            y = 0x7C;
            command = 0x2039;
        } else {
            targetAddress = (s32)runtime->object84 + 8;
            x = 0x36;
            y = 0x5C;
            command = 0x2068;
        }
        sub_8082E1C((struct RuntimeObject*)targetAddress, 3, command, 0);
        sub_808843C((struct RuntimeObject*)targetAddress, x, y, 0, 0x100);
        sub_808842C((struct RuntimeObject*)targetAddress, 0x400, 0x20);
        process->update = sub_8106F8C;
        sub_8106F8C(process);
        sound_effect_play(0x2B, SOUND_VOLUME_UNCHANGED);
    }
}
