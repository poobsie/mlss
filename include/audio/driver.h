#ifndef GUARD_AUDIO_DRIVER_H
#define GUARD_AUDIO_DRIVER_H

#include "global.h"

#define audio_driver_send_command_bytes sub_819B970
#define audio_driver_stop_music_player sub_819B984
#define audio_driver_resume_music_player sub_819B99C
#define audio_driver_play_sound sub_819B9D0
#define audio_driver_stop_sound sub_819B9E8
#define audio_driver_stop_all_sounds sub_819BA00

void audio_update(void);
void audio_timer0_interrupt(void);
u32 audio_driver_send_command_bytes(u32 command, u32 argument);
u32 audio_driver_stop_music_player(u32 player);
u32 audio_driver_resume_music_player(u32 player);
u32 audio_driver_play_sound(u32 soundId);
u32 audio_driver_stop_sound(u32 soundId);
u32 audio_driver_stop_all_sounds(void);

#endif
