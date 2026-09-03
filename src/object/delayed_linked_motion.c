#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_delayed_linked_motion." #name)))

void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);

#define DEFINE_DELAYED_LINKED_MOTION(name, next)                         \
    void next(struct RuntimeObject*);                                    \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        struct RuntimeObject* linked;                                    \
        struct RuntimeObjectVisual* visual;                              \
        u8 flags;                                                        \
                                                                         \
        if (object->flags76 & 0x38) {                                    \
            runtime_object_finish_action(object);                        \
            return;                                                      \
        }                                                                \
        if (object->behaviorState > 0) {                                 \
            object->behaviorState--;                                     \
            return;                                                      \
        }                                                                \
        linked = object->linkedObject;                                   \
        linked->valueA0 = 0xB400;                                        \
        linked->valueA4 = -0x1CC;                                        \
        sub_8082E1C(object, 2, 0, 0);                                   \
        visual = object->visual;                                         \
        flags = visual->flags;                                           \
        visual->flags = flags | 0x10;                                   \
        object->update = next;                                           \
    }

DEFINE_DELAYED_LINKED_MOTION(sub_8091BE0, sub_80913A4)
DEFINE_DELAYED_LINKED_MOTION(sub_8092D70, sub_8092534)
DEFINE_DELAYED_LINKED_MOTION(sub_8093DBC, sub_8093580)
