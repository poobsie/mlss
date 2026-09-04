#ifndef GUARD_RUNTIME_COMPACT_LEAVES_H
#define GUARD_RUNTIME_COMPACT_LEAVES_H

#include "global.h"

#define runtime_large_owner_clear_slots sub_8160EC4
#define runtime_embedded_object_at_0c sub_8150EFC

struct RuntimeLargeOwner;
struct RuntimeLargeOwner* runtime_large_owner_clear_slots(struct RuntimeLargeOwner* owner);
void* runtime_embedded_object_at_0c(void* owner);

#endif
