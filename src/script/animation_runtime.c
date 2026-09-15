#include "script/animation_runtime.h"
#include "field/runtime_nodes.h"

#define SEC(name) __attribute__((section(".text.animation_runtime." #name)))
#define PAD(name) SEC(name) const u16 name##_padding = 0
#define ANIMATION_FIELD_RUNTIME (*(struct AnimationFieldRuntime**)0x03000FD8)
#define DISPLAY_X_SHADOW (*(volatile u16*)0x02000018)
#define DISPLAY_Y_SHADOW (*(volatile u16*)0x0200001A)

struct AnimationAction {
    u8 unknown00[0x12];
    u8 flags;
};

extern void sub_807F6D0(void);
extern void sub_8082E1C(void* object, s32 animation, s32 command, s32 argument);
extern void sub_807FC54(void* object, s32 x, s32 y, s32 z, s32 argument);
extern void sub_807FB34(void* object);
extern void sub_80DF024(s32 effect, s32 x, s32 y, s32 z, void* owner);

SEC(sub_80E12F8)
void animation_offset_set_velocity(s32 velocityX, s32 velocityY)
{
    struct AnimationOffsetState* state;

    state = ANIMATION_FIELD_RUNTIME->offsetState274;
    if (state == 0) {
        state = (struct AnimationOffsetState*)field_runtime_push_node_list_40(
            animation_offset_update);
    }
    state->velocityX = velocityX;
    state->velocityY = velocityY;
    state->positionX = DISPLAY_X_SHADOW << 8;
    state->positionY = DISPLAY_Y_SHADOW << 8;
    ANIMATION_FIELD_RUNTIME->offsetState274 = state;
}

SEC(sub_80E195C)
void sub_80E195C(struct AnimationAttachmentState* state,
                 struct AnimationAttachmentOwner* owner)
{
    u16 command = owner->pendingCommand;
    u16 argument = owner->pendingArgument;

    owner->pendingCommand = 0;
    owner->pendingArgument = 0;
    state->pendingX = 0;
    state->pendingY = 0;
    if (command != 0 && (owner->flags & 0x38) != 0) {
        sub_8082E1C(owner->action, argument, command, 0);
        owner->flags &= -0x39;
    }
}
PAD(sub_80E195C);

SEC(sub_80E19A8)
void sub_80E19A8(struct AnimationScriptState* state)
{
    if (state->waitTimer > 0) {
        state->waitTimer--;
    } else {
        sub_807F6D0();
        state->update = 0;
    }
}
PAD(sub_80E19A8);

SEC(sub_80E19EC)
void sub_80E19EC(struct AnimationOffsetState* state)
{
    state->positionX += state->velocityX;
    state->positionY += state->velocityY;
    *(s16*)0x02000018 = state->positionX / 0x100;
    *(s16*)0x0200001A = state->positionY / 0x100;
}

SEC(sub_80E1AB0)
void sub_80E1AB0(struct AnimationScriptState* state)
{
    struct AnimationAction* action = state->owner;

    if ((action->flags & 8) == 0) {
        sub_807FC54(action, state->originX, state->originY, state->originZ, 0);
    } else {
        sub_807FB34(action);
        state->update = 0;
    }
}
PAD(sub_80E1AB0);

SEC(animation_script_update_4_byte_stream)
void animation_script_update_4_byte_stream(struct AnimationScriptState* state)
{
    if (state->waitTimer == 0) {
        do {
            const u16* record = (const u16*)state->cursor;
            sub_80DF024(record[0], state->originX, state->originY,
                        state->originZ, state->owner);
            state->waitTimer = record[1];
            state->cursor = (const u8*)(record + 2);
        } while (state->waitTimer == 0);
    }

    if (state->waitTimer < 0)
        state->update = 0;
    else
        state->waitTimer--;
}
