#include "object/shared_motion.h"

u8 sub_801B1C8(void* handle, s32* positionA, s32* positionB);
void free_heap_8018DA8(void* allocation);
void sub_806499C(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);
void sub_807FC08(s32* x, s32* y, s32* z, s32 argument);

#define SEC(symbol) __attribute__((section(".text.small_functions_12." #symbol)))

#define SHARED_MOTION_HANDLE (*(void**)0x03000E18)
#define SHARED_MOTION_XY_X (*(s32*)0x03000E40)
#define SHARED_MOTION_XY_Y (*(s32*)0x03000E44)
#define SHARED_MOTION_XZ_X (*(s32*)0x03000E60)
#define SHARED_MOTION_XZ_Z (*(s32*)0x03000E64)

SEC(sub_8063248) void object_update_shared_motion_xy(struct RuntimeObject* object)
{
    s32 screenX;
    s32 screenY;
    s32 screenZ;
    s32 positionY;
    s32 positionX;
    s32 roundedY;
    s32 positionZ;

    if (sub_801B1C8(SHARED_MOTION_HANDLE,
                     (s32*)0x03000E40,
                     (s32*)0x03000E44) == 1) {
        positionX = SHARED_MOTION_XY_X;
        object->currentPositionX = positionX;
        positionY = SHARED_MOTION_XY_Y;
        object->currentPositionY = positionY;
        if (positionX < 0)
            positionX += 0xFF;
        screenX = positionX >> 8;
        roundedY = positionY;
        if (roundedY < 0)
            roundedY += 0xFF;
        screenY = roundedY >> 8;
        positionZ = object->verticalPosition;
        if (positionZ < 0)
            positionZ += 0xFF;
        screenZ = positionZ >> 8;
        sub_807FC08(&screenX, &screenY, &screenZ, 0);
        return;
    }
    free_heap_8018DA8(SHARED_MOTION_HANDLE);
    sub_807C298(object);
}

SEC(sub_8064908) void object_update_shared_motion_xz(struct RuntimeObject* object)
{
    s32 screenX;
    s32 screenY;
    s32 screenZ;
    s32 positionZ;
    s32 positionX;
    s32 positionY;
    s32 roundedZ;

    object->visual->value0C += 0x1000;
    if (sub_801B1C8(SHARED_MOTION_HANDLE,
                     (s32*)0x03000E60,
                     (s32*)0x03000E64) == 1) {
        positionX = SHARED_MOTION_XZ_X;
        object->currentPositionX = positionX;
        positionZ = SHARED_MOTION_XZ_Z;
        object->verticalPosition = positionZ;
        if (positionX < 0)
            positionX += 0xFF;
        screenX = positionX >> 8;
        positionY = object->currentPositionY;
        if (positionY < 0)
            positionY += 0xFF;
        screenY = positionY >> 8;
        roundedZ = positionZ;
        if (roundedZ < 0)
            roundedZ += 0xFF;
        screenZ = (roundedZ >> 8) + 0x20;
        sub_807FC08(&screenX, &screenY, &screenZ, 0);
        return;
    }
    free_heap_8018DA8(SHARED_MOTION_HANDLE);
    object->timer = 0;
    object->update = sub_806499C;
}
