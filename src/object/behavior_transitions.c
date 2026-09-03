#include "global.h"
#include "object/behavior_object.h"

#define FUNCTION_SECTION(name) __attribute__((section(".text." #name)))

extern void sub_8082E1C(void*, u32, u32, u32);

#define DEFINE_SETUP(name, kind, next)                                                                 \
    extern void next(struct BehaviorObject*);                                                          \
    void name(struct BehaviorObject*) FUNCTION_SECTION(name);                                          \
    void name(struct BehaviorObject* object) {                                                         \
        sub_8082E1C(object, kind, 0, 0);                                                               \
        object->update = next;                                                                         \
    }

DEFINE_SETUP(sub_8062D68, 0xE, sub_808750C)
DEFINE_SETUP(sub_8064354, 6, sub_8063FC0)
DEFINE_SETUP(sub_806446C, 3, sub_8063CC8)
DEFINE_SETUP(sub_806A894, 2, sub_806A908)
DEFINE_SETUP(sub_806B50C, 2, sub_806AEFC)
DEFINE_SETUP(sub_806C294, 2, sub_806C2B0)
DEFINE_SETUP(sub_8070EC0, 5, sub_806EB18)
DEFINE_SETUP(sub_80746A8, 2, sub_8072764)
DEFINE_SETUP(sub_807608C, 0xE, sub_80760F4)
DEFINE_SETUP(sub_8077538, 0xA, sub_8076574)
DEFINE_SETUP(sub_8098CA0, 0x12, sub_8098CBC)
DEFINE_SETUP(sub_8099034, 0xF, sub_8099050)
DEFINE_SETUP(sub_80993C8, 0xC, sub_80993E4)
DEFINE_SETUP(sub_8099FE0, 6, sub_809A09C)
DEFINE_SETUP(sub_809A7EC, 2, sub_809A808)

#define DEFINE_FLAG_CALL(name, target)                                                                 \
    extern void target(struct BehaviorObject*);                                                        \
    void name(struct BehaviorObject*) FUNCTION_SECTION(name);                                          \
    void name(struct BehaviorObject* object) {                                                         \
        if (object->visual->flags & 8)                                                                 \
            target(object);                                                                            \
    }                                                                                                  \
    const u16 name##_padding FUNCTION_SECTION(name) = 0;

DEFINE_FLAG_CALL(sub_80651B0, sub_807C298)
DEFINE_FLAG_CALL(sub_806E5D8, sub_807C298)
DEFINE_FLAG_CALL(sub_80798A8, sub_807C298)
DEFINE_FLAG_CALL(sub_808BEB4, sub_8087540)
DEFINE_FLAG_CALL(sub_808C174, sub_8087540)
DEFINE_FLAG_CALL(sub_808C308, sub_8087540)
DEFINE_FLAG_CALL(sub_808C510, sub_807C298)
DEFINE_FLAG_CALL(sub_809900C, sub_8087540)
DEFINE_FLAG_CALL(sub_80993A0, sub_8087540)
DEFINE_FLAG_CALL(sub_8099FC4, sub_8087540)
DEFINE_FLAG_CALL(sub_809AEB0, sub_807C298)
DEFINE_FLAG_CALL(sub_809B738, sub_807C298)
DEFINE_FLAG_CALL(sub_809B754, sub_807C298)
DEFINE_FLAG_CALL(sub_809BA28, sub_807C298)
DEFINE_FLAG_CALL(sub_809D24C, sub_8087540)

#define DEFINE_COUNTDOWN(name, target)                                                                 \
    extern void target(struct BehaviorObject*);                                                        \
    void name(struct BehaviorObject*) FUNCTION_SECTION(name);                                          \
    void name(struct BehaviorObject* object) {                                                         \
        object->countdown--;                                                                           \
        if (object->countdown <= 0) {                                                                  \
            object->visual->state = 0x10;                                                              \
            target(object);                                                                            \
        }                                                                                              \
    }

DEFINE_COUNTDOWN(sub_808EE0C, sub_808EE54)
DEFINE_COUNTDOWN(sub_808EE30, sub_808EEB8)
DEFINE_COUNTDOWN(sub_808FE08, sub_808FE50)
DEFINE_COUNTDOWN(sub_808FE2C, sub_808FEB4)
DEFINE_COUNTDOWN(sub_8090B80, sub_8090BC8)
DEFINE_COUNTDOWN(sub_8090BA4, sub_8090C2C)
DEFINE_COUNTDOWN(sub_8091D10, sub_8091CC8)
DEFINE_COUNTDOWN(sub_8091D78, sub_8091D34)
DEFINE_COUNTDOWN(sub_8092EA0, sub_8092E58)
DEFINE_COUNTDOWN(sub_8092F08, sub_8092EC4)
DEFINE_COUNTDOWN(sub_8094070, sub_809400C)
DEFINE_COUNTDOWN(sub_80940F8, sub_8094094)
DEFINE_COUNTDOWN(sub_80944AC, sub_8094464)
DEFINE_COUNTDOWN(sub_8094514, sub_80944D0)
DEFINE_COUNTDOWN(sub_8094904, sub_80948BC)
DEFINE_COUNTDOWN(sub_809496C, sub_8094928)
DEFINE_COUNTDOWN(sub_8094D5C, sub_8094D14)
DEFINE_COUNTDOWN(sub_8094DC4, sub_8094D80)

#define DEFINE_FORWARD(name, target)                                                                   \
    extern void target(struct BehaviorObject*);                                                        \
    void name(void*) FUNCTION_SECTION(name);                                                           \
    void name(void* object) {                                                                          \
        target(object);                                                                                \
    }                                                                                                  \
    const u16 name##_padding FUNCTION_SECTION(name) = 0;

extern u32 sub_80871A8(void*);
u32 sub_806541C(void*) FUNCTION_SECTION(sub_806541C);
u32 sub_806541C(void* object) {
    return sub_80871A8(object);
}
const u16 sub_806541C_padding FUNCTION_SECTION(sub_806541C) = 0;

DEFINE_FORWARD(sub_8068268, sub_807C298)
DEFINE_FORWARD(sub_8079478, sub_807C298)
DEFINE_FORWARD(sub_80796B8, sub_807C298)
