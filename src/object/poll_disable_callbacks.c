#include "object/runtime_object.h"
#include "object/functions.h"

s32 sub_8087CE4(struct RuntimeObject* object);
void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);

/* The single-iteration block retains the original compiler's register allocation. */
#define DEFINE_POLL_DISABLE(name) \
    __attribute__((section(".text.object_poll_disable." #name))) \
    void name(struct RuntimeObject* object) { \
        u8 active = sub_8087CE4(object); \
        if (active == 0) { \
            do { sub_8082E1C(object, -1, -1, 0); } while (0); \
            object->update = (RuntimeObjectCallback)(u32)active; \
        } \
    } \
    __attribute__((section(".text.object_poll_disable." #name))) \
    const u16 name##_padding = 0;

DEFINE_POLL_DISABLE(sub_8110C88)
DEFINE_POLL_DISABLE(sub_8112870)
DEFINE_POLL_DISABLE(sub_8132650)
