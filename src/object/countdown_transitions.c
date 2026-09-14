#include "global.h"
#include "audio/sound_effects.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.countdown_transitions." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_COUNTDOWN_TRANSITION(name, kind, next)                   \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        s32 current;                                                     \
        if (object->visual->flags & 8) {                                \
            current = (u16)object->timer - 1;                            \
            object->timer = current;                                    \
            if ((s32)(current << 16) <= 0) {                            \
                sub_8082E1C(object, kind, 0, 0);                        \
                object->update = next;                                  \
            }                                                            \
        }                                                                \
    }

DEFINE_COUNTDOWN_TRANSITION(sub_805DF4C, 5, sub_805DA78)
DEFINE_COUNTDOWN_TRANSITION(sub_8063C8C, 13, sub_8063C60)
DEFINE_COUNTDOWN_TRANSITION(sub_806EADC, 11, sub_808750C)

extern void sub_808AA60(struct RuntimeObject*);
extern void sub_808A8F8(struct RuntimeObject*);
extern void sub_808A7B0(struct RuntimeObject*);
extern void sub_808A660(struct RuntimeObject*);
extern void sub_808A4D0(struct RuntimeObject*);
extern void sub_808A3C4(struct RuntimeObject*);
extern void sub_808A27C(struct RuntimeObject*);

#define DEFINE_PREDECREMENT_TIMER_TRANSITION(name, animation, next)          \
    MISC3_SEC(name) void name(struct RuntimeObject* object)                  \
    {                                                                        \
        u16 current = object->timer;                                         \
        object->timer = current - 1;                                         \
        if ((s32)(current << 16) <= 0) {                                    \
            sub_8082E1C(object, animation, 0, 0);                            \
            object->update = next;                                          \
        }                                                                    \
    }

DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_8_variant_a,
                                     8, sub_808AA60)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_4_variant_a,
                                     4, sub_808A8F8)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_8_variant_b,
                                     8, sub_808A7B0)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_4_variant_b,
                                     4, sub_808A660)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_9_variant_a,
                                     9, sub_808A4D0)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_5_variant_a,
                                     5, sub_808A3C4)
DEFINE_PREDECREMENT_TIMER_TRANSITION(object_countdown_then_animation_5_variant_b,
                                     5, sub_808A27C)

__attribute__((section(".text.timer_callbacks.sub_8132EE0")))
void object_countdown_then_animation_6(struct RuntimeObject* object) {
    u32 remaining = (u16)object->timer - 1U;
    object->timer = remaining;
    if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
        sub_8082E1C(object, 6, 0, 0);
        object->update = sub_8132678;
    }
}
__attribute__((section(".text.timer_callbacks.sub_8061830")))
void object_refresh_and_countdown_then_animation_7(struct RuntimeObject* object) {
    u32 remaining;
    sub_80614B4(object);
    remaining = (u16)object->timer - 1U;
    object->timer = remaining;
    if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
        sub_8082E1C(object, 7, 0, 0);
        object->update = sub_808750C;
    }
}

__attribute__((section(".text.timer_callbacks.sub_8132EA8")))
void object_countdown_then_animation_10_sound_9f(struct RuntimeObject* object) {
    u32 remaining = (u16)object->timer - 1U;
    object->timer = remaining;
    if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
        sub_8082E1C(object, 10, 0, 0);
        sound_effect_play(0x9F, -1);
        object->update = sub_8132818;
    }
}

__attribute__((section(".text.timer_callbacks.sub_8061864")))
void object_on_visual_complete_countdown_then_animation_5(struct RuntimeObject* object) {
    u32 remaining;
    sub_80614B4(object);
    if (OBJECT_VISUAL_COMPLETE & object->visual->flags) {
        remaining = (u16)object->timer - 1U;
        object->timer = remaining;
        if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
            sub_8082E1C(object, 5, 0, 0);
            object->update = sub_80616B8;
        }
    }
}

__attribute__((section(".text.timer_callbacks.sub_8065A5C")))
void object_when_value80_clear_animation_14_sound_af(struct RuntimeObject* object) {
    s32 duration;
    if (object->value80 == 0) {
        sub_8082E1C(object, 14, 0, 0);
        duration = object->valueA8;
        object->timer = duration;
        object->update = sub_8065BD8;
        sound_effect_stop(0x81);
        sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
    }
}

__attribute__((section(".text.timer_callbacks.sub_8132E68")))
void object_on_visual_complete_start_animation_5_sound_a0(struct RuntimeObject* object) {
    s32 duration;
    if (OBJECT_VISUAL_COMPLETE & object->visual->flags) {
        sub_8082E1C(object, 5, 0, 0);
        duration = object->behaviorState;
        object->timer = duration;
        sound_effect_play(0xA0, SOUND_VOLUME_UNCHANGED);
        object->update = object_countdown_then_animation_6;
    }
}

__attribute__((section(".text.timer_callbacks.sub_8063524")))
void object_on_visual_complete_countdown_animation_6_sound_ae(struct RuntimeObject* object) {
    u32 remaining;
    if (OBJECT_VISUAL_COMPLETE & object->visual->flags) {
        remaining = (u16)object->timer - 1U;
        object->timer = remaining;
        if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
            sub_8082E1C(object, 6, 0, 0);
            sound_effect_play(0xAE, SOUND_VOLUME_UNCHANGED);
            object->update = sub_8062FD4;
        }
    }
}

__attribute__((section(".text.timer_callbacks.sub_8062548")))
void object_on_visual_complete_select_animation_6_or_8(struct RuntimeObject* object) {
    u32 remaining;
    if (OBJECT_VISUAL_COMPLETE & object->visual->flags) {
        remaining = (u16)object->timer - 1U;
        object->timer = remaining;
        if (OBJECT_TIMER_NEGATIVE(remaining)) {
            if (object->behaviorState == 0) {
                sub_8082E1C(object, 6, 0, 0);
            } else {
                sub_8082E1C(object, 8, 0, 0);
            }

            object->update = sub_80621DC;
        }
    }
}

__attribute__((section(".text.timer_callbacks.sub_806C314")))
void object_on_visual_complete_branch_countdown_sequence(struct RuntimeObject* object) {
    RuntimeObjectCallback next;
    u32 remaining;
    if (OBJECT_VISUAL_COMPLETE & object->visual->flags) {
        remaining = (u16)object->timer - 1U;
        object->timer = remaining;
        if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
            sound_effect_stop(0x7C);
            if (object->valueA4 != 0) {
                if (object->valueA8 == 0) {
                    sub_8082E1C(object, 9, 0, 0);
                } else {
                    sub_8082E1C(object, 15, 0, 0);
                }
                next = sub_806C94C;
            } else {
                if (object->valueA8 == 0) {
                    sub_8082E1C(object, 30, 0, 0);
                } else {
                    sub_8082E1C(object, 31, 0, 0);
                }
                object->timer = 3;
                next = object_continue_visual_countdown_and_spawn_effect;
            }
            object->update = next;
        }
    }
}

s32 sub_8086858(struct RuntimeObject*, s32);

__attribute__((section(".text.timer_callbacks.sub_806C3AC")))
void object_continue_visual_countdown_and_spawn_effect(struct RuntimeObject* object) {
    s32 effect;
    u8 flags;
    u32 remaining;
    struct RuntimeObjectVisual* visual;
    if (OBJECT_VISUAL_COMPLETE & object->visual->flags) {
        remaining = (u16)object->timer - 1U;
        object->timer = remaining;
        if (OBJECT_TIMER_NONPOSITIVE(remaining)) {
            sound_effect_play(0x44, SOUND_VOLUME_UNCHANGED);
            object->behaviorState = 0;
            if (object->valueA8 == 0) {
                sub_8082E1C(object, 10, 0, 0);
                effect = 0x163A;
            } else {
                sub_8082E1C(object, 16, 0, 0);
                effect = 0x16BC;
            }
            OBJECT_SHARED_EFFECT_RESULT = sub_8086858(object, effect);
            flags = object->flags77;
            object->flags77 = flags | 0x40;
            object->auxiliaryUpdate = (RuntimeObjectCallback)sub_806C8C0;
            object->secondaryUpdate = sub_806C848;
            visual = object->visual;
            effect = object->valueA0;
            visual->parameter20 = effect;
            object->update = sub_806C8D8;
        }
    }
}
