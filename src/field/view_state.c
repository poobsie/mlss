#include "field/view_state.h"

#define SEC(name) __attribute__((section(".text.field_view_state." #name)))

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
