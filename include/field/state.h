#ifndef GUARD_FIELD_STATE_H
#define GUARD_FIELD_STATE_H

#include "global.h"

struct FieldConfigurationSource {
    u8 unknown00[0x21];
    u8 kind;
};

struct FieldStateObject {
    u8 unknown000[4];
    u16 state;
    u8 unknown006[0x1E];
    u8 flags024;
    u8 unknown025[0x2F];
    u8 mode054;
    u8 unknown055[0x1B9];
    u8 flags20E;
    u8 unknown20F[3];
    u8 flags212;
    u8 unknown213;
    u8 flags214;
    u8 unknown215[0x57];
    s16 configurationValue;
    u8 configurationSelector;
    u8 unknown26F[0x25];
    struct FieldConfigurationSource* configurationSource;
    u8 unknown298[0xC3];
    u8 flags35B;
};

struct __attribute__((packed)) FieldLowThreeBits {
    u8 value : 3;
    u8 rest : 5;
};

struct __attribute__((packed)) FieldBitSix {
    u8 low : 6;
    u8 value : 1;
    u8 high : 1;
};

#endif
