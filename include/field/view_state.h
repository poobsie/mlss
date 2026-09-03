#ifndef GUARD_FIELD_VIEW_STATE_H
#define GUARD_FIELD_VIEW_STATE_H

#include "global.h"

typedef struct FieldViewState {
    u8 unknown000[0x20];
    s16 panDeltaX;
    s16 panDeltaY;
    u8 unknown024[0x750];
    s16 originX;
    s16 originY;
    s16 panX;
    s16 panY;
} FieldViewState;

#define field_view_set_pan_delta sub_805A954
#define field_adjust_world_values_for_view sub_807FBD8
#define field_adjust_record_for_view sub_807FC54

void field_view_add_pan(FieldViewState *view, s32 x, s32 y);
void field_view_set_pan(FieldViewState *view, s16 x, s16 y);
s32 field_view_get_origin_y(FieldViewState *view);
s32 field_view_get_origin_x(FieldViewState *view);
void field_view_set_pan_delta(FieldViewState* view, s16 x, s16 y);
void field_adjust_world_values_for_view(
    s32* x, s32* y, s32* depth, s32 unused);
void field_adjust_record_for_view(
    s16* record, s32 x, s32 y, s32 z, s32 baseline);

/* Address-compatible entry points retained for assembly callers. */
void sub_8082D00(FieldViewState *view, s32 x, s32 y);
void sub_8082D24(FieldViewState *view, s16 x, s16 y);
s32 sub_8082D40(FieldViewState *view);
s32 sub_8082D50(FieldViewState *view);

#endif
