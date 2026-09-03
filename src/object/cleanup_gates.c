#include "global.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_flag_gates." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

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
