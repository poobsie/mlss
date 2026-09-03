#include "field/functions.h"
#include "field/scene_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SECTION(name) \
    __attribute__((section(".text.text_late_helpers." STRINGIFY(name))))
#define BYTE_AT(object, offset) (*(u8*)((u8*)(object) + (offset)))

void sub_813C6E4(void* context, struct FieldSceneObject* object);
void sub_813D6FC(void* context, struct FieldSceneObject* object);
void sub_813D850(void* context, struct FieldSceneObject* object);
void sub_8143374(void* context, struct FieldSceneObject* object);

#define DEFINE_FLAG_DISPATCH(name, target)                              \
    SECTION(name) void name(void* context, struct FieldSceneObject* object) { \
        BYTE_AT(object, 0x33E) |= 0x10;                               \
        BYTE_AT(object, 0x2B6) |= 0x40;                               \
        target(context, object);                                       \
    }

DEFINE_FLAG_DISPATCH(field_set_dispatch_flags_variant_a, sub_813C6E4)
DEFINE_FLAG_DISPATCH(field_set_dispatch_flags_variant_b, sub_813D6FC)
DEFINE_FLAG_DISPATCH(field_set_dispatch_flags_variant_c, sub_813D850)
DEFINE_FLAG_DISPATCH(field_set_dispatch_flags_variant_d, sub_8143374)
