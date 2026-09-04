#ifndef GUARD_OBJECT_ANIMATION_EFFECT_CALLBACKS_H
#define GUARD_OBJECT_ANIMATION_EFFECT_CALLBACKS_H

#include "object/runtime_object.h"

void sub_8099FFC(struct RuntimeObject* object);
void sub_809A06C(struct RuntimeObject* object);

/* The mirrored callbacks differ only in the continuation they install. */
#define object_start_animation_2_save_position_a sub_8099FFC
#define object_start_animation_2_save_position_b sub_809A06C

#endif
