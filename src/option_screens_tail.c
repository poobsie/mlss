#include "global.h"
#include "common.h"
#include "process.h"

void generate_window_bg_8051B98(struct WindowAttr*, int*, u8, u8, u8, u8, int);

struct OptionTailProcess {
    struct Process process;
    u8 brightness;
    u8 pad_1D[3];
    void* field_20;
    u8 pad_24[4];
    void* field_28;
    void* field_2C;
    void* field_30;
    void* field_34;
    struct WindowAttr window;
};

void sub_8053FC4(struct OptionTailProcess* optn) {

    switch (optn->process.state) {
    case 0:
        if (optn->window.field_1 > 0) {
            sub_8051EE0(&optn->window);
        } else if (--optn->brightness == 0 || (gGameState.field_2A & 0xB)) {
            *(u8*)(*(u32*)0x0839EC80 + 1) |= 0x20;
            optn->window.field_0_0 = 1;
            optn->window.field_1 = 7;
            optn->process.state = 1;
        }
        break;
    case 1:
        sub_8051EE0(&optn->window);
        {
        s8 value = optn->window.field_1;
        if (value == 0) {
            if (optn != 0) {
                optn->process.definition = (void*)0x08CDC1C8;
                if (optn->field_34 != 0)
                    free_heap_8018D9C(optn->field_34);
                if (optn->field_20 != 0)
                    free_heap_8018D9C(optn->field_20);
                if (optn->field_28 != 0)
                    free_heap_8018D9C(optn->field_28);
                if (optn->field_2C != 0)
                    free_heap_8018D9C(optn->field_2C);
                free_heap_8018DA8(optn->field_30);
                *(u16*)0x02000000 = value;
                *(u16*)0x02000050 = value;
                process_remove(&optn->process, 3);
            }
            open_init_8055A00(alloc_Zero(0xE4, 0, (char*)0x081E2714, 0), 8,
                              (char*)0x081E2714, 2);
        }
        }
        break;
    }
}

void sub_80540B0(void* optn) {
    u8* dimensions = (u8*)0x083A2978;
    u8 width = (u32)(dimensions[0] << 24) >> 24;
    u8 height = (u32)(dimensions[2] << 24) >> 24;
    u8 x = 15 - width / 2;
    u8 y = 10 - height / 2;

    generate_window_bg_8051B98(optn + 0x38, *(int**)(optn + 0x34), x, y, width, height, 0xE000);
    *(u8*)(*(u32*)0x0839EC80 + 0x4A) |= 0x10;
}

void sub_805410C(struct OptionTailProcess* optn, u32 flags) {
    optn->process.definition = (void*)0x08CDC1C8;
    if (optn->field_34 != 0)
        free_heap_8018D9C(optn->field_34);
    if (optn->field_20 != 0)
        free_heap_8018D9C(optn->field_20);
    if (optn->field_28 != 0)
        free_heap_8018D9C(optn->field_28);
    if (optn->field_2C != 0)
        free_heap_8018D9C(optn->field_2C);
    free_heap_8018DA8(optn->field_30);
    *(u16*)0x02000000 = 0;
    *(u16*)0x02000050 = 0;
    process_remove(&optn->process, flags);
}

void sub_8054164(void) {
    int value = gGameState.field_880;

    sub_8020A78();
    dword_3000D48(stru_203FFB8.field_3C, stru_203FFB8.field_3C + 0xA14);
    value = dword_3000D4C(stru_203FFB8.field_3C, value);
    gGameState.field_880 = value;
}

void sub_80541B0(void* optn, int width, int height) {
    int x = 15 - width / 2;
    int y = 10 - height / 2;
    struct WindowAttr* window = optn + 0x40;
    int* winw = *(int**)(optn + 0x38);

    generate_window_bg_8051B98(window, winw, x, y, width, height, 0xE000);
    *(u8*)(*(u32*)0x0839EC80 + 0x4A) |= 0x10;
}

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
