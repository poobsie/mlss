#include "math/vector3.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

SEC(sub_8136688) void vector3_copy(struct Vector3* destination,
                                  const struct Vector3* source)
{
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
}

SEC(sub_8136688) const u16 vector3_copy_padding = 0;
