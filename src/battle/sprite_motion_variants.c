#include "battle/sprite_motion.h"

#define SEC(name) __attribute__((section(".text.text_upper_structural." #name)))
#define CALLBACK_SEC_INNER(name) \
    __attribute__((section(".text.battle_sprite_callbacks." #name)))
#define CALLBACK_SEC(name) CALLBACK_SEC_INNER(name)

extern void* sub_815F8F4(
    struct BattleSpriteMotion*, const struct BattleSpriteMotionConfig*);
extern void sub_815F97C(struct BattleSpriteMotion*, s32);
extern struct BattleSprite* sub_815FA3C(struct BattleSpriteMotion*);
extern void sub_815FA70(struct BattleSpriteMotion*, s32);
extern void sub_815FAFC(struct BattleSpriteMotion*);
extern void sub_815FB14(struct BattleSpriteMotion*, void*);
extern void sub_815FAA4(struct BattleSpriteMotion*, void*);
extern void sub_8021308(void*);
extern s32 sub_8199F30(void);

struct BattleSpritePosition {
    u16 x;
    u16 y;
};

struct BattleFixedOrigin {
    s32 x;
    s32 y;
};

/*
 * These callbacks form two mirrored battle-effect families. Descriptor
 * identities and the gameplay meaning of state/variant values remain unknown;
 * the constructor, position, and sprite-size behavior is structurally proven.
 */

#define DEFINE_ZEROED_INITIALIZER(name, descriptor_value, next_state)    \
CALLBACK_SEC(name) void* name(                                          \
    struct BattleSpriteMotion* object,                                  \
    const struct BattleSpriteMotionConfig* config, u16 value)           \
{                                                                       \
    sub_815F8F4(object, config);                                        \
    object->descriptor = (void*)(descriptor_value);                     \
    object->slot34.values.value = value;                                \
    object->slot34.values.auxiliary = 0;                                \
    *(u16*)&object->savedX = 0;                                         \
    if ((next_state) >= 0)                                              \
        object->state = (next_state);                                   \
    sub_815F97C(object, 0);                                             \
    return object;                                                      \
}

DEFINE_ZEROED_INITIALIZER(battle_initialize_sprite_motion_zeroed_a, 0x08CDC5B0, -1)
DEFINE_ZEROED_INITIALIZER(battle_initialize_sprite_motion_state_2_a, 0x08CDC830, 2)
DEFINE_ZEROED_INITIALIZER(battle_initialize_sprite_motion_state_2_b, 0x08CDCD50, 2)
DEFINE_ZEROED_INITIALIZER(battle_initialize_sprite_motion_zeroed_b, 0x08CDCD90, -1)

#define DEFINE_SIMPLE_STATE_INITIALIZER(name, descriptor_value, initialize_sprite) \
CALLBACK_SEC(name) void* name(                                          \
    struct BattleSpriteMotion* object,                                  \
    const struct BattleSpriteMotionConfig* config, u16 value)           \
{                                                                       \
    sub_815F8F4(object, config);                                        \
    object->descriptor = (void*)(descriptor_value);                     \
    object->slot34.values.value = value;                                \
    object->state = 0;                                                  \
    if (initialize_sprite)                                              \
        sub_815F97C(object, 0);                                         \
    return object;                                                      \
}

DEFINE_SIMPLE_STATE_INITIALIZER(battle_initialize_sprite_motion_idle_a, 0x08CDC7B0, 0)
DEFINE_SIMPLE_STATE_INITIALIZER(battle_initialize_sprite_motion_idle_with_sprite, 0x08CDC7F0, 1)
DEFINE_SIMPLE_STATE_INITIALIZER(battle_initialize_sprite_motion_idle_b, 0x08CDCCD0, 0)

#define DEFINE_ORIGIN_SYNC(name)                                        \
CALLBACK_SEC(name) void name(                                           \
    struct BattleSpriteMotion* object, const struct BattleFixedOrigin* origin) \
{                                                                       \
    struct BattleSpritePosition* position;                              \
    s32 coordinate;                                                     \
    sub_815FAA4(object, (void*)origin);                                 \
    position = object->slot34.ownedResource;                            \
    if (position != 0) {                                                \
        coordinate = origin->x;                                        \
        position->x = (object->positionX - coordinate) >> 8;           \
        position = object->slot34.ownedResource;                        \
        coordinate = origin->y;                                        \
        position->y = (object->positionY - coordinate) >> 8;           \
    }                                                                   \
}

DEFINE_ORIGIN_SYNC(battle_sync_sprite_motion_to_origin_a)
DEFINE_ORIGIN_SYNC(battle_sync_sprite_motion_to_origin_b)

#define DEFINE_SPRITE_SIZE_SETUP(name)                                  \
CALLBACK_SEC(name) void name(struct BattleSpriteMotion* object)         \
{                                                                       \
    sub_815F97C(object, 0);                                             \
    sub_815FA3C(object)->size04 = 0xC0;                                \
    sub_815FA3C(object)->size06 = 0xC0;                                \
}

DEFINE_SPRITE_SIZE_SETUP(battle_setup_sprite_motion_size_a)
CALLBACK_SEC(sub_8158B90) const u16 sub_8158B90_padding = 0;
DEFINE_SPRITE_SIZE_SETUP(battle_setup_sprite_motion_size_b)
CALLBACK_SEC(sub_815F3CC) const u16 sub_815F3CC_padding = 0;

CALLBACK_SEC(sub_815F08C)
s32 battle_wrap_sprite_motion_x(
    struct BattleSpriteMotion* object, void* unused1, void* unused2,
    const s32* originX)
{
    object->positionX -= (s16)object->slot34.values.value;
    if (object->positionX - *originX < -0x2000)
        object->positionX += ((sub_8199F30() & 0x1FF) + 0x200) << 8;
    return 0;
}


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
