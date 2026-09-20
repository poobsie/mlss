#ifndef GUARD_FIELD_DISPLAY_SCALE_TRANSITION_H
#define GUARD_FIELD_DISPLAY_SCALE_TRANSITION_H

#include "global.h"

struct FieldDisplayScale;

struct FieldDisplayScale* sub_8084338(
    s32 id, s32 value, s32 mode, s32 slot);
void sub_807BC90(struct FieldDisplayScale* resource);

struct FieldDisplayScaleProcess {
    u8 unknown00[4];
    void (*update)(struct FieldDisplayScaleProcess* process);
    struct FieldDisplayScale* resource;
    u8 unknown0C[0xA];
    u16 slotAndState16;
};

#define field_update_or_release_display_scale sub_810C398
void field_update_or_release_display_scale(
    struct FieldDisplayScaleProcess* process);

#endif
