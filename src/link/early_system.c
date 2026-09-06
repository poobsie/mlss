#include "global.h"
#include "link/early_system.h"

#define SEC(name) __attribute__((section(".text.link_early." #name)))

struct LinkControlState {
    u8 statusFlags;
};

extern struct LinkControlState gLinkControlState __asm__("stru_3000D18");

SEC(sub_801AEA0)
s32 link_scale_transfer_value(s32 value, s32 unused, s32 fallback)
{
    switch (gLinkControlState.statusFlags >> 6) {
    case 0:
        fallback = value;
        break;
    case 1:
        fallback = value << 2;
        break;
    case 2:
        fallback = value << 4;
        break;
    case 3:
        fallback = value << 6;
        break;
    }
    return fallback;
}
SEC(sub_801AEA0) const u16 link_scale_transfer_value_padding = 0;
