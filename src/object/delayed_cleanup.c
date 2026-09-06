#include "global.h"
#include "object/runtime_leaf_callbacks.h"
#define SEC(name) __attribute__((section(".text.delayed_cleanup_transitions." #name)))
#define DEFINE_DELAYED_CLEANUP_TRANSITION(name, limit)                   \
    SEC(name) void name(struct RuntimeObject* object)                    \
    {                                                                    \
        struct RuntimeObjectState* state = object->state;                \
        if (state != 0)                                                  \
            state->flags111 &= -5;                                      \
        if (object->flags76 & 0x38)                                     \
            runtime_object_finish_action(object);                        \
        else if (object->timer++ > limit)                               \
            runtime_object_finish_action(object);                        \
    }
DEFINE_DELAYED_CLEANUP_TRANSITION(sub_808EBB8, 0x17)
DEFINE_DELAYED_CLEANUP_TRANSITION(object_finish_action_on_flags_38_or_after_20_ticks, 0x13)
DEFINE_DELAYED_CLEANUP_TRANSITION(sub_808FBB4, 0x17)
DEFINE_DELAYED_CLEANUP_TRANSITION(sub_808FC04, 0x13)
DEFINE_DELAYED_CLEANUP_TRANSITION(object_finish_action_on_flags_38_or_after_24_ticks_later, 0x17)
DEFINE_DELAYED_CLEANUP_TRANSITION(object_finish_action_on_flags_38_or_after_20_ticks_later, 0x13)
