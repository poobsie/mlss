#include "audio/sound_effects.h"
#include "field/actor.h"
#include "object/field_actor_effect.h"

void sub_8082E1C(struct RuntimeObject* object, s32 animation, s32 command, s32 argument);
void sub_80880C4(struct RuntimeObject* object, s32 value);
void sub_808843C(struct RuntimeObject* object, s32 x, s32 y, s32 z, s32 scale);
void sub_809D91C(struct RuntimeObject* object);

#define SEC(symbol) __attribute__((section(".text.small_functions_12." #symbol)))

SEC(sub_809D4E4)
void object_begin_effect_centered_between_field_actors(struct RuntimeObject* object)
{
    s32 combinedY;
    s32 ownerX;
    s32 actorY;
    s32 screenY;
    struct RuntimeObject* actorAAction;
    struct RuntimeObject* actorBAction;
    struct FieldActor* actorA;
    struct FieldActor* actorB;
    struct RuntimeObject* positionOwner;

    actorA = gFieldRuntime->actorA;
    actorAAction = (struct RuntimeObject*)((u8*)actorA + 8);
    actorB = gFieldRuntime->actorB;
    actorBAction = (struct RuntimeObject*)((u8*)actorB + 8);
    sub_8082E1C(object, 8, 0, 0);
    if ((actorA->stateFlags & 6) != 2) {
        actorY = actorBAction->positionY;
        goto convert_actor_y;
    }
    if ((actorB->stateFlags & 6) != 2) {
        actorY = actorAAction->positionY;
convert_actor_y:
        if (actorY < 0)
            actorY += 0xFF;
        screenY = actorY >> 8;
    } else {
        combinedY = actorAAction->positionY + actorBAction->positionY;
        if (combinedY < 0)
            combinedY += 0x1FF;
        screenY = combinedY >> 9;
    }
    positionOwner = object->positionOwner;
    ownerX = positionOwner->positionX;
    if (ownerX < 0)
        ownerX += 0xFF;
    sub_808843C(object, (ownerX >> 8) + 0x38, screenY, 0, 0x100);
    sub_80880C4(object, 0x180);
    sound_effect_play(0x99, SOUND_VOLUME_UNCHANGED);
    object->update = sub_809D91C;
}
