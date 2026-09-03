#include "global.h"
#include "audio/driver.h"

#define SECTION(name) __attribute__((section(name)))

#define AUDIO_ENABLED 1

extern void sub_819B95C(void);
extern void sub_819A600(void);
extern void sub_819A5D2(void);

struct AudioDriverStateOverlay {
    u8 padding[0x88C];
    u8 flags;
};

extern struct AudioDriverStateOverlay gAudioDriverState __asm__("gGameState");

SECTION(".text.audio_driver")
void audio_update(void) {
    if (gAudioDriverState.flags & AUDIO_ENABLED) {
        sub_819B95C();
        sub_819A600();
    }
}

SECTION(".text.audio_driver")
void audio_timer0_interrupt(void) {
    if (gAudioDriverState.flags & AUDIO_ENABLED)
        sub_819A5D2();
}
