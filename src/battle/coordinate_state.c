#include "battle/coordinate_state.h"
#include "common.h"
#include "graphics/functions.h"

#define SEC(symbol) __attribute__((section(".text.battle_coordinate_state." #symbol)))

s16 sub_8160854(void* heightContext, s32 x);
void graphics_release_owned_resource(void* owner);

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
    projector->output->xPosition = (projector->positionX - origin->x) >> 8;
    projector->output->yPosition = (projector->positionY - origin->y) >> 8;
}

SEC(sub_81612F8)
void battle_coordinate_projector_create_sprite(
    struct BattleCoordinateProjector* projector, s32 variant)
{
    struct Sprite* sprite = sub_8020DD0(
        0, projector->spriteResourceId, variant, -1, -1, -1, -1);
    projector->output = sprite;
    sprite->xPosition = projector->positionX >> 8;
    projector->output->yPosition = projector->positionY >> 8;
}

SEC(sub_8161330)
void battle_destroy_coordinate_projector(
    struct BattleCoordinateProjector* projector, u32 flags)
{
    projector->descriptor = (const void*)0x08CDD018;
    if (projector->output != 0)
        graphics_release_owned_resource(projector);
    if (flags & 1)
        free_heap_8018DA8(projector);
}
