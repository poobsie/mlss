#include "field/object_slide_sequence.h"

#define SEC(name) __attribute__((section(".text.field_object_slide_sequence." #name)))
#define FIELD_RUNTIME (*(struct FieldSlideRuntime**)0x03000FD8)

void sub_8106AC8(struct FieldSlideProcess* process);
void sub_8082C58(FieldViewState* view, s32* x, s32* y, s32* depth, s32 unused);
void sub_8082E1C(void* object, s32 animation, s32 value, s32 flags);

SEC(sub_81040DC) void sub_81040DC(struct FieldSlideProcess* process)
{
    s32 screenX;
    s32 screenY;
    s32 depth;
    s32 position;
    s32 snappedPosition;
    s32 roundedPosition;
    struct FieldSlideRuntime* runtime;
    struct FieldSlideObject* first;
    struct FieldSlideObject* second;

    runtime = FIELD_RUNTIME;
    first = runtime->firstObject;
    second = runtime->secondObject;
    position = first->positionX - 0x100;
    first->positionX = position;
    second->positionX = position;
    roundedPosition = first->positionX;
    if (roundedPosition < 0)
        roundedPosition += 0xFF;
    screenX = roundedPosition >> 8;
    screenY = 0;
    depth = 0;
    sub_8082C58(runtime->view, &screenX, &screenY, &depth, 0);
    if (screenX <= 0xD0) {
        snappedPosition =
            ((s32)(sub_8082D50(FIELD_RUNTIME->view) << 0x10) >> 8) + 0xD000;
        first->positionX = snappedPosition;
        second->positionX = snappedPosition;
        sub_8082E1C(second, 4, 0, 0);
        FIELD_RUNTIME->slideActive342 = 0;
        process->update = sub_8106AC8;
    }
}

void field_slide_pair_to_screen_x_208(struct FieldSlideProcess* process)
    __attribute__((alias("sub_81040DC")));
