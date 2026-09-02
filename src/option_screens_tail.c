#include "global.h"
#include "common.h"

void generate_window_bg_8051B98(struct WindowAttr*, int*, u8, u8, u8, u8, int);

void sub_805420C(struct OPTNProcess* optn) {
    u8* dimensions = (u8*)0x083A2918;
    u8 width = (u32)(dimensions[0] << 24) >> 24;
    u8 height = (u32)(dimensions[2] << 24) >> 24;
    u8 x = 15 - width / 2;
    u8 y = 10 - height / 2;

    generate_window_bg_8051B98(&optn->field_48, optn->winw, x, y, width, height, 0xC800);
}

void option_screen_set_ok_button(struct OPTNProcess* optn, int width, int height) {
    u8 x = 15 - width / 2;
    u8 y = 10 - height / 2;

    generate_window_bg_8051B98(&optn->field_48, optn->winw, x, y, width, height, 0xC800);
    optn->okButtonPosX = x * 8 + width * 4 - 16;
    optn->okButtonPosY = (y + height) * 8 - 22;
}
