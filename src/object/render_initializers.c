#include "global.h"
#include "object/render_object.h"

#define SEC(name) __attribute__((section(".text.render_object_initializers." #name)))

extern void sub_815F8F4();
extern void sub_815F97C(struct RenderObject*, s32);

#define DEFINE_RENDER_OBJECT_INITIALIZER(name, descriptor_address)      \
    SEC(name) struct RenderObject* name(struct RenderObject* object, s32 unusedMode, u16 value) \
    {                                                                    \
        sub_815F8F4();                                                   \
        object->descriptor = (void *)(descriptor_address);              \
        object->value = value;                                          \
        sub_815F97C(object, 0);                                         \
        return object;                                                   \
    }

#define DEFINE_ACTIVE_RENDER_OBJECT_INITIALIZER(name, descriptor_address) \
    SEC(name) struct RenderObject* name(struct RenderObject* object, s32 unusedMode, u16 value) \
    {                                                                    \
        sub_815F8F4();                                                   \
        object->descriptor = (void *)(descriptor_address);              \
        object->value = value;                                          \
        object->active = 1;                                             \
        return object;                                                   \
    }

DEFINE_RENDER_OBJECT_INITIALIZER(sub_81585B0, 0x08CDC670)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_8158710, 0x08CDC6F0)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_815EE08, 0x08CDCB90)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_815EE88, 0x08CDCBD0)
DEFINE_RENDER_OBJECT_INITIALIZER(sub_815EF58, 0x08CDCC10)
DEFINE_ACTIVE_RENDER_OBJECT_INITIALIZER(sub_815881C, 0x08CDC770)
DEFINE_ACTIVE_RENDER_OBJECT_INITIALIZER(sub_815F064, 0x08CDCC90)
