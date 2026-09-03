#include "global.h"
#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_flag_gates." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_807C298(struct RuntimeObject* object);
s32 sub_8087CE4();
s32 sub_80884AC();

#define DEFINE_OBJECT_FLAG_GATE(name)                                    \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        if (object->visual->flags & 8)                                  \
            sub_8087540(object);                                         \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_OBJECT_FLAG_GATE(sub_808C070)
DEFINE_OBJECT_FLAG_GATE(sub_808C098)
DEFINE_OBJECT_FLAG_GATE(sub_808C0C0)
DEFINE_OBJECT_FLAG_GATE(sub_808C0E8)
DEFINE_OBJECT_FLAG_GATE(sub_808C19C)

#define DEFINE_VISUAL_DISABLE(name)                                    \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        if (object->visual->flags & 8) {                               \
            sub_8082E1C(object, -1, -1, 0);                           \
            object->update = 0;                                        \
        }                                                               \
    }

DEFINE_VISUAL_DISABLE(object_on_visual_complete_disable_a)
DEFINE_VISUAL_DISABLE(object_on_visual_complete_disable_b)
DEFINE_VISUAL_DISABLE(object_on_visual_complete_disable_c)
DEFINE_VISUAL_DISABLE(object_on_visual_complete_disable_d)

#define DEFINE_VISUAL_CLEANUP(name, animation)                         \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        if (object->visual->flags & 8) {                               \
            sub_8082E1C(object, animation, 0, 0);                     \
            sub_8087540(object);                                       \
        }                                                               \
    }

DEFINE_VISUAL_CLEANUP(object_on_visual_complete_cleanup_animation_6, 6)
DEFINE_VISUAL_CLEANUP(object_on_visual_complete_cleanup_animation_0_a, 0)
DEFINE_VISUAL_CLEANUP(object_on_visual_complete_cleanup_animation_0_b, 0)
DEFINE_VISUAL_CLEANUP(object_on_visual_complete_cleanup_animation_0_c, 0)
DEFINE_VISUAL_CLEANUP(object_on_visual_complete_cleanup_animation_0_d, 0)

MISC_SEC(object_when_value80_clear_invoke_cleanup_callback)
void object_when_value80_clear_invoke_cleanup_callback(
    struct RuntimeObject* object)
{
    s32 value;
    RuntimeObjectCallback cleanup;

    value = object->value80;
    if (value == 0) {
        cleanup = object->cleanup;
        if (cleanup != 0)
            cleanup(object);
        object->descriptor = (void*)value;
    }
}

MISC_SEC(object_on_visual_complete_invoke_cleanup_callback)
void object_on_visual_complete_invoke_cleanup_callback(
    struct RuntimeObject* object)
{
    RuntimeObjectCallback cleanup;

    if (object->visual->flags & 8) {
        cleanup = object->cleanup;
        if (cleanup != 0)
            cleanup(object);
        object->descriptor = 0;
    }
}
MISC_SEC(object_on_visual_complete_invoke_cleanup_callback)
const u16 object_on_visual_complete_invoke_cleanup_callback_padding = 0;

#define DEFINE_FLAG20_STOP(name)                                      \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                   \
        sub_8087CE4();                                                  \
        if (object->flags79 & 0x20) {                                  \
            object->update = 0;                                        \
            object->value74 = 0;                                       \
        }                                                               \
    }                                                                   \
    MISC_SEC(name) const u16 name##_padding = 0;

DEFINE_FLAG20_STOP(object_when_flag20_set_stop_and_clear_value74_a)
DEFINE_FLAG20_STOP(object_when_flag20_set_stop_and_clear_value74_b)

MISC_SEC(object_poll_then_stop_on_flag20)
void object_poll_then_stop_on_flag20(struct RuntimeObject* object)
{
    sub_80884AC();
    if (object->flags79 & 0x20)
        object->update = 0;
}

MISC_SEC(object_poll_then_release_on_flag20)
void object_poll_then_release_on_flag20(struct RuntimeObject* object)
{
    sub_8087CE4();
    if (object->flags79 & 0x20)
        sub_807C298(object);
}
MISC_SEC(object_poll_then_release_on_flag20)
const u16 object_poll_then_release_on_flag20_padding = 0;

MISC_SEC(object_when_ready_release)
void object_when_ready_release(struct RuntimeObject* object)
{
    if ((sub_8087CE4() << 0x18) == 0)
        sub_807C298(object);
}
MISC_SEC(object_when_ready_release)
const u16 object_when_ready_release_padding = 0;

MISC_SEC(object_when_ready_release_and_stop_sound_10c)
void object_when_ready_release_and_stop_sound_10c(struct RuntimeObject* object)
{
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_807C298(object);
        sound_effect_stop(0x10C);
    }
}
MISC_SEC(object_when_ready_release_and_stop_sound_10c)
const u16 object_when_ready_release_and_stop_sound_10c_padding = 0;

MISC_SEC(object_when_value80_clear_stop_sound_11a_and_cleanup)
void object_when_value80_clear_stop_sound_11a_and_cleanup(
    struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sound_effect_stop(0x11A);
        sub_8087540(object);
    }
}

MISC_SEC(object_when_value80_clear_mark_visual_flag40_and_cleanup)
void object_when_value80_clear_mark_visual_flag40_and_cleanup(
    struct RuntimeObject* object)
{
    struct RuntimeObjectVisual* visual;
    u8 flags;

    if (object->value80 == 0) {
        sound_effect_stop(0x6C);
        visual = object->visual;
        flags = visual->flags11;
        flags |= 0x40;
        visual->flags11 = flags;
        sub_8087540(object);
    }
}
