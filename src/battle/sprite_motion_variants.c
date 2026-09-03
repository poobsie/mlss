#include "battle/sprite_motion.h"

#define SEC(name) __attribute__((section(".text.text_upper_structural." #name)))

extern void* sub_815F8F4(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*);
extern void sub_815F97C(struct BattleSpriteMotion*, s32);
extern struct BattleSprite* sub_815FA3C(struct BattleSpriteMotion*);
extern void sub_815FA70(struct BattleSpriteMotion*, s32);
extern void sub_815FAFC(struct BattleSpriteMotion*);
extern void sub_815FB14(struct BattleSpriteMotion*, void*);
extern void sub_815FAA4(struct BattleSpriteMotion*, void*);
extern void sub_8021308(void*);

struct BattleSpritePosition {
    u16 x;
    u16 y;
};

#define DEFINE_INITIALIZER(name, descriptor_value)                       \
SEC(name) void* name(                                                    \
    struct BattleSpriteMotion* object,                                   \
    const struct BattleSpriteMotionConfig* config, u16 value)            \
{                                                                        \
    sub_815F8F4(object, config);                                         \
    object->descriptor = (void*)(descriptor_value);                      \
    object->slot34.values.value = value;                                 \
    sub_815F97C(object, 0);                                              \
    return object;                                                       \
}

#define DEFINE_POSITION_SNAPSHOT_INITIALIZER(name, descriptor_value)     \
SEC(name) void* name(                                                    \
    struct BattleSpriteMotion* object,                                   \
    const struct BattleSpriteMotionConfig* config, u16 value)            \
{                                                                        \
    u32 x;                                                               \
    u32 y;                                                               \
    sub_815F8F4(object, config);                                         \
    object->descriptor = (void*)(descriptor_value);                      \
    object->slot34.values.value = value;                                 \
    x = object->positionX;                                               \
    y = object->positionY;                                               \
    object->savedX = x;                                                  \
    object->slot3C.savedY = y;                                           \
    sub_815F97C(object, 0);                                              \
    return object;                                                       \
}

DEFINE_INITIALIZER(sub_815852C, 0x08CDC5F0)
DEFINE_INITIALIZER(sub_815ED84, 0x08CDCB10)
DEFINE_POSITION_SNAPSHOT_INITIALIZER(sub_81585EC, 0x08CDC630)
DEFINE_POSITION_SNAPSHOT_INITIALIZER(sub_815EE44, 0x08CDCB50)

#define DEFINE_OWNED_RESOURCE_DESTRUCTOR(name, descriptor_value, member) \
SEC(name) void name(struct BattleSpriteMotion* object, void* argument)   \
{                                                                        \
    object->descriptor = (void*)(descriptor_value);                      \
    if (object->member != 0) {                                          \
        sub_8021308(object->member);                                     \
        object->member = 0;                                              \
    }                                                                    \
    sub_815FB14(object, argument);                                       \
}

DEFINE_OWNED_RESOURCE_DESTRUCTOR(sub_8158C98, 0x08CDC8F0, ownedResource40)
DEFINE_OWNED_RESOURCE_DESTRUCTOR(sub_815EFAC, 0x08CDCC50, slot34.ownedResource)
DEFINE_OWNED_RESOURCE_DESTRUCTOR(sub_8158764, 0x08CDC730, slot34.ownedResource)
DEFINE_OWNED_RESOURCE_DESTRUCTOR(sub_8158BB4, 0x08CDC8B0, ownedResource40)

SEC(sub_815F3F0)
void sub_815F3F0(struct BattleSpriteMotion* object, void* argument)
{
    object->descriptor = (void*)0x08CDCDD0;
    if (object->ownedResource40 != 0) {
        sub_8021308(object->ownedResource40);
        object->ownedResource40 = 0;
    }
    if (object->slot3C.child != 0) {
        sub_8021308(object->slot3C.child);
        object->slot3C.child = 0;
    }
    sub_815FB14(object, argument);
}

#define DEFINE_LINKED_CHILD_DESTRUCTOR(name, descriptor_value)           \
SEC(name) void name(struct BattleSpriteMotion* object, void* argument)   \
{                                                                        \
    struct BattleSpriteMotion* child;                                    \
    u8* definition;                                                      \
    object->descriptor = (void*)(descriptor_value);                      \
    child = object->slot34.child;                                        \
    if (child != 0) {                                                    \
        definition = (u8*)child->descriptor;                             \
        (*(void (**)(void*, s32))(definition + 0x0C))(                   \
            (u8*)child + *(s16*)(definition + 8), 3);                    \
    }                                                                    \
    sub_815FB14(object, argument);                                       \
}

DEFINE_LINKED_CHILD_DESTRUCTOR(sub_8158954, 0x08CDC9B0)
DEFINE_LINKED_CHILD_DESTRUCTOR(sub_815F19C, 0x08CDCED0)

#define DEFINE_PREPARE_STATE(name, next_state)                           \
SEC(name) void name(struct BattleSpriteMotion* object)                   \
{                                                                        \
    struct BattleSprite* sprite = sub_815FA3C(object);                   \
    if (sprite != 0) {                                                   \
        sub_815FA70(object, 1);                                          \
        sub_815FA3C(object)->value0C = 0;                                \
    }                                                                    \
    object->slot34.values.auxiliary = 0x1E;                              \
    object->state = (next_state);                                        \
}

DEFINE_PREPARE_STATE(sub_8158A20, 4)
DEFINE_PREPARE_STATE(sub_8158ABC, 2)

#define DEFINE_ATTACHED_POSITION_SYNC(name)                              \
SEC(name) void name(struct BattleSpriteMotion* object, void* origin)     \
{                                                                        \
    sub_815FAA4(object, origin);                                         \
    if (object->ownedResource40 != 0) {                                  \
        ((struct BattleSpritePosition*)object->ownedResource40)->x =     \
            ((struct BattleSpritePosition*)sub_815FA3C(object))->x;      \
        ((struct BattleSpritePosition*)object->ownedResource40)->y =     \
            ((struct BattleSpritePosition*)sub_815FA3C(object))->y;      \
    }                                                                    \
}

DEFINE_ATTACHED_POSITION_SYNC(sub_8158B64)
DEFINE_ATTACHED_POSITION_SYNC(sub_8158C6C)

#define DEFINE_CHILD_WRAPPER_DESTRUCTOR(name, descriptor_value)          \
SEC(name) void name(struct BattleSpriteMotion* object, void* argument)   \
{                                                                        \
    struct BattleSpriteMotion* child;                                    \
    u8* definition;                                                      \
    object->descriptor = (void*)(descriptor_value);                      \
    if (object->slot3C.child != 0) {                                     \
        sub_815FAFC(object->slot3C.child);                               \
        child = object->slot3C.child;                                    \
        if (child != 0) {                                                \
            definition = (u8*)child->descriptor;                         \
            (*(void (**)(void*, s32))(definition + 0x0C))(               \
                (u8*)child + *(s16*)(definition + 8), 3);                \
        }                                                                \
    }                                                                    \
    sub_815FB14(object, argument);                                       \
}

DEFINE_CHILD_WRAPPER_DESTRUCTOR(sub_8158EEC, 0x08CDC9F0)
DEFINE_CHILD_WRAPPER_DESTRUCTOR(sub_815F58C, 0x08CDCF10)

void* battle_initialize_sprite_motion_variant_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16)
    __attribute__((alias("sub_815852C")));
void* battle_initialize_sprite_motion_variant_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16)
    __attribute__((alias("sub_815ED84")));
void* battle_initialize_sprite_motion_with_position_snapshot_variant_a(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16)
    __attribute__((alias("sub_81585EC")));
void* battle_initialize_sprite_motion_with_position_snapshot_variant_b(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*, u16)
    __attribute__((alias("sub_815EE44")));
void battle_prepare_sprite_motion_state_4(struct BattleSpriteMotion*)
    __attribute__((alias("sub_8158A20")));
void battle_prepare_sprite_motion_state_2(struct BattleSpriteMotion*)
    __attribute__((alias("sub_8158ABC")));
void battle_destroy_sprite_motion_resource_40(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158C98")));
void battle_destroy_sprite_motion_resource_34(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_815EFAC")));
void battle_destroy_sprite_motion_child_34_variant_a(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158954")));
void battle_destroy_sprite_motion_child_34_variant_b(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_815F19C")));
void battle_destroy_sprite_motion_child_3c_variant_a(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158EEC")));
void battle_destroy_sprite_motion_child_3c_variant_b(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_815F58C")));
void battle_destroy_sprite_motion_resource_34_variant_c(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158764")));
void battle_destroy_sprite_motion_resource_40_variant_c(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158BB4")));
void battle_destroy_sprite_motion_resources_3c_and_40(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_815F3F0")));
void battle_sync_attached_sprite_position_variant_a(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158B64")));
void battle_sync_attached_sprite_position_variant_b(
    struct BattleSpriteMotion*, void*)
    __attribute__((alias("sub_8158C6C")));
