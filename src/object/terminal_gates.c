#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))

void sub_807C298(struct RuntimeObject* object);
void sub_808750C(struct RuntimeObject* object);

#define DEFINE_VISUAL_GATE(name, action)                               \
    SEC(name) void name(struct RuntimeObject* object)                   \
    {                                                                    \
        if (object->visual->flags & 8)                                  \
            action;                                                      \
    }

DEFINE_VISUAL_GATE(object_stop_when_visual_complete_a, object->update = 0)
DEFINE_VISUAL_GATE(object_stop_when_visual_complete_b, object->update = 0)
DEFINE_VISUAL_GATE(
    object_return_idle_when_visual_complete_a, object->update = sub_808750C)
DEFINE_VISUAL_GATE(
    object_return_idle_when_visual_complete_b, object->update = sub_808750C)
DEFINE_VISUAL_GATE(
    object_return_idle_when_visual_complete_c, object->update = sub_808750C)

#define DEFINE_PADDED_VALUE80_GATE(name, action)                       \
    SEC(name) void name(struct RuntimeObject* object)                   \
    {                                                                    \
        if (object->value80 == 0)                                       \
            action(object);                                              \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_PADDED_VALUE80_GATE(object_trigger_when_value80_clear_a, sub_807C298)
DEFINE_PADDED_VALUE80_GATE(object_trigger_when_value80_clear_b, sub_807C298)
DEFINE_PADDED_VALUE80_GATE(object_trigger_when_value80_clear_c, sub_807C298)
DEFINE_PADDED_VALUE80_GATE(object_cleanup_when_value80_clear_a, sub_8087540)
DEFINE_PADDED_VALUE80_GATE(object_cleanup_when_value80_clear_b, sub_8087540)
DEFINE_PADDED_VALUE80_GATE(object_cleanup_when_value80_clear_c, sub_8087540)
