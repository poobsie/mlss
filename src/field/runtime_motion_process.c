#include "field/actor.h"
#include "field/runtime_nodes.h"

#define SEC(symbol) \
    __attribute__((section(".text.field_runtime_motion_process." #symbol)))

struct FieldRuntimeMotionState {
    struct FieldRuntimeMotionState* next;
    s32 x;
    s32 y;
    u8* ownerActive;
    s16 velocityX;
    s16 velocityY;
    u16 unknown14;
    u16 countdown;
    s16 renderParameter;
};

void sub_80801BC(struct FieldRuntimeNode* process);

SEC(sub_807F834)
void field_runtime_countdown_then_motion(struct FieldRuntimeNode* process)
{
    struct FieldRuntimeMotionState* state = process->unknown0C;
    struct FieldRuntime* runtime = gFieldRuntime;
    u8 flags = runtime->flags0B;
    s32 updateMask = 2;
    FieldRuntimeNodeCallback callback;

    runtime->flags0B = (u8)(flags | updateMask);
    state->countdown--;
    if (state->countdown == 0) {
        state->countdown = 20;
        callback = sub_80801BC;
        process->ownerOrCallback = (void*)callback;
    }
}
