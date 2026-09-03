#ifndef GUARD_FIELD_OBJECT_SLIDE_SEQUENCE_H
#define GUARD_FIELD_OBJECT_SLIDE_SEQUENCE_H

#include "global.h"
#include "field/view_state.h"

struct FieldSlideObject {
    u8 unknown00[0x10];
    s32 positionX;
};

struct FieldSlideRuntime {
    u8 unknown000[0x24C];
    FieldViewState* view;
    u8 unknown250[0x28];
    struct FieldSlideObject* secondObject;
    u8 unknown27C[0xC6];
    s8 slideActive342;
    u8 unknown343[0x39];
    struct FieldSlideObject* firstObject;
};

struct FieldSlideProcess {
    u8 unknown00[4];
    void (*update)(struct FieldSlideProcess* process);
};

void field_slide_pair_to_screen_x_208(struct FieldSlideProcess* process);

#endif
