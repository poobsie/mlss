#include "global.h"
#include "mario_bros/functions.h"
#include "mario_bros/object.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_pool_" #name)))

struct MarioBrosPoolObject {
    u8 unknown00[2];
    u16 poolIndex;
    u8 unknown04[3];
    struct __attribute__((packed)) {
        u8 highFlag : 1;
        u8 unknown : 7;
    } flags07;
    u8 unknown08[0x30];
    void* allocation38;
};

struct MarioBrosLinkContext {
    u8 unknown00[0x4F];
    struct __attribute__((packed)) {
        u8 mode : 2;
        u8 unknown : 6;
    } linkFlags4F;
    u8 unknown50[8];
    struct MarioBrosPoolObject* linkedObject58;
};

struct MarioBrosPoolRuntime {
    u8 unknown0000[0x4494];
    struct MarioBrosPoolObject* objects4494[28];
    struct MarioBrosPoolObject* objects4504[16];
    u16 active4544[28];
};

extern struct MarioBrosPoolRuntime gMarioGlobal_03000F50;
extern struct MarioBrosPoolRuntime gMarioGlobal_03000F40;

extern void sub_8F51010(void* pool, void* allocation);
extern void sub_8F93C24(void* pool, void* allocation);
extern void sub_8F6F568(void* destination, const void* source, u32 size);
extern void sub_8F960C8(void* destination, const void* source, u32 size);
extern u16 sub_8F63968(struct MarioBrosLinkContext* context);
extern u16 sub_8F8A2BC(struct MarioBrosLinkContext* context);
extern u16 sub_8F5F148(u16 kind, u32 coordinate, u32 unknown);
extern u16 sub_8F85A9C(u16 kind, u32 coordinate, u32 unknown);
extern u16 sub_8F5EFD8(u16 kind, u32 coordinateA, u32 coordinateB);
extern u16 sub_8F8592C(u16 kind, u32 coordinateA, u32 coordinateB);
extern void sub_8F64AC0(struct MarioBrosPoolObject* object);
extern void sub_8F8B414(struct MarioBrosPoolObject* object);

struct MarioBrosSpawnSource {
    u8 unknown00[0xC];
    u32 coordinate0C;
    u32 coordinate10;
};

struct MarioBrosSpawnLink {
    u8 active;
    u8 unknown01[3];
    struct MarioBrosSpawnSource* owner;
};

#define DEFINE_RELEASE(name, runtime, pool, release, template, copy)              \
    MB_SECTION(name) void name(struct MarioBrosPoolObject* object) {              \
        u16 index = object->poolIndex;                                             \
        if (object->allocation38 != 0) {                                           \
            release((void*)(pool), object->allocation38);                          \
            object->allocation38 = 0;                                              \
        }                                                                          \
        (runtime).active4544[index] = 0;                                           \
        copy((runtime).objects4494[index], (const void*)(template), 0x3C);          \
    }

DEFINE_RELEASE(mario_bros_release_pool_object_a, gMarioGlobal_03000F50, 0x03001BC8,
               sub_8F51010, 0x08F9FA74, sub_8F6F568)
DEFINE_RELEASE(mario_bros_release_pool_object_b, gMarioGlobal_03000F40, 0x03001BB8,
               sub_8F93C24, 0x0201DDBC, sub_8F960C8)

#define DEFINE_ATTACH(name, find, runtime)                                         \
    MB_SECTION(name) void name(void* unused, struct MarioBrosLinkContext* context) {\
        u16 index = find(context);                                                 \
        if (index != 0xFFFF) {                                                     \
            struct MarioBrosPoolObject* object =                                   \
                (runtime).objects4494[index];                                       \
            context->linkFlags4F.mode = 2;                                         \
            context->linkedObject58 = object;                                      \
        }                                                                          \
    }

DEFINE_ATTACH(mario_bros_attach_pool_object_a, sub_8F63968, gMarioGlobal_03000F50)
DEFINE_ATTACH(mario_bros_attach_pool_object_b, sub_8F8A2BC, gMarioGlobal_03000F40)

#define DEFINE_PROPAGATE_HIGH_FLAG(name, find, runtime)                            \
    MB_SECTION(name) void name(struct MarioBrosObject* source) {                   \
        u16 index = find(2, source->positionX, 0);                                 \
        if (index != 0xFFFF) {                                                     \
            struct MarioBrosPoolObject* destination =                              \
                (runtime).objects4504[index];                                       \
            destination->flags07.highFlag = source->flags08 >> 7;                  \
        }                                                                          \
    }

DEFINE_PROPAGATE_HIGH_FLAG(mario_bros_propagate_high_flag_a, sub_8F5F148,
                           gMarioGlobal_03000F50)
DEFINE_PROPAGATE_HIGH_FLAG(mario_bros_propagate_high_flag_b, sub_8F85A9C,
                           gMarioGlobal_03000F40)

#define DEFINE_SPAWN_LINKED(name, find, initialize, runtime)                       \
    MB_SECTION(name) u16 name(struct MarioBrosSpawnSource* source) {               \
        u16 index = find(5, source->coordinate0C, source->coordinate10);            \
        struct MarioBrosPoolObject* object;                                        \
        struct MarioBrosSpawnLink* link;                                           \
        u16 result;                                                                \
        if (index == 0xFF)                                                         \
            goto unavailable;                                                      \
        object = (runtime).objects4494[index];                                     \
        initialize(object);                                                        \
        ((struct MarioBrosObject*)object)->state = 3;                              \
        link = (struct MarioBrosSpawnLink*)object->allocation38;                   \
        link->active = 1;                                                          \
        link->owner = source;                                                      \
        result = index;                                                            \
        goto done;                                                                 \
    unavailable:                                                                  \
        result = 0xFF;                                                             \
    done:                                                                         \
        return result;                                                             \
    }

DEFINE_SPAWN_LINKED(mario_bros_spawn_linked_object_a, sub_8F5EFD8, sub_8F64AC0,
                    gMarioGlobal_03000F50)
DEFINE_SPAWN_LINKED(mario_bros_spawn_linked_object_b, sub_8F8592C, sub_8F8B414,
                    gMarioGlobal_03000F40)
