#include "object/functions.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

struct ObjectLinkedGateOwner {
    u8 unknown00[8];
    void** activeEntry;
};

struct ObjectLinkedGate {
    u8 unknown00[4];
    struct ObjectLinkedGateOwner* owner;
};

void sub_8065C5C(struct RuntimeObject* object);
void sub_806AA18(struct RuntimeObject* object);
void sub_806B56C(struct RuntimeObject* object);
void sub_8079C3C(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_808750C(struct RuntimeObject* object);
s32 sub_8087CE4();

SEC(object_release_linked_object_then_idle)
void object_release_linked_object_then_idle(struct RuntimeObject* object)
{
    if (object->linkedObject != 0)
        sub_807C298(object->linkedObject);
    object->update = sub_808750C;
}

SEC(object_when_value80_clear_release_linked_and_delay_3)
void object_when_value80_clear_release_linked_and_delay_3(struct RuntimeObject* object)
{
    if (object->value80 == 0) {
        sub_807C298(object->linkedObject);
        object->timer = 3;
        object->update = sub_8065C5C;
    }
}

#define DEFINE_LINKED_CLEAR_ANIMATION(name, animation, next)           \
    SEC(name) void name(struct RuntimeObject* object)                   \
    {                                                                   \
        if (object->linkedObject == 0) {                               \
            sub_8082E1C(object, animation, 0, 0);                     \
            object->update = next;                                     \
        }                                                               \
    }

DEFINE_LINKED_CLEAR_ANIMATION(object_when_linked_object_clear_start_animation_0, 0, sub_808750C)
DEFINE_LINKED_CLEAR_ANIMATION(object_when_linked_object_clear_start_animation_8, 8, sub_806B56C)

SEC(object_start_animation_5_and_delay_0)
void object_start_animation_5_and_delay_0(struct RuntimeObject* object)
{
    sub_8082E1C(object, 5, 0, 0);
    object->update = sub_806AA18;
    object->timer = 0;
}

#define DEFINE_NESTED_ENTRY_GATE(name)                                 \
    SEC(name) void name(struct RuntimeObject* object)                   \
    {                                                                   \
        struct RuntimeObject* linked;                                  \
        struct ObjectLinkedGate* gate;                                 \
        void* entry;                                                    \
        linked = object->linkedObject;                                 \
        gate = (struct ObjectLinkedGate*)linked;                       \
        entry = *gate->owner->activeEntry;                             \
        if (entry == 0) {                                               \
            sub_807C298(linked);                                       \
            object->linkedObject = entry;                              \
            object->update = entry;                                    \
        }                                                               \
    }

DEFINE_NESTED_ENTRY_GATE(object_release_linked_when_owner_entry_clear_a)
DEFINE_NESTED_ENTRY_GATE(object_release_linked_when_owner_entry_clear_b)

SEC(object_when_linked_update_stops_start_animation_12)
void object_when_linked_update_stops_start_animation_12(struct RuntimeObject* object)
{
    if (object->linkedObject->update == 0) {
        sub_8082E1C(object, 0x12, 0, 0);
        object->update = sub_8079C3C;
    }
}

SEC(object_when_ready_release_linked_and_self)
void object_when_ready_release_linked_and_self(struct RuntimeObject* object)
{
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_807C298(object->linkedObject);
        sub_807C298(object);
    }
}
