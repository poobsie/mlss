#include "global.h"
#include "audio/sound_effects.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.object_visual_completion_variants." #name)))

extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
extern s32 sub_8086858(struct RuntimeObject*, s32);
extern void sub_8062F8C(struct RuntimeObject*);
extern void sub_80651B0(struct RuntimeObject*);
extern void sub_806541C(struct RuntimeObject*);
extern void sub_809A178(struct RuntimeObject*);
extern void sub_80D9E34(struct RuntimeObject*);
extern void sub_80DA098(struct RuntimeObject*);
extern void sub_809A858(struct RuntimeObject*);

SEC(sub_8062F40) void sub_8062F40(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (object->behaviorState == 0)
            sub_8082E1C(object, 5, 0, 0);
        else
            sub_8082E1C(object, 8, 0, 0);
        object->timer = 0x1E;
        object->update = sub_8062F8C;
    }
}

SEC(sub_806533C) void sub_806533C(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 3, 0, 0);
        *(s32*)0x03000E3C = sub_8086858(object, 0x151D);
        object->secondaryUpdate = sub_806541C;
        object->update = sub_80651B0;
    }
}

SEC(sub_809A858) void sub_809A858(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (!(object->flags98 & 2))
            sub_8082E1C(object, 5, 0, 0);
        else
            sub_8082E1C(object, 7, 0, 0);
        object->update = sub_809A178;
    }
}

SEC(sub_80D9F50) void sub_80D9F50(struct RuntimeObject* object)
{
    s32 value;

    if (object->visual->flags & 8) {
        value = object->valueA8;
        if (value != 0) {
            sub_8082E1C(object, 0xA, 0, 0);
        } else {
            sub_8082E1C(object, 0xB, 0, 0);
            sub_8086858(object, 0x13CA);
            object->secondaryUpdate = sub_80D9E34;
            object->auxiliaryState = value;
        }
        object->timer = 0x18;
        object->update = sub_80DA098;
    }
}

SEC(sub_809A808) void sub_809A808(struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        if (!(object->flags98 & 1))
            sub_8082E1C(object, 3, 0, 0);
        else
            sub_8082E1C(object, 4, 0, 0);
        sound_effect_play(0x88, SOUND_VOLUME_UNCHANGED);
        object->update = sub_809A858;
    }
}
