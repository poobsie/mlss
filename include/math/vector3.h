#ifndef GUARD_MATH_VECTOR3_H
#define GUARD_MATH_VECTOR3_H

#include "global.h"

struct Vector3 {
    s32 x;
    s32 y;
    s32 z;
};

#define vector3_copy sub_8136688

void vector3_copy(struct Vector3* destination, const struct Vector3* source);

#endif
