#ifndef GUARD_FIELD_RUNTIME_RESOURCE_TEARDOWN_H
#define GUARD_FIELD_RUNTIME_RESOURCE_TEARDOWN_H

#include "global.h"

struct FieldRuntimeResourceTeardown {
    u8 unknown00[4];
    void (*callback)(struct FieldRuntimeResourceTeardown* teardown);
};

#define field_release_runtime_resource_and_continue sub_8106EE8

void field_release_runtime_resource_and_continue(
    struct FieldRuntimeResourceTeardown* teardown);

#endif
