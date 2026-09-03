#include "global.h"

#define SECTION(name) __attribute__((section(name)))

extern int sub_819BABC(void);
extern void sub_819B9B4(int channel, int value);
extern void sub_819A43C(void);
extern void sub_819AFA8(void* address);
extern void sub_8018E88(int value, int count);
extern int sub_819BA2C(void);
extern void sub_819B984(int value);
extern void sub_819B99C(int value);
extern void sub_80193B4(int index, u8 value, u8 arg);
extern void sub_819B95C(void);
extern void sub_819A600(void);
extern void sub_819A5D2(void);

struct RuntimeStateOverlay {
    u8 pad000[0x88C];
    u8 flags88C;
    u8 flags88D;
    u8 pad88E[2];
    u16 soundVolume;
    u8 byte892;
    u8 byte893;
    u16 value894;
    u16 value896;
    u16 values898[2];
    u16 values89C[2];
    u16 values8A0[2];
    u16 values8A4[2];
};

extern struct RuntimeStateOverlay gRuntimeState __asm__("gGameState");
extern u8 byte_3000C28;
extern u32 dword_3000C6C;
extern u32 dword_3000C78;
extern u32 dword_80000F4;

SECTION(".text.runtime_helpers_before_audio")
int sub_8019588(void) {
    int value = sub_819BABC();
    return ((u32)(-value | value)) >> 31;
}

// Preserve the original zero-filled alignment before the audio subsystem.
const u16 runtime_helpers_before_audio_padding SECTION(".text.runtime_helpers_before_audio") = 0;

SECTION(".text.runtime_helpers_after_audio")
int sub_80195F8(int index) {
    return (sub_819BA2C() >> (index + 1)) & 1;
}

SECTION(".text.runtime_helpers_after_audio")
u16 sub_8019610(int index) {
    return gRuntimeState.values898[index];
}

SECTION(".text.runtime_helpers_after_audio")
void sub_8019628(int index) {
    sub_819B984(index + 1);
    gRuntimeState.values89C[index] = 0;
}

SECTION(".text.runtime_helpers_after_audio")
void sub_8019650(int index, int value, u8 arg) {
    sub_819B99C(index + 1);
    if (value == -1) {
        value = gRuntimeState.values8A0[index] >> 8;
        if (value == 0)
            value = 0xFF;
    }
    sub_80193B4(index, (u8)value, (u8)arg);
}

SECTION(".text.runtime_helpers_after_audio")
void sub_8019694(void) {
    if (gRuntimeState.flags88C & 1) {
        sub_819B95C();
        sub_819A600();
    }
}

SECTION(".text.runtime_helpers_after_audio")
void sub_80196BC(void) {
    if (gRuntimeState.flags88C & 1)
        sub_819A5D2();
}

SECTION(".text.runtime_helpers_tail")
int sub_80197C4(int limit) {
    int count = 0;
    int value = 1;

    do {
        count++;
        value *= 10;
    } while (value <= limit);
    return count;
}

SECTION(".text.runtime_helpers_tail")
void sub_80197E0(void) {
    byte_3000C28 = 0;
    dword_3000C6C = dword_80000F4;
    dword_3000C78 = 0;
}
