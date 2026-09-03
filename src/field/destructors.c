#include "global.h"
#include "field/scene_object.h"

#define SEC(name) __attribute__((section(".text.field_destructors." #name)))

void free_heap_8018DA8(void* object);

#define DEFINE_FIELD_DESTRUCTOR(name)                                   \
    SEC(name) void name(struct FieldSceneObject* object, s32 flags)      \
    {                                                                   \
        object->descriptor = (void*)0x08CDBDE8;                         \
        if (flags & 1)                                                  \
            free_heap_8018DA8(object);                                  \
    }

DEFINE_FIELD_DESTRUCTOR(sub_8048040)
DEFINE_FIELD_DESTRUCTOR(sub_81DD5B0)
DEFINE_FIELD_DESTRUCTOR(sub_81DD5D4)
DEFINE_FIELD_DESTRUCTOR(sub_81DD5F8)
