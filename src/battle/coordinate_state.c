#include "battle/coordinate_state.h"

#define SEC(symbol) __attribute__((section(".text.battle_coordinate_state." #symbol)))

s16 sub_8160854(void* heightContext, s32 x);

SEC(sub_8161180)
void battle_update_coordinate_projector_motion(
    struct BattleCoordinateProjector* projector)
{
    s32 x = projector->positionX + projector->velocityX;
    s32 ground;
    projector->positionX = x;
    projector->positionY += projector->velocityY
                          + projector->verticalAcceleration;
    ground = sub_8160854(projector->heightContext, x) << 8;
    if (projector->positionY > ground)
        projector->positionY = ground;
}

SEC(sub_816127C)
void battle_write_relative_coordinates(
    struct BattleCoordinateProjector* projector,
    const struct BattleCoordinateOrigin* origin)
{
    projector->output->x = (projector->positionX - origin->x) >> 8;
    projector->output->y = (projector->positionY - origin->y) >> 8;
}
