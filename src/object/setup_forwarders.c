#include "audio/sound_effects.h"
#include "object/functions.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

s32 sub_8086C64(s32 arg0, s32 arg1, s32 arg2);
s32 sub_8087124(s32 arg0, s32 arg1, s32 arg2);
s32 sub_810DD7C();

#define DEFINE_PADDED_FORWARDER(name, sound, target)                   \
    SEC(name) s32 name(s32 arg0, s32 arg1, s32 arg2)                   \
    {                                                                  \
        sound_effect_stop(sound);                                      \
        return target(arg0, arg1, arg2);                               \
    }                                                                  \
    SEC(name) const u16 name##_padding = 0;

DEFINE_PADDED_FORWARDER(object_stop_sound_6c_then_forward_setup_a, 0x6C, sub_8087124)
DEFINE_PADDED_FORWARDER(object_stop_sound_6c_then_forward_setup_b, 0x6C, sub_8086C64)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_a, 0x81, sub_8087124)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_b, 0x81, sub_8086C64)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_c, 0x81, sub_810DD7C)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_d, 0x81, sub_8087124)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_e, 0x81, sub_810DD7C)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_f, 0x81, sub_8087124)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_g, 0x81, sub_8086C64)
DEFINE_PADDED_FORWARDER(object_stop_sound_81_then_forward_setup_h, 0x81, sub_810DD7C)

#define DEFINE_FORWARDER(name, sound, target)                          \
    SEC(name) s32 name(s32 arg0, s32 arg1, s32 arg2)                   \
    {                                                                  \
        sound_effect_stop(sound);                                      \
        return target(arg0, arg1, arg2);                               \
    }

DEFINE_FORWARDER(object_stop_sound_11a_then_forward_setup_a, 0x11A, sub_8086C64)
DEFINE_FORWARDER(object_stop_sound_11a_then_forward_setup_b, 0x11A, sub_810DD7C)
DEFINE_FORWARDER(object_stop_sound_11c_then_forward_setup, 0x11C, sub_8087124)

SEC(object_forward_setup_then_stop_sound_81)
s32 object_forward_setup_then_stop_sound_81(void)
{
    s32 result;

    result = sub_810DD7C();
    sound_effect_stop(0x81);
    return result;
}
SEC(object_forward_setup_then_stop_sound_81)
const u16 object_forward_setup_then_stop_sound_81_padding = 0;
