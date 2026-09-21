#include "global.h"
#include "object/runtime_leaf_callbacks.h"
#include "object/runtime_object.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.object_visual_setups." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
extern u32 sub_8199F30(void);
extern s32 sub_81DD77C(u32 limit, s32 value);
extern void sub_809400C(struct RuntimeObject* object);
extern void sub_8094070(struct RuntimeObject* object);

struct ObjectSnapshotDisplayState {
    u8 unknown00[0x2A];
    u16 snapshot2A;
};

struct ObjectSnapshotRuntime {
    u8 unknown00[0x3C];
    struct ObjectSnapshotDisplayState display3C;
};

#define OBJECT_SNAPSHOT_RUNTIME \
    (*(struct ObjectSnapshotRuntime**)0x03000FF4)

SEC(sub_8093F08)
s32 object_initialize_snapshot_animation_with_random_duration(
    struct RuntimeObject* object)
{
    struct ObjectSnapshotDisplayState* display;
    volatile u8* objectFlags;
    s8* visualFlags;
    s32 flagValue;
    s32 mask;
    s32 duration;

    object->descriptor = (const void*)0x084FE9A4;
    display = &OBJECT_SNAPSHOT_RUNTIME->display3C;
    objectFlags = &object->flags77;
    flagValue = *objectFlags;
    mask = -0x41;
    flagValue &= mask;
    mask = -0x21;
    flagValue &= mask;
    *objectFlags = flagValue;
    object->state->displaySnapshot = display->snapshot2A;

    duration = sub_81DD77C(5, sub_8199F30()) + 10;
    if (duration != 0) {
        sub_8082E1C(object, 4, 0x204D, 0);
        visualFlags = (s8*)&object->visual->flags;
        *visualFlags &= -7;
        object->behaviorState = duration;
        object->update = sub_8094070;
    } else {
        object->update = sub_809400C;
    }
    return 1;
}

#define DEFINE_OBJECT_VISUAL_SETUP(name, sprite_value, behavior_state, next) \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        volatile u8 *flags;                                              \
        s32 flag_value;                                                  \
        s32 mask;                                                        \
        void *display;                                                   \
        object->descriptor = (void *)0x084FE9A4;                         \
        display = (u8 *)(*(void **)0x03000FF4) + 0x3C;                 \
        flags = &object->flags77;                                       \
        flag_value = *flags;                                             \
        mask = -0x41;                                                    \
        flag_value &= mask;                                              \
        mask = -0x21;                                                    \
        flag_value &= mask;                                              \
        *flags = flag_value;                                             \
        object->state->displaySnapshot =                                    \
            FIELD(display, u16, 0x2A);                                  \
        sub_8082E1C(object, 4, 0x204D, 0);                              \
        object->visual->parameter20 = sprite_value;                      \
        object->behaviorState = behavior_state;                         \
        object->update = next;                                          \
        return 1;                                                        \
    }

DEFINE_OBJECT_VISUAL_SETUP(sub_808ED40, 0x30, 2, sub_808EE0C)
DEFINE_OBJECT_VISUAL_SETUP(sub_808FD3C, 0x10, 6, sub_808FE08)
DEFINE_OBJECT_VISUAL_SETUP(sub_8090AB4, 0x60, 1, sub_8090B80)
