#include "global.h"
#include "object/runtime_object.h"

#define SECTION(name) __attribute__((section(".text.object_child_mode_transitions." #name)))

extern u32 sub_8087CE4(void);
extern u32 sub_80883F0(void);
extern void sub_8082E1C(struct RuntimeObject*, u32, u32, u32);
extern void sub_810FE1C(struct RuntimeObject*);
extern void sub_810F9FC(struct RuntimeObject*);
extern void sub_810F6D4(struct RuntimeObject*);

#define DEFINE_TRANSITION(name, gate, kind, callback) \
SECTION(name) void name(struct RuntimeObject* object) \
{ \
    if ((u8)gate() == 0) { \
        sub_8082E1C(object, kind, 0, 0); \
        { \
            s32 value = object->visual->flags; \
            s32 mask = 7; \
            mask = -mask; \
            mask &= value; \
            mask |= 2; \
            object->visual->flags = mask; \
        } \
        object->update = callback; \
    } \
}

DEFINE_TRANSITION(sub_810FBFC, sub_8087CE4, 8, sub_810FE1C)
DEFINE_TRANSITION(sub_810FF78, sub_80883F0, 7, sub_810F9FC)
DEFINE_TRANSITION(sub_8110078, sub_80883F0, 7, sub_810F6D4)
