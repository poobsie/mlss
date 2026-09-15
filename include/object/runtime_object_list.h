#ifndef GUARD_OBJECT_RUNTIME_OBJECT_LIST_H
#define GUARD_OBJECT_RUNTIME_OBJECT_LIST_H

#include "object/runtime_object.h"

#define runtime_object_prepend_with_shared_callback sub_807F4C4
#define runtime_object_prepend_to_active_list sub_807F4FC

void runtime_object_prepend_with_shared_callback(
    struct RuntimeObject* object, RuntimeObjectCallback callback);
void runtime_object_prepend_to_active_list(struct RuntimeObject* object);

#endif
