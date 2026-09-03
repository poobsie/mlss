#include "global.h"
#include "link/multiplayer.h"

struct MultiplayerFrameState {
    u8 active;
    u8 transferEnabled;
    u8 unknown02;
    u8 unknown03;
    u8 bufferSwapPending;
    u8 unknown05;
    u8 transferReady;
    u8 serialStatusBit;
    u8 unknown08;
    u8 inactiveInterruptInstalled;
    u8 fieldA;
    u8 fieldB;
    u8 unknown0C[8];
    u32 transferCounter;
    s32 transferResult;
    u32 buffer1C;
    u32 buffer20;
    u32 buffer24;
    u32 buffer28;
};

void multiplayer_frame_update(void)
{
    struct MultiplayerFrameState * volatile *global =
        (struct MultiplayerFrameState **)0x03000D0C;
    struct MultiplayerFrameState *state = *global;

    if (state != 0) {
        int active = state->active;

        if (active != 0) {
            if (state->transferEnabled != 0 && state->transferReady != 0) {
                u32 temp;
                vu16 *sio;
                struct MultiplayerFrameState *current;
                u32 sioData;

                state->transferResult = -2;
                temp = state->buffer28;
                state->buffer28 = state->buffer24;
                state->buffer24 = temp;

                if (state->bufferSwapPending != 0) {
                    temp = state->buffer20;
                    state->buffer20 = state->buffer1C;
                    state->buffer1C = temp;
                    state->bufferSwapPending = 0;
                    (*global)->transferCounter = 0;
                }

                current = *global;
                sio = (vu16 *)0x04000128;
                current->serialStatusBit = (*(vu32 *)sio << 25) >> 31;
                sioData = 0xFEFE;
                sio[1] = sioData;
                sio[0] |= 0x80;
                *(vu16 *)0x0400010E = 0xC0;
            }
        } else {
            if (state->inactiveInterruptInstalled == 0) {
                *(vu16 *)0x04000208 = active;
                *(vu16 *)0x03007FF8 |= 0x80;
                *(vu16 *)0x04000208 = 1;
            }
            (*global)->inactiveInterruptInstalled = active;
        }
    }
}

void multiplayer_mark_transfer_ready(void)
{
    struct MultiplayerFrameState *state =
        *(struct MultiplayerFrameState **)0x03000D0C;

    if (state->active != 0)
        state->transferReady = 1;
}
