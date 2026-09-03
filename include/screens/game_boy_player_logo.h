#ifndef GUARD_SCREENS_GAME_BOY_PLAYER_LOGO_H
#define GUARD_SCREENS_GAME_BOY_PLAYER_LOGO_H

#include "process/process.h"

enum GameBoyPlayerLogoState {
    GAME_BOY_PLAYER_LOGO_FADE_IN,
    GAME_BOY_PLAYER_LOGO_HOLD,
    GAME_BOY_PLAYER_LOGO_FADE_OUT,
};

struct GameBoyPlayerLogo {
    struct Process process;
    s8 phaseTimer;
    u16 currentDpad;
    u16 previousDpad;
    u32 lastChordFrame;
    u32 previousChordFrame;
    void (*finishCallback)(void);
};

extern struct ProcessDefinition gGameBoyPlayerLogoProcessDefinition
    __asm__("stru_8CDBD78");

struct GameBoyPlayerLogo* game_boy_player_logo_create(
    struct GameBoyPlayerLogo* logo,
    u8 priority,
    char* label,
    void (*finishCallback)(void));
void game_boy_player_logo_update(struct GameBoyPlayerLogo* logo);

#endif
