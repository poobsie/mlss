#include "audio/sound_effects.h"

#define audio_play_sound_50 sub_8029878
#define audio_stop_scene_sound_set sub_803C610

void audio_play_sound_50(void)
    __attribute__((section(".text.early_code_helpers.sub_8029878")));
void audio_play_sound_50(void) {
    sound_effect_play(0x50, SOUND_VOLUME_UNCHANGED);
}

void audio_stop_scene_sound_set(void)
    __attribute__((section(".text.text_early_helpers_04.sub_803C610")));
void audio_stop_scene_sound_set(void) {
    sound_effect_stop(0x157);
    sound_effect_stop(0x87);
    sound_effect_stop(0xDB);
    sound_effect_stop(0xDA);
    sound_effect_stop(0xDA);
}
