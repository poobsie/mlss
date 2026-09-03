#include "global.h"
#include "object/render_object.h"

#define SEC(name) __attribute__((section(".text.object_destructors." #name)))

extern void sub_8163B60(struct DescriptorObject*, s32);

#define DEFINE_OBJECT_DESTRUCTOR(name, descriptor_address)             \
    SEC(name) void name(struct DescriptorObject* object, s32 flags)     \
    {                                                                    \
        object->descriptor = (void *)(descriptor_address);              \
        sub_8163B60(object, flags);                                     \
    }

DEFINE_OBJECT_DESTRUCTOR(sub_8167EBC, 0x08CDD168)
DEFINE_OBJECT_DESTRUCTOR(sub_8167F40, 0x08CDD178)
DEFINE_OBJECT_DESTRUCTOR(sub_8167FF8, 0x08CDD188)
DEFINE_OBJECT_DESTRUCTOR(sub_816B0E0, 0x08CDD1C8)
DEFINE_OBJECT_DESTRUCTOR(sub_816B21C, 0x08CDD1D8)
DEFINE_OBJECT_DESTRUCTOR(sub_816B2E0, 0x08CDD1E8)
DEFINE_OBJECT_DESTRUCTOR(sub_816B338, 0x08CDD1F8)
DEFINE_OBJECT_DESTRUCTOR(sub_816D608, 0x08CDD238)
DEFINE_OBJECT_DESTRUCTOR(sub_816D6C0, 0x08CDD248)
DEFINE_OBJECT_DESTRUCTOR(sub_816D710, 0x08CDD258)
DEFINE_OBJECT_DESTRUCTOR(sub_816D7B8, 0x08CDD268)
DEFINE_OBJECT_DESTRUCTOR(sub_8171C20, 0x08CDD2A8)
DEFINE_OBJECT_DESTRUCTOR(sub_8171C88, 0x08CDD2B8)
DEFINE_OBJECT_DESTRUCTOR(sub_8171D58, 0x08CDD2C8)
DEFINE_OBJECT_DESTRUCTOR(sub_8171F84, 0x08CDD2D8)
