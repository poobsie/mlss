#ifndef GUARD_SCRIPT_ANIMATION_RUNTIME_H
#define GUARD_SCRIPT_ANIMATION_RUNTIME_H

#include "global.h"
#include "process/types.h"
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

struct AnimationSceneProcess {
    struct Process process;
    u32* completion;
};

struct AnimationFieldRuntime {
    u8 unknown000[0x248];
    void* layer248;
    u8 unknown24C[0x8C];
    void* optional2D8;
};

void sub_80E195C(struct AnimationAttachmentState*, struct AnimationAttachmentOwner*);
void sub_80E19A8(struct AnimationScriptState*);
void sub_80E19EC(struct AnimationOffsetState*);
void sub_80E1AB0(struct AnimationScriptState*);
void sub_80E2EDC(struct AnimationSceneProcess*, u32);
bool32 sub_80E3CF4(void);
void sub_80E3D1C(void);
void sub_80E3D70(void);
bool32 sub_80E3DA4(void);

#define animation_attachment_flush_pending sub_80E195C
#define animation_script_tick_terminal_wait sub_80E19A8
#define animation_offset_update sub_80E19EC
#define animation_script_apply_origin sub_80E1AB0
#define animation_scene_remove_process sub_80E2EDC
#define animation_scene_layer_is_active sub_80E3CF4
#define animation_scene_configure_layer sub_80E3D1C
#define animation_scene_clear_vram_regions sub_80E3D70
#define animation_scene_poll_runtime_ready sub_80E3DA4

#endif
