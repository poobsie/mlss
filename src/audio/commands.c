#include "audio/driver.h"

#define SEC(name) __attribute__((section(".text.high." #name)))

u32 sub_819B418(u16 command);

SEC(sub_819B970) u32 sub_819B970(u32 command, u32 argument)
{
    return sub_819B418((u16)((command << 8) | argument));
}

SEC(sub_819B984) u32 sub_819B984(u32 player)
{
    return sub_819B418((u16)((player << 8) | 0x1000));
}

SEC(sub_819B99C) u32 sub_819B99C(u32 player)
{
    return sub_819B418((u16)((player << 8) | 0x2000));
}

SEC(sub_819B9D0) u32 sub_819B9D0(u32 soundId)
{
    return sub_819B418((u16)(soundId | 0x5000));
}

SEC(sub_819B9E8) u32 sub_819B9E8(u32 soundId)
{
    return sub_819B418((u16)(soundId | 0x6000));
}

SEC(sub_819BA00) u32 sub_819BA00(void)
{
    return sub_819B418(0x7000);
}

#define PAD(name) const u16 name##_padding SEC(name) = 0
PAD(sub_819B970);
PAD(sub_819B9D0);
PAD(sub_819B9E8);
PAD(sub_819BA00);
