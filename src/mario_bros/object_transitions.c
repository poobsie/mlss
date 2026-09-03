#include "global.h"
#include "mario_bros/object.h"

#define SECTION(name) __attribute__((section(".text.mariobros_transitions." #name)))

extern u8 sub_8F611F8(void *);
extern void sub_8F6DEA4(u32);

#define DEFINE_TRANSITION(name, code) \
    SECTION(name) void name(struct MarioBrosObject *object) \
    { \
        if (sub_8F611F8(object)) { \
            ((struct MarioBrosFlags08 *)&object->flags08)->mode = 2; \
            ((struct MarioBrosFlags0A *)&object->flags0A)->high = 0; \
            ((struct MarioBrosFlags0A *)&object->flags0A)->enabled = 1; \
            object->state = 3; \
            sub_8F6DEA4(code); \
        } \
    }

DEFINE_TRANSITION(sub_8F6009C, 0x17)
DEFINE_TRANSITION(sub_8F60BA0, 0x16)
DEFINE_TRANSITION(sub_8F629AC, 0x15)
