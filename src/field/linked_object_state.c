#include "global.h"
#include "field/linked_object.h"

#define SEC(name) __attribute__((section(".text.field_linked_object_state." #name)))

void sub_80494D4(struct FieldLinkedObject* object);
void sub_804FCD4(struct FieldLinkedObject* object);

SEC(sub_803C424) void sub_803C424(struct FieldLinkedObjectOwner* owner)
{
    struct FieldLinkedObject* second = owner->secondary;
    struct FieldLinkedObject* first = owner->primary;

    first->state = 0xB2;
    second->state = 0xB2;
}
SEC(sub_803C424) const u16 sub_803C424_padding = 0;

SEC(sub_803C440) s32 sub_803C440(struct FieldLinkedObjectOwner* owner)
{
    s32 result = 0;
    s8 marker = owner->primary->marker344;

    if (marker == 0x1C || marker == 0x15)
        result = 1;
    return result;
}

SEC(sub_803C4D8) s32 sub_803C4D8(struct FieldLinkedObjectOwner* owner)
{
    u16 state = owner->primary->state;

    if ((u32)(u16)(state - 0x10) <= 8U || (u32)(u16)(state - 0x1D) <= 4U)
        return 1;
    return 0;
}
SEC(sub_803C4D8) const u16 sub_803C4D8_padding = 0;

SEC(sub_803C638) void sub_803C638(struct FieldLinkedObjectOwner* owner)
{
    u16 state;
    struct FieldLinkedObject* object = owner->primary;

    state = object->state;
    if ((u32)(u16)(state - 5) <= 4U) {
        sub_804FCD4(object);
        return;
    }
    if ((u32)(u16)(state - 0xA) <= 2U)
        sub_80494D4(object);
}
