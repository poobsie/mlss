#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))

void sub_80681EC(struct RuntimeObject* object);
void sub_8068B68(struct RuntimeObject* object);
void sub_806A22C(struct RuntimeObject* object);
void sub_806A638(struct RuntimeObject* object);
void sub_806B3D0(struct RuntimeObject* object);
void sub_806CD70(struct RuntimeObject* object);
void sub_8075C8C(struct RuntimeObject* object);
void sub_806123C(struct RuntimeObject* object);
void sub_810DD7C();

#define DEFINE_POSITION_OWNER_SETUP(name, next)                       \
    SEC(name) s32 name(struct RuntimeObject* object)                   \
    {                                                                  \
        sub_810DD7C(object, object->positionOwner, 0xFF);              \
        object->update = next;                                         \
        return 0;                                                      \
    }

DEFINE_POSITION_OWNER_SETUP(object_setup_from_position_owner_a, sub_80681EC)
DEFINE_POSITION_OWNER_SETUP(object_setup_from_position_owner_b, sub_8068B68)
DEFINE_POSITION_OWNER_SETUP(object_setup_from_position_owner_c, sub_806A22C)
DEFINE_POSITION_OWNER_SETUP(object_setup_from_position_owner_d, sub_806A638)

SEC(object_setup_from_position_owner_only)
s32 object_setup_from_position_owner_only(struct RuntimeObject* object)
{
    sub_810DD7C(object, object->positionOwner, 0xFF);
    return 0;
}

DEFINE_POSITION_OWNER_SETUP(object_setup_from_position_owner_e, sub_806B3D0)

SEC(object_setup_behavior_1_from_owner)
s32 object_setup_behavior_1_from_owner(
    struct RuntimeObject* object, void* owner)
{
    object->behaviorState = 1;
    sub_810DD7C(object, owner, 0xFF);
    return 0;
}
SEC(object_setup_behavior_1_from_owner)
const u16 object_setup_behavior_1_from_owner_padding = 0;

#define DEFINE_OWNER_SETUP(name, next)                                \
    SEC(name) s32 name(struct RuntimeObject* object, void* owner)      \
    {                                                                  \
        sub_810DD7C(object, owner, 0xFF);                              \
        object->update = next;                                         \
        return 0;                                                      \
    }

DEFINE_OWNER_SETUP(object_setup_from_owner_a, sub_806CD70)
DEFINE_OWNER_SETUP(object_setup_from_owner_b, sub_8075C8C)

SEC(object_setup_then_clear_value80)
s32 object_setup_then_clear_value80(struct RuntimeObject* object)
{
    sub_810DD7C();
    object->value80 = 0;
    object->update = sub_806123C;
    return 0;
}
