#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

s32 sub_8082B00(void);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_805DEDC(struct RuntimeObject* object);
void sub_805F6BC(struct RuntimeObject* object);
void sub_805FF80(struct RuntimeObject* object);
void sub_8061480(struct RuntimeObject* object);
void sub_8062420(struct RuntimeObject* object);
void sub_8062E98(struct RuntimeObject* object);
void sub_8063568(struct RuntimeObject* object);
void sub_8064558(struct RuntimeObject* object);
void sub_8065428(struct RuntimeObject* object);
void sub_80659E0(struct RuntimeObject* object);
void sub_8066DA4(struct RuntimeObject* object);
void sub_8066EE0(struct RuntimeObject* object);
void sub_806829C(struct RuntimeObject* object);
void sub_806A3F8(struct RuntimeObject* object);

#define DEFINE_READY_ANIMATION(name, animation, next)                 \
    SEC(name) void name(struct RuntimeObject* object)                  \
    {                                                                  \
        if (sub_8082B00() == 0) {                                     \
            sub_8082E1C(object, animation, 0, 0);                     \
            object->update = next;                                    \
        }                                                              \
    }

DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_3_a, 3, sub_805DEDC)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_a, 2, sub_805F6BC)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_b, 2, sub_805FF80)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_c, 2, sub_8061480)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_d, 2, sub_8062420)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_e, 2, sub_8062E98)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_3_b, 3, sub_8063568)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_f, 2, sub_8064558)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_g, 2, sub_8065428)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_h, 2, sub_80659E0)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_i, 2, sub_8066DA4)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_j, 2, sub_8066EE0)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_k, 2, sub_806829C)
DEFINE_READY_ANIMATION(object_when_field_ready_start_animation_2_l, 2, sub_806A3F8)
