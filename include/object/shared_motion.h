#ifndef GUARD_OBJECT_SHARED_MOTION_H
#define GUARD_OBJECT_SHARED_MOTION_H

#include "object/runtime_object.h"

#define object_update_shared_motion_xy sub_8063248
#define object_update_shared_motion_xz sub_8064908

void object_update_shared_motion_xy(struct RuntimeObject* object);
void object_update_shared_motion_xz(struct RuntimeObject* object);

#endif
