#include "global.h"
#include "mario_bros/functions.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_geometry_" #name)))

#define DEFINE_OFFSET_AND_CLAMP(name)                   \
    MB_SECTION(name) s32 name(s32 value, u16 flags) {   \
        value += (flags & 1) ? 0x28 : 0x38;             \
        if (value >= 0) {                               \
            if (value > 0x40F)                          \
                value = 0x410;                          \
        }                                               \
        return value;                                   \
    }

DEFINE_OFFSET_AND_CLAMP(mario_bros_offset_and_clamp_coordinate_a)
DEFINE_OFFSET_AND_CLAMP(mario_bros_offset_and_clamp_coordinate_b)

#define DEFINE_HORIZONTAL_EDGE_DISTANCE(name)                               \
    MB_SECTION(name) s32 name(s32 x, s32 y, s32 xLimit, s32 yLimit) {       \
        if (x < 0 || x > xLimit)                                            \
            return 0;                                                       \
        if (y < 0) {                                                        \
            s32 inverted = ~y;                                              \
            y = inverted + 1;                                               \
        }                                                                   \
        if (y > yLimit)                                                     \
            return 0;                                                       \
        return xLimit - x;                                                  \
    }

DEFINE_HORIZONTAL_EDGE_DISTANCE(mario_bros_measure_horizontal_edge_distance_a)
DEFINE_HORIZONTAL_EDGE_DISTANCE(mario_bros_measure_horizontal_edge_distance_b)

#define DEFINE_UPPER_EDGE_DISTANCE(name)                              \
    MB_SECTION(name) s32 name(s32 x, s32 y, s32 xLimit, s32 yLimit) {\
        if (y < 0 || y > yLimit || y < (yLimit >> 1))                 \
            return -1;                                               \
        if (x < 0) {                                                  \
            s32 inverted = ~x;                                       \
            x = inverted + 1;                                        \
        }                                                             \
        if (x > xLimit)                                               \
            return -1;                                               \
        return yLimit - y;                                           \
    }

DEFINE_UPPER_EDGE_DISTANCE(mario_bros_measure_upper_edge_distance_a)
DEFINE_UPPER_EDGE_DISTANCE(mario_bros_measure_upper_edge_distance_b)
