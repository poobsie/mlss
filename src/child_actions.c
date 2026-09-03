#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.child_actions." #name)))

extern void sprite_hide_8021F20(void *);
extern void sprite_show_8020CBC(void *);

SEC(sub_8135F20) void sub_8135F20(void *object)
{
    void *child = FIELD(object, void *, 4);
    if (child != 0)
        sub_8135F20(child);
    child = FIELD(object, void *, 8);
    if (child != 0)
        sub_8135F20(child);
}
SEC(sub_8135F20) const u16 sub_8135F20_padding = 0;

#define DEFINE_CHILD_ACTION(name, action)                               \
    SEC(name) void name(void *object)                                   \
    {                                                                    \
        void *child = FIELD(object, void *, 0x10);                      \
        if (child != 0)                                                  \
            action(child);                                               \
        child = FIELD(object, void *, 0x14);                            \
        if (child != 0)                                                  \
            action(child);                                               \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_CHILD_ACTION(sub_8163A24, sprite_hide_8021F20)
DEFINE_CHILD_ACTION(sub_8163A44, sprite_show_8020CBC)
