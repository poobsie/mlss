#include "global.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.callback_results." #name)))

#define DEFINE_CALLBACK_RESULT(name, next)                               \
    extern void next(struct RuntimeObject*);                             \
    SEC(name) s32 name(struct RuntimeObject* object)                     \
    {                                                                    \
        object->update = next;                                          \
        return 1;                                                        \
    }

DEFINE_CALLBACK_RESULT(sub_8099028, sub_8099034)
DEFINE_CALLBACK_RESULT(sub_80993BC, sub_80993C8)
