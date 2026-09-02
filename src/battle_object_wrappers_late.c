#include "global.h"

void sub_815FB14(void* object, void* argument, void* definition);
void free_heap_8018DA8(void* pointer);
void sprite_hide_8021F20(void* sprite);
void sprite_show_8020CBC(void* sprite);
void sub_8021308(void* sprite);
void sub_815FAE4(void* object, int y);

#define DEFINE_OBJECT_WRAPPER(name, address)                                   \
    void name(void* object, void* argument)                                    \
        __attribute__((section(".text." #name)));                             \
    void name(void* object, void* argument) {                                  \
        void* definition = (void*)(address);                                   \
        *(void**)((u8*)object + 0x30) = definition;                            \
        sub_815FB14(object, argument, definition);                             \
    }

void sub_815EC3C(u8* object) __attribute__((section(".text.sub_815EC3C")));
void sub_815EC3C(u8* object) {
    u8* sprite = *(u8**)(object + 0xC);
    sprite[0x12] |= 0x20;
    object[0x1A] = 0;
}

DEFINE_OBJECT_WRAPPER(sub_815ED70, 0x08CDCB10)
DEFINE_OBJECT_WRAPPER(sub_815EDF4, 0x08CDCB90)
DEFINE_OBJECT_WRAPPER(sub_815EE30, 0x08CDCB50)
DEFINE_OBJECT_WRAPPER(sub_815EE74, 0x08CDCBD0)
DEFINE_OBJECT_WRAPPER(sub_815EF44, 0x08CDCC10)
DEFINE_OBJECT_WRAPPER(sub_815F050, 0x08CDCC90)
DEFINE_OBJECT_WRAPPER(sub_815F110, 0x08CDCE50)
DEFINE_OBJECT_WRAPPER(sub_815F168, 0x08CDCE90)
DEFINE_OBJECT_WRAPPER(sub_815F1DC, 0x08CDCCD0)
DEFINE_OBJECT_WRAPPER(sub_815F224, 0x08CDCD10)
DEFINE_OBJECT_WRAPPER(sub_815F27C, 0x08CDCD50)
DEFINE_OBJECT_WRAPPER(sub_815F340, 0x08CDCD90)

void sub_8159904(u8* object, u32 value)
    __attribute__((section(".text.sub_8159904")));
void sub_8159904(u8* object, u32 value) {
    *(u32*)(object + 0x52C) = value;
}

void sub_8159984(u8* object, u16 value)
    __attribute__((section(".text.sub_8159984")));
void sub_8159984(u8* object, u16 value) {
    *(u16*)(object + 0x518) = 1;
    *(u16*)(object + 0x514) = value;
}

#define DEFINE_DESTRUCTOR(name)                                                \
    void name(u8* object, int flags)                                           \
        __attribute__((section(".text." #name)));                             \
    void name(u8* object, int flags) {                                         \
        u8* current = object;                                                  \
        *(void**)(current + 4) = (void*)0x08CDCF50;                            \
        if (flags & 1) {                                                       \
            free_heap_8018DA8(current);                                        \
        }                                                                      \
    }

DEFINE_DESTRUCTOR(sub_815F7FC)
DEFINE_DESTRUCTOR(sub_815F838)
DEFINE_DESTRUCTOR(sub_815F85C)
DEFINE_DESTRUCTOR(sub_815F898)
DEFINE_DESTRUCTOR(sub_815F8BC)

void* sub_815FA3C(void* object) __attribute__((section(".text.sub_815FA3C")));
void* sub_815FA3C(void* object) {
    return *(void**)object;
}

void sub_815FA40(void* object) __attribute__((section(".text.sub_815FA40")));
void sub_815FA40(void* object) {
    void* sprite = *(void**)object;
    if (sprite != 0) {
        sprite_hide_8021F20(sprite);
    }
}

void sub_815FA50(void* object) __attribute__((section(".text.sub_815FA50")));
void sub_815FA50(void* object) {
    void* sprite = *(void**)object;
    if (sprite != 0) {
        sprite_show_8020CBC(sprite);
    }
}

void sub_815F56C(void* object, int unused, int y)
    __attribute__((section(".text.sub_815F56C")));
void sub_815F56C(void* object, int unused, int y) {
    sub_815FAE4(object, y);
}

void sub_815FAFC(u8* object) __attribute__((section(".text.sub_815FAFC")));
void sub_815FAFC(u8* object) {
    void* sprite = *(void**)object;
    if (sprite != 0) {
        sub_8021308(sprite);
        *(void**)object = 0;
    }
}
