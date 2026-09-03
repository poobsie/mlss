#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_state_action." #name)))

void sub_807FF48(void* callback, struct RuntimeObjectState* state);
void sub_807B7A8(struct RuntimeObjectState* state);

SEC(sub_8086700) s32 sub_8086700(struct RuntimeObject* object)
{
    s32 maskedFlags;
    u8 stateFlags;
    u8 flags;
    struct RuntimeObjectState* state;

    maskedFlags = object->flags76 & 6;
    if ((maskedFlags != 6) && (maskedFlags != 2)) {
        state = object->state;
        if (state != NULL) {
            stateFlags = state->flags111 & 2;
            if (stateFlags == 0) {
                object->update = (RuntimeObjectCallback)0x08087441;
                object->value80 = stateFlags;
                sub_807FF48((void*)0x0808742D, state);
                flags = state->flags111;
                state->flags111 = flags | 1;
                sub_807B7A8(object->state);
                return 1;
            }
        }
    }
    return 0;
}
