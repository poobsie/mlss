#ifndef GUARD_MARIO_BROS_OBJECT_H
#define GUARD_MARIO_BROS_OBJECT_H

#include "global.h"

/*
 * Shared prefix used by several Mario Bros minigame object classes.
 * value18 and value1C remain neutral because movement objects use them as
 * deltas while animation objects store table-selected values in value18.
 */
struct MarioBrosObject {
    u8 unknown00[4];
    u8 state;
    u8 unknown05;
    u16 value06;
    u8 flags08;
    u8 displayFrame;
    u8 flags0A;
    u8 animationFrame;
    u8 animationVariant;
    u8 unknown0D[3];
    u32 positionX;
    u32 positionY;
    u32 value18;
    u32 value1C;
    u16 value20;
    u8 unknown22[2];
    u16 value24;
    u8 value26;
    u8 unknown27[9];
    void* value30;
    void* value34;
    void* value38;
};

struct __attribute__((packed)) MarioBrosFlags08 {
    u8 mode : 2;
    u8 variantBit2 : 1;
    u8 unknown : 5;
};

struct __attribute__((packed)) MarioBrosFlags0A {
    u8 mode : 2;
    u8 enabled : 1;
    u8 tableValue : 4;
    u8 high : 1;
};

struct __attribute__((packed)) MarioBrosDisplayFrame {
    u8 frame : 3;
    u8 unknown : 5;
};

#endif
