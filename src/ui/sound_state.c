#include "global.h"
#include "audio/sound_effects.h"

#define SEC(name) __attribute__((section(".text.high." #name)))
#define U16AT(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32AT(p, o) (*(u32*)((u8*)(p) + (o)))

SEC(sub_816AFDC) void sub_816AFDC(void* p) {
    U32AT(p, 0x490) &= ~8;
}

SEC(sub_816D6D4) void sub_816D6D4(void* p) {
    if (U32AT(p, 0x88) != 0) {
        U32AT(p, 0x88) = 0;
        sound_effect_stop(0x97);
    }
}

SEC(sub_816D6F0) void sub_816D6F0(void* p) {
    if (U32AT(p, 0x88) == 0) {
        U32AT(p, 0x88) = 1;
        sound_effect_play(0x97, SOUND_VOLUME_UNCHANGED);
    }
}

SEC(sub_8171DD4) void sub_8171DD4(void* p) {
    if (U16AT(p, 0xEA) != 0) {
        U16AT(p, 0xEA) = 0;
        sound_effect_stop(0x97);
    }
}

#define PAD(name) const u16 name##_padding SEC(name) = 0
PAD(sub_816AFDC);
PAD(sub_816D6D4);
PAD(sub_816D6F0);
PAD(sub_8171DD4);
