#include "battle/coordinate_state.h"

#define SEC(symbol) __attribute__((section(".text.battle_coordinate_state." #symbol)))

SEC(sub_816127C)
void battle_write_relative_coordinates(
    struct BattleCoordinateProjector* projector,
    const struct BattleCoordinateOrigin* origin)
{
    projector->output->x = (projector->positionX - origin->x) >> 8;
    projector->output->y = (projector->positionY - origin->y) >> 8;
}
