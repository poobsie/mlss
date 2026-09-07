#ifndef GUARD_SCRIPT_ANIMATION_RUNTIME_H
#define GUARD_SCRIPT_ANIMATION_RUNTIME_H

#include "global.h"
#include "script/animation_script.h"

struct AnimationAttachmentState {
    u8 unknown00[0x5C];
    s32 pendingX;
    s32 pendingY;
};

struct AnimationAttachmentOwner {
    u8 unknown00[8];
    u8 action[0x70];
    u16 pendingCommand;
    u16 pendingArgument;
    u8 unknown7C[2];
    s8 flags;
};

struct AnimationOffsetState {
    u8 unknown00[0x10];
    s16 positionX;
    s16 velocityX;
    s16 velocityY;
    s16 unknown16;
    s16 positionY;
};

void sub_80E195C(struct AnimationAttachmentState*, struct AnimationAttachmentOwner*);
void sub_80E19A8(struct AnimationScriptState*);
void sub_80E19EC(struct AnimationOffsetState*);
void sub_80E1AB0(struct AnimationScriptState*);

#define animation_attachment_flush_pending sub_80E195C
#define animation_script_tick_terminal_wait sub_80E19A8
#define animation_offset_update sub_80E19EC
#define animation_script_apply_origin sub_80E1AB0

#endif
