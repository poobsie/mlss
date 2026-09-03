#include "field/view_state.h"
#include "field/object_slide_sequence.h"

#define SEC(name) __attribute__((section(".text.field_view_state." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))
#define FIELD_VIEW_RUNTIME (*(struct FieldSlideRuntime**)0x03000FD8)

void sub_8082C20(FieldViewState* view, s32* x, s32* y, s32* depth,
                 s32 unused);
void sub_8082CCC(FieldViewState* view, s16* record, s32 x, s32 y, s32 z,
                 s32 baseline);

MISC3_SEC(field_adjust_world_values_for_view)
void field_adjust_world_values_for_view(
    s32* x, s32* y, s32* depth, s32 unused)
{
    sub_8082C20(FIELD_VIEW_RUNTIME->view, x, y, depth, unused);
}

MISC3_SEC(field_adjust_record_for_view)
void field_adjust_record_for_view(
    s16* record, s32 x, s32 y, s32 z, s32 baseline)
{
    sub_8082CCC(FIELD_VIEW_RUNTIME->view, record, x, y, z, baseline);
}

MISC_SEC(field_view_set_pan_delta)
void field_view_set_pan_delta(FieldViewState* view, s16 x, s16 y)
{
    view->panDeltaX = x;
    view->panDeltaY = y;
}
MISC_SEC(field_view_set_pan_delta)
const u16 field_view_set_pan_delta_padding = 0;

SEC(sub_8082D00) void sub_8082D00(FieldViewState *view, s32 x, s32 y)
{
    view->panX = (u16)(view->panX + x);
    view->panY = (u16)(view->panY + y);
}

SEC(sub_8082D24) void sub_8082D24(FieldViewState *view, s16 x, s16 y)
{
    view->panX = x;
    view->panY = y;
}

SEC(sub_8082D40) s32 sub_8082D40(FieldViewState *view)
{
    return view->originY;
}

SEC(sub_8082D50) s32 sub_8082D50(FieldViewState *view)
{
    return view->originX;
}

void field_view_add_pan(FieldViewState *view, s32 x, s32 y)
    __attribute__((alias("sub_8082D00")));
void field_view_set_pan(FieldViewState *view, s16 x, s16 y)
    __attribute__((alias("sub_8082D24")));
s32 field_view_get_origin_y(FieldViewState *view)
    __attribute__((alias("sub_8082D40")));
s32 field_view_get_origin_x(FieldViewState *view)
    __attribute__((alias("sub_8082D50")));
