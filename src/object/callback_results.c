#include "global.h"
#include "object/functions.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.callback_results." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))

#define DEFINE_CALLBACK_RESULT(name, next)                               \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        object->update = next;                                          \
        return 1;                                                        \
    }

DEFINE_CALLBACK_RESULT(sub_8099028, sub_8099034)
DEFINE_CALLBACK_RESULT(sub_80993BC, sub_80993C8)

void sub_808C348(struct RuntimeObject* object);
void sub_808C4C8(struct RuntimeObject* object);
void sub_809CA24(struct RuntimeObject* object);
void sub_809D2A8(struct RuntimeObject* object);

#define DEFINE_MISC_CALLBACK_RESULT(name, next)                        \
    MISC_SEC(name) s32 name(struct RuntimeObject* object)               \
    {                                                                   \
        object->update = next;                                          \
        return 1;                                                       \
    }

DEFINE_MISC_CALLBACK_RESULT(
    object_install_update_and_return_true_a, sub_808C348)
DEFINE_MISC_CALLBACK_RESULT(
    object_install_update_and_return_true_b, sub_808C4C8)

MISC_SEC(object_install_update_a)
void object_install_update_a(struct RuntimeObject* object)
{
    object->update = sub_809CA24;
}

DEFINE_MISC_CALLBACK_RESULT(
    object_install_update_and_return_true_c, sub_809D2A8)
