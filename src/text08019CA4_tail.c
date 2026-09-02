#include "global.h"

struct LinkStateTail {
    u8 field0;
    u8 field1;
    u8 field2;
    u8 field3;
    u8 field4;
    u8 field5;
    u8 field6;
    u8 field7;
    u8 field8;
    u8 field9;
    u8 fieldA;
    u8 fieldB;
    u8 pad0C[8];
    u32 field14;
    s32 field18;
    u32 field1C;
    u32 field20;
    u32 field24;
    u32 field28;
};

void sub_801A2A0(void)
{
    struct LinkStateTail * volatile *global = (struct LinkStateTail **)0x03000D0C;
    struct LinkStateTail *state = *global;

    if (state != 0) {
        int field0 = state->field0;

        if (field0 != 0) {
            if (state->field1 != 0 && state->field6 != 0) {
                u32 temp;
                vu16 *sio;
                struct LinkStateTail *current;
                u32 sioData;

                state->field18 = -2;
                temp = state->field28;
                state->field28 = state->field24;
                state->field24 = temp;

                if (state->field4 != 0) {
                    temp = state->field20;
                    state->field20 = state->field1C;
                    state->field1C = temp;
                    state->field4 = 0;
                    (*global)->field14 = 0;
                }

                current = *global;
                sio = (vu16 *)0x04000128;
                current->field7 = (*(vu32 *)sio << 25) >> 31;
                sioData = 0xFEFE;
                sio[1] = sioData;
                sio[0] |= 0x80;
                *(vu16 *)0x0400010E = 0xC0;
            }
        } else {
            if (state->field9 == 0) {
                *(vu16 *)0x04000208 = field0;
                *(vu16 *)0x03007FF8 |= 0x80;
                *(vu16 *)0x04000208 = 1;
            }
            (*global)->field9 = field0;
        }
    }
}

void sub_801A33C(void)
{
    struct LinkStateTail *state = *(struct LinkStateTail **)0x03000D0C;

    if (state->field0 != 0)
        state->field6 = 1;
}
