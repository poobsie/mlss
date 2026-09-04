#ifndef GUARD_OBJECT_ANIMATION_EFFECT_CALLBACKS_H
#define GUARD_OBJECT_ANIMATION_EFFECT_CALLBACKS_H

#include "object/runtime_object.h"

/* The mirrored callbacks differ only in the continuation they install. */
#define object_start_animation_2_save_position_a sub_8099FFC
#define object_start_animation_2_save_position_b sub_809A06C

void object_start_animation_2_save_position_a(struct RuntimeObject* object);
void object_start_animation_2_save_position_b(struct RuntimeObject* object);

#endif
