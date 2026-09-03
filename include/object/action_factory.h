#ifndef GUARD_OBJECT_ACTION_FACTORY_H
#define GUARD_OBJECT_ACTION_FACTORY_H

#include "global.h"

typedef void (*ObjectActionUpdate)(void);

void sub_80DEEA8(
    u32 coordinate0, u32 coordinate1, u32 coordinate2, u32 eventId,
    ObjectActionUpdate update, u32 visualId, u32 visualVariant,
    u32 pathMode, u32 pointCount, u32 objectOrientation,
    u32 visualOrientation, const void* pointData, u32 trailingPointCount);

#define object_create_scripted_action sub_80DEEA8

#endif
