#ifndef GUARD_FIELD_VIEW_STATE_H
#define GUARD_FIELD_VIEW_STATE_H

#include "global.h"

typedef struct FieldViewState {
    u8 unknown000[0x774];
    s16 originX;
    s16 originY;
    s16 panX;
    s16 panY;
} FieldViewState;

void field_view_add_pan(FieldViewState *view, s32 x, s32 y);
void field_view_set_pan(FieldViewState *view, s16 x, s16 y);
s32 field_view_get_origin_y(FieldViewState *view);
s32 field_view_get_origin_x(FieldViewState *view);

/* Address-compatible entry points retained for assembly callers. */
void sub_8082D00(FieldViewState *view, s32 x, s32 y);
void sub_8082D24(FieldViewState *view, s16 x, s16 y);
s32 sub_8082D40(FieldViewState *view);
s32 sub_8082D50(FieldViewState *view);

#endif
