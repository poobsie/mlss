#ifndef GUARD_GRAPHICS_POSITION_BINDING_H
#define GUARD_GRAPHICS_POSITION_BINDING_H

#include "global.h"

struct ScreenPosition {
    s16 x;
    s16 y;
};

struct FixedPosition {
    s32 x;
    s32 y;
};

struct PositionBinding {
    struct ScreenPosition* output;
    s32 worldX;
    s32 worldY;
};

#define position_binding_update_relative sub_815FAA4
#define position_binding_update_callback_a sub_8158988
#define position_binding_update_callback_b sub_81589D0
#define position_binding_update_callback_c sub_815F1D0
#define position_binding_update_callback_d sub_815F218

void position_binding_update_relative(struct PositionBinding* binding,
                                      const struct FixedPosition* origin);
void position_binding_update_callback_a(struct PositionBinding* binding,
                                        const struct FixedPosition* origin);
void position_binding_update_callback_b(struct PositionBinding* binding,
                                        const struct FixedPosition* origin);
void position_binding_update_callback_c(struct PositionBinding* binding,
                                        const struct FixedPosition* origin);
void position_binding_update_callback_d(struct PositionBinding* binding,
                                        const struct FixedPosition* origin);

#endif
