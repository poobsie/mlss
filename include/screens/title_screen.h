#ifndef GUARD_SCREENS_TITLE_SCREEN_H
#define GUARD_SCREENS_TITLE_SCREEN_H

#include "process/process.h"

enum TitleScreenStates {
    // Fade in from white.
    TS_STATE_FADE_IN = 0,
    // Suitcase falls out of sky and opens, revealing logo.
    TS_STATE_TITLE_ANIMATION,
    // Waits a few frames and then show PRESS START.
    TS_STATE_PRESS_START_SHOW,
    // Wait for player input for press start.
    TS_STATE_PRESS_START_WAIT,
    // Suitcase opening animation.
    TS_STATE_SUITCASE_OPENS,
    // Wait for player to select game.
    TS_STATE_GAME_SELECT,
    // Player has chosen, load next process and fade out.
    TS_STATE_FADE_OUT
};

enum TitleScreenItems {
    TS_ITEM_SUITCASE = 0,
    TS_ITEM_ML_LOGO,
    TS_ITEM_SS_TEXT,
    TS_ITEM_LICENSE_TEXT,
    TS_ITEM_PRESS_START_TEXT,
    TS_ITEM_POINTER,

    TS_ITEM_COUNT
};

enum TitleScreenItemSuitcaseStates {
    TS_ITEM_SC_STATE_FALLING = 0,
    TS_ITEM_SC_STATE_HIT_GROUND,
    TS_ITEM_SC_STATE_FALL_OVER,
    TS_ITEM_SC_STATE_OPEN,
    TS_ITEM_SC_STATE_OPEN_WAIT,
    TS_ITEM_SC_STATE_CLOSE,
    TS_ITEM_SC_STATE_MOVE_LEFT,
    TS_ITEM_SC_STATE_BUMP_OPEN,
};

enum TitleScreenSprites {
    TS_SPRITE_PRESS_START_TEXT = 0,
    TS_SPRITE_BEAN_POINTER,
    // "MARIO & LUIGI".
    TS_SPRITE_ML_GAME_TEXT,
    // "MARIO BROS.".
    TS_SPRITE_MB_GAME_TEXT,
    // "OPTIONS".
    TS_SPRITE_OPTIONS_TEXT,
    TS_SPRITE_SUITCASE,
    TS_SPRITE_LICENSE_TEXT,
    // The contents of the suitcase.
    TS_SPRITE_SUITCASE_VISUAL,
    // "SUPERSTAR SAGA".
    TS_SPRITE_SS_TEXT,
};

enum TitleScreenSuitcaseVisualStates {
    TS_SV_STATE_APPEAR = 0,
    TS_SV_STATE_IDLE,
    TS_SV_STATE_DISAPPEAR,
};

enum CompanyIntroState {
    COMPANY_INTRO_BROTHERS_FALL,
    COMPANY_INTRO_IMPACT_SHAKE,
    COMPANY_INTRO_BROTHERS_HOLD,
    COMPANY_INTRO_BROTHERS_FADE_OUT,
    COMPANY_INTRO_LOGO_FADE_IN,
    COMPANY_INTRO_LOGO_HOLD,
    COMPANY_INTRO_LOGO_FADE_OUT,
};

struct CompanyIntro {
    struct Process process;
    s8 phaseTimer;
    u8 brothersInMotion : 1;
    s32 backgroundOffsetY;
    s32 marioX;
    s32 luigiX;
    s32 marioY;
    s32 luigiY;
    s32 gravity;
    s32 verticalVelocity;
    struct Process* renderProcess;
    struct Sprite* mario;
    struct Sprite* luigi;
    struct Sprite* alphaDreamLogo;
};

extern struct ProcessDefinition gCompanyIntroProcessDefinition __asm__("stru_8CDC258");
extern struct ProcessDefinition gScreenRenderProcessDefinition __asm__("stru_8CDC268");

struct CompanyIntro* company_intro_create(struct CompanyIntro* intro, u8 priority, char* label);
void company_intro_update(struct CompanyIntro* intro);
void company_intro_destroy(struct CompanyIntro* intro, int flags);
struct Process* screen_render_process_create(struct Process* process, u8 priority, char* label);
void screen_render_process_update(void);

struct TitleScreen {
    struct Process process;
    s8 brightness;
    u8 suitcaseVisualState : 2;
    // Index to the state after fade in.
    u8 entryStateIdx : 2;
    bool8 isSkippingSuitcaseAnim : 1;
    bool8 skipSuitcaseAnim : 1;
    // Index used for game selection text sprites.
    u8 spriteIdx : 2;

    int xPosSuitcase;
    int yPosSuitcase;
    s16 xVelocitySuitcase;
    s16 yVelocitySuitcase;

    s16 mlTextProgression;
    int mlTextPosY;
    int mlTextScaleX;
    int mlTextScaleY;

    s16 ssTextProgression;
    int ssTextPosY;
    int ssTextScaleX;
    int ssTextScaleY;

    s16 nTextProgression;
    int nTextPosY;
    int nTextScaleX;
    int nTextScaleY;

    s16 psTextVelocity;
    int psTextPosY;

    int beanPosX;
    int beanPosY;
    s16 beanVelocityX;
    s16 beanVelocityY;

    char pad1[16];

    s8 states[6];
    u16 timer;

    char pad2[12];

    struct BgAffineSrcData mlTextAffineSrc;
    struct BgAffineDstData mlTextAffineDst;
    struct MarioBrosScoreVisual* mbsv;
    s8 selection;
    struct Sprite* sprites[9];
};

#endif
