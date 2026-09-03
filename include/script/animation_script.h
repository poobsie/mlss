#ifndef GUARD_SCRIPT_ANIMATION_SCRIPT_H
#define GUARD_SCRIPT_ANIMATION_SCRIPT_H

#include "global.h"

struct AnimationScriptState;
typedef void (*AnimationScriptUpdate)(struct AnimationScriptState* state);

struct AnimationScriptState {
    u32 unknown0;
    AnimationScriptUpdate update;
    void* owner;
    const u8* cursor;
    s16 waitTimer;
    s16 originX;
    s16 originY;
    s16 originZ;
};

void animation_script_enter_10_byte_stream(struct AnimationScriptState* state);
void animation_script_enter_4_byte_stream(struct AnimationScriptState* state);
void animation_script_enter_command_stream(struct AnimationScriptState* state);
void animation_script_update_10_byte_stream(struct AnimationScriptState* state);
void animation_script_update_4_byte_stream(struct AnimationScriptState* state);
void animation_script_update_command_stream(struct AnimationScriptState* state);

#endif
