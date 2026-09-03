#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))

void sub_80873B8(struct RuntimeObject* object, s32 kind, s32 duration);
void sub_808B2D4(struct RuntimeObject* object);
void sub_808C62C(struct RuntimeObject* object);
void sub_808C65C(struct RuntimeObject* object);
void sub_808C68C(struct RuntimeObject* object);
void sub_808C6BC(struct RuntimeObject* object);
void sub_808C724(struct RuntimeObject* object);

#define DEFINE_FOLLOWUP_SETUP(name, kind, duration, next)              \
    SEC(name) void name(struct RuntimeObject* object)                   \
    {                                                                   \
        object->timer = duration;                                       \
        sub_80873B8(object, kind, duration);                            \
        object->followup = next;                                        \
    }

DEFINE_FOLLOWUP_SETUP(
    object_setup_followup_kind_2_for_12_ticks, 2, 12, sub_808B2D4)
DEFINE_FOLLOWUP_SETUP(
    object_setup_followup_kind_6_for_5_ticks_a, 6, 5, sub_808C62C)
DEFINE_FOLLOWUP_SETUP(
    object_setup_followup_kind_2_for_5_ticks_a, 2, 5, sub_808C65C)
DEFINE_FOLLOWUP_SETUP(
    object_setup_followup_kind_6_for_5_ticks_b, 6, 5, sub_808C68C)
DEFINE_FOLLOWUP_SETUP(
    object_setup_followup_kind_2_for_5_ticks_b, 2, 5, sub_808C6BC)
DEFINE_FOLLOWUP_SETUP(
    object_setup_followup_kind_7_for_3_ticks, 7, 3, sub_808C724)
