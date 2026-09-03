#ifndef GUARD_RUNTIME_CALLBACK_PACKET_H
#define GUARD_RUNTIME_CALLBACK_PACKET_H

#include "global.h"

typedef void (*RuntimePairCallback)(s32 first, s32 second);

struct RuntimeCallbackPacket {
    s32 first;
    s32 second;
    u8 unknown08[0x0C];
    RuntimePairCallback callback;
};

void runtime_invoke_pair_callback(struct RuntimeCallbackPacket* packet);
void sub_801DC38(struct RuntimeCallbackPacket* packet);

#endif
