#include "audio/driver_state.h"
#include "gba/io_reg.h"

#define SEC(name) \
    __attribute__((section(".text.audio_voice_routing." #name)))
#define REG_PSG_STEREO_ROUTING (*(vu8*)(REG_ADDR_SOUNDCNT_L + 1))

SEC(sub_819AB78)
void audio_driver_update_voice_stereo_routing(struct AudioDriverVoice* voice)
{
    u8 channelMask = 1 << (voice->voiceIndex & 3);
    u32 leftMask;
    u8 routing = REG_PSG_STEREO_ROUTING;

    leftMask = channelMask << 4;
    routing &= ~(channelMask | leftMask);
    if (voice->pan <= 0x80)
        routing |= channelMask;
    if (voice->pan > 0x7E)
        routing |= leftMask;
    REG_PSG_STEREO_ROUTING = routing;
}
