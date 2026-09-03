#include "global.h"
#include "audio/music.h"
#include "audio/sound_effects.h"
#include "common.h"
#include "link/multiplayer.h"
#include "runtime/functions.h"
#include "save/profile.h"
#include "screens/options.h"
#include "screens/title_screen.h"

struct CompanyIntro* company_intro_create(struct CompanyIntro* intro, u8 priority, char* label) {
    struct Process* renderProcess;
    void* cgdw;
    struct TitleSaveSummary* saveSummary;
    vu32 zero;

    process_add(&intro->process, priority, label);
    intro->process.definition = &gCompanyIntroProcessDefinition;

    BUFFER_REG_SOUNDCNT_L = 0x7FFF;
    gGameState.field_2 = 1;
    BUFFER_REG_DISPCNT = 0;
    sub_8017E34();

    renderProcess = (struct Process*)alloc_Zero(sizeof(struct Process), 0, "OPDR", 0);
    process_add(renderProcess, 8, "OPDR");
    renderProcess->definition = &gScreenRenderProcessDefinition;
    intro->renderProcess = renderProcess;
    renderProcess->parentProcess = &intro->process;

    dword_3000C78 = 0;
    sub_8020994(0, 0, 0, 0x80);
    stru_203FFB8.field_0_2 = 1;

    intro->mario = sub_8020DD0(2, 4097, 1, -1, -1, -1, -1);
    sub_801E150(intro->mario, 12, -1, 0, 0);
    intro->mario->xPosition = 80;
    intro->mario->yPosition = -35;
    intro->mario->field_11_6 = 1;

    intro->luigi = sub_8020DD0(2, 4098, 1, -1, -1, -1, -1);
    sub_801E150(intro->luigi, 12, -1, 0, 0);
    intro->luigi->xPosition = 160;
    intro->luigi->yPosition = -35;

    intro->alphaDreamLogo = sub_8020DD0(7, 33103, 1, -1, -1, -1, -1);
    sub_801E150(intro->alphaDreamLogo, 0, -1, 0, 0);
    intro->alphaDreamLogo->xPosition = 120;
    intro->alphaDreamLogo->yPosition = 74;

    sub_80213A0(0, 4109, -1, 1);
    sub_80213A0(0, 4110, -1, 1);
    intro->marioX = 20480;
    intro->marioY = -8960;
    intro->luigiX = 40960;
    intro->luigiY = -8960;

    cgdw = alloc_zero_8018DB4(0x8000, 1, "CGDW", 0);
    dword_3000C84(dword_83A2B48, cgdw);
    CpuFastSet(cgdw, (void*)BG_CHAR_ADDR(2), (sub_80198B0(dword_83A2B48) >> 2) & 0x1FFFFF);
    CpuFastSet(dword_83A2F98, (void*)BG_SCREEN_ADDR(28), 320);
    zero = 0;
    CpuFastSet((int*)&zero, (void*)0x600E500, 0x10000C0);
    dword_3000C84(dword_83A34B8, cgdw);
    CpuFastSet(cgdw, (void*)BG_CHAR_ADDR(3), (sub_80198B0(dword_83A34B8) >> 2) & 0x1FFFFF);
    CpuFastSet(dword_83A3860, (void*)BG_SCREEN_ADDR(29), 320);
    free_heap_8018DA8(cgdw);

    dword_3000C78 = sub_800063C;
    saveSummary = save_get_title_summary();
    gTitleSaveSummary.value0 = saveSummary->value0;
    gTitleSaveSummary.value4 = saveSummary->value4;
    gTitleSaveSummary.titleState = 0;
    gTitleSaveSummary.easySleepEnabled = gSaveState->easySleepEnabled;
    gTitleSaveSummary.autoSleepEnabled = gSaveState->autoSleepEnabled;
    gTitleSaveSummary.value7_4 = gSaveState->value8_0;
    gTitleSaveSummary.gameBoyPlayerDetected = gGameState.gameBoyPlayerDetected;

    BUFFER_REG_BG0CNT = BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(28);
    BUFFER_REG_BG0HOFS = 0;
    BUFFER_REG_BG0VOFS = 99;

    intro->backgroundOffsetY = 25344;
    CpuFastSet(&dword_83A3498, (void*)0x2000000 + 0x80, 8);
    BUFFER_REG_SOUNDCNT_L = 0x7FFF;
    gGameState.field_2 = -1;

    sprite_show_8020CBC(intro->mario);
    sprite_show_8020CBC(intro->luigi);

    intro->verticalVelocity = 0;
    intro->gravity = 117;
    intro->brothersInMotion = 1;
    intro->process.state = COMPANY_INTRO_BROTHERS_FALL;

    BUFFER_REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_OBJ_ON;

    return intro;
}

void company_intro_update(struct CompanyIntro* intro) {
    switch (intro->process.state) {
        case COMPANY_INTRO_BROTHERS_FALL:
            intro->marioY += intro->verticalVelocity;
            intro->luigiY += intro->verticalVelocity;
            intro->backgroundOffsetY -= intro->verticalVelocity;
            intro->verticalVelocity = intro->verticalVelocity + intro->gravity;
            if (intro->backgroundOffsetY <= 0) {
                intro->phaseTimer = 16;
                intro->backgroundOffsetY = 0;
                intro->verticalVelocity = -1324;
                sound_effect_play(134, SOUND_VOLUME_UNCHANGED);
                intro->process.state = COMPANY_INTRO_IMPACT_SHAKE;
            }
            break;

        case COMPANY_INTRO_IMPACT_SHAKE:
            if (intro->phaseTimer > 10) {
                intro->backgroundOffsetY ^= 512;
            } else {
                intro->backgroundOffsetY ^= 256;
            }
            intro->phaseTimer--;
            if (intro->phaseTimer == 0) {
                intro->phaseTimer = 100;
                BUFFER_REG_BG0VOFS = 0;
                intro->process.state = COMPANY_INTRO_BROTHERS_HOLD;
            }
            break;

        case COMPANY_INTRO_BROTHERS_HOLD:
            if (intro->phaseTimer == 80) {
                sound_effect_play(221, SOUND_VOLUME_UNCHANGED);
            }
            intro->phaseTimer--;
            if (intro->phaseTimer == 0) {
                intro->phaseTimer = 16;
                BUFFER_REG_BLDCNT = 191;
                BUFFER_REG_BLDY = 0;
                intro->process.state = COMPANY_INTRO_BROTHERS_FADE_OUT;
            }
            break;

        case COMPANY_INTRO_BROTHERS_FADE_OUT:
            intro->phaseTimer--;
            BUFFER_REG_BLDY = 16 - intro->phaseTimer;
            if (intro->phaseTimer == 0) {
                sprite_hide_8021F20(intro->mario);
                sprite_hide_8021F20(intro->luigi);
                CpuFastSet(dword_83A3D60, (void*)0x2000000 + 0x80, 8);
                gGameState.field_2 = -1;
                BUFFER_REG_BG0CNT = BGCNT_CHARBASE(3) | BGCNT_SCREENBASE(29);
                sprite_show_8020CBC(intro->alphaDreamLogo);
                intro->alphaDreamLogo->field_12_4 = 1;
                intro->phaseTimer = 16;
                intro->process.state = COMPANY_INTRO_LOGO_FADE_IN;
            }
            break;

        case COMPANY_INTRO_LOGO_FADE_IN:
            intro->phaseTimer--;
            BUFFER_REG_BLDY = intro->phaseTimer;
            if (gGameState.field_2A & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                intro->phaseTimer = 16 - intro->phaseTimer;
                intro->process.state = COMPANY_INTRO_LOGO_FADE_OUT;
            } else if (intro->phaseTimer == 0) {
                intro->phaseTimer = 120;
                intro->alphaDreamLogo->field_12_4 = 0;
                intro->alphaDreamLogo->field_12_1 = 1;
                intro->process.state = COMPANY_INTRO_LOGO_HOLD;
            }
            break;

        case COMPANY_INTRO_LOGO_HOLD:
            if ((gGameState.field_2A & (A_BUTTON | B_BUTTON | START_BUTTON)) == 0) {
                intro->phaseTimer--;
                if (intro->phaseTimer != 0) {
                    break;
                }
            }
            intro->phaseTimer = 16;
            intro->process.state = COMPANY_INTRO_LOGO_FADE_OUT;
            break;

        case COMPANY_INTRO_LOGO_FADE_OUT:
            intro->phaseTimer--;
            BUFFER_REG_BLDY = 16 - intro->phaseTimer;
            if (intro->phaseTimer == 0) {
                if (intro) {
                    intro->process.definition = &gCompanyIntroProcessDefinition;
                    sub_8021FD4();
                    if (intro->renderProcess) {
                        process_remove(intro->renderProcess, 3);
                    }
                    process_remove(&intro->process, 3);
                }
                title_screen_create(alloc_Zero(sizeof(struct TitleScreen), 0, "OPEN", 0), 8, "OPEN", 0);
                return;
            }
            break;
    }

    if (intro->process.state < COMPANY_INTRO_BROTHERS_FADE_OUT) {
        if (intro->process.state != COMPANY_INTRO_BROTHERS_FALL && intro->brothersInMotion) {
            intro->marioX -= 384;
            intro->luigiX += 384;
            intro->marioY += intro->verticalVelocity;
            intro->luigiY += intro->verticalVelocity;
            intro->verticalVelocity += intro->gravity;
            if (intro->marioY >= 24064) {
                bool32 temp;
                intro->marioY = 24064;
                intro->luigiY = 24064;
                sub_80210A8(intro->mario, 2, 4109, 1, -1, -1, -1, -1);
                sub_801E150(intro->mario, 0, -1, 0, 0);
                sprite_show_8020CBC(intro->mario);
                temp = intro->mario->field_11_6;
                temp ^= 1;
                intro->mario->field_11_6 = temp;
                intro->mario->field_12_1 = 1;

                sub_80210A8(intro->luigi, 2, 4110, 1, -1, -1, -1, -1);
                sub_801E150(intro->luigi, 0, -1, 0, 0);
                sprite_show_8020CBC(intro->luigi);
                intro->luigi->field_12_1 = 1;
                intro->brothersInMotion = 0;
            }
        }
        BUFFER_REG_BG0VOFS = intro->backgroundOffsetY / 256;
        intro->mario->xPosition = intro->marioX / 256;
        intro->mario->yPosition = intro->marioY / 256;
        intro->luigi->xPosition = intro->luigiX / 256;
        intro->luigi->yPosition = intro->luigiY / 256;
    }

    sub_8021F7C();
}

// https://decomp.me/scratch/WOp2S
#ifndef NONMATCHING
asm_unified(".include \"asm/nonmatching/title_screen_create.s\"");
#else
struct TitleScreen* title_screen_create(struct TitleScreen* titleScreen, u8 priority, char* label,
                                      int selection) {
    struct TitleSaveSummary* saveSummary;
    void* cgdw;
    u32 i;
    // int sel;
    char* tmp1;
    void (**tmp2)();
    struct Sprite** sprites;

    // sel = selection;

    process_add(&titleScreen->process, priority, label);
    titleScreen->process.definition = &gTitleScreenProcessDefinition;

    (*(vu16*)(0x2000000 + 0x80)) = 0x7FFF;
    gGameState.field_2 = 1;
    (*(vu16*)(0x2000000 + 0x0)) = 0;
    sub_8017E34();
    gGameState.field_31 = 8;

    saveSummary = save_get_title_summary();
    gTitleSaveSummary.value0 = saveSummary->value0;
    gTitleSaveSummary.value4 = saveSummary->value4;
    gTitleSaveSummary.titleState = 0;
    gTitleSaveSummary.easySleepEnabled = gSaveState->easySleepEnabled;
    gTitleSaveSummary.autoSleepEnabled = gSaveState->autoSleepEnabled;
    gTitleSaveSummary.value7_4 = gSaveState->value8_0;
    gTitleSaveSummary.gameBoyPlayerDetected = gGameState.gameBoyPlayerDetected;

    dword_3000DA0 = alloc_Zero(340, 0, "ORST", 1);
    titleScreen->scoreDisplay = title_screen_score_display_create(alloc_Zero(0x24, 0, "OPDR", 0), 8, "OPDR", gTitleSaveSummary.value0,
                           gTitleSaveSummary.value4);
    titleScreen->scoreDisplay->process.parentProcess = &titleScreen->process;

    titleScreen->selection = selection != 0 ? selection - 1 : 0;
    titleScreen->suitcaseVisualState = 0;
    titleScreen->brightness = 16;
    titleScreen->isSkippingSuitcaseAnim = 0;
    titleScreen->skipSuitcaseAnim = 1;
    titleScreen->itemStates[0] = 0;

    // Why.
    tmp2 = &dword_3000C78;
    tmp1 = "CGDW";
    sprites = titleScreen->sprites;

    titleScreen->itemStates[1] = 0xFF;
    titleScreen->itemStates[2] = 0xFF;
    titleScreen->itemStates[3] = 0xFF;
    titleScreen->itemStates[4] = 0xFF;
    titleScreen->itemStates[5] = 0xFF;

    *tmp2 = 0;

    cgdw = alloc_zero_8018DB4(0x8000, 1, tmp1, 0);
    dword_3000C84(dword_83A3D80, cgdw);
    CpuFastSet(cgdw, (void*)0x6000000, (sub_80198B0(dword_83A3D80) >> 2) & 0x1FFFFF);
    dword_3000C84(dword_83A4874, cgdw);
    CpuFastSet(cgdw, (void*)0x6004000, (sub_80198B0(dword_83A4874) >> 2) & 0x1FFFFF);
    CpuFastSet(dword_83A575C, (void*)0x600C000, 320);
    CpuFastSet(dword_83A5C5C, (void*)0x600D000, 1024);
    CpuFastSet(dword_83A6C5C, (void*)0x600C800, 312);
    free_heap_8018DA8(cgdw);
    sub_8020994(0, 0, 0, 0);

    for (i = 0; i < 9; i += 3) {
        sprites[i + 0] =
            sub_8020DD0(0, word_83A74C0[(i * 2) + 0], word_83A74C0[(i * 2) + 1], -1, -1, -1, -1);
        sub_801E150(sprites[i + 0], 0, -1, 0, 0);

        sprites[i + 1] =
            sub_8020DD0(0, word_83A74C0[(i * 2) + 2], word_83A74C0[(i * 2) + 3], -1, -1, -1, -1);
        sub_801E150(sprites[i + 1], 0, -1, 0, 0);

        sprites[i + 2] =
            sub_8020DD0(0, word_83A74C0[(i * 2) + 4], word_83A74C0[(i * 2) + 5], -1, -1, -1, -1);
        sub_801E150(sprites[i + 2], 0, -1, 0, 0);
    }

    if (selection == 0) {
        titleScreen->suitcaseX = 30720;
        titleScreen->suitcaseY = 0;
        titleScreen->suitcaseVelocityY = 512;
        sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 0, 0, 0, 0);
        titleScreen->sprites[TS_SPRITE_SUITCASE]->xPosition = 120;
        titleScreen->sprites[TS_SPRITE_SUITCASE]->yPosition = 0;
        titleScreen->sprites[TS_SPRITE_SUITCASE]->field_1F_0 = 0;
        titleScreen->sprites[TS_SPRITE_SUITCASE]->field_1F_2 = 1;
        titleScreen->sprites[TS_SPRITE_SUITCASE]->field_E = 2;
        sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SUITCASE]);
    } else {
        title_screen_prepare_game_select(titleScreen, selection);
    }

    dword_3000C78 = sub_800063C;

    (*(vu16*)(0x2000000 + 0x50)) = 191;
    (*(vu16*)(0x2000000 + 0x54)) = 16;
    (*(vu16*)(0x2000000 + 0x08)) = 6146;
    (*(vu16*)(0x2000000 + 0x0A)) = 23043;
    (*(vu16*)(0x2000000 + 0x0C)) = 22916;
    (*(vu16*)(0x2000000 + 0x10)) = 0;
    (*(vu16*)(0x2000000 + 0x12)) = 0;
    (*(vu16*)(0x2000000 + 0x14)) = 0;
    (*(vu16*)(0x2000000 + 0x16)) = 0;

    CpuFastSet(gGameState.gameBoyPlayerDetected == 0 ? dword_83A7300 : dword_83A7140,
               (void*)0x2000080, 112);

    (*(vu16*)(0x2000000 + 0x80)) = 0x7FFF;
    gGameState.field_2 = -1;
    gGameState.field_0 = -1;
    runtime_install_interrupt_callback(2, open_8056224);
    music_play(0, 41, MUSIC_VOLUME_UNCHANGED);

    if (selection == 0) {
        titleScreen->entryStateIdx = 0;
        (*(vu16*)(0x2000000 + 0x00)) |= 4673;
    } else {
        titleScreen->entryStateIdx = 2;
        (*(vu16*)(0x2000000 + 0x00)) |= 5953;
    }

    return titleScreen;
}
#endif

void title_screen_prepare_press_start(struct TitleScreen* titleScreen) {
    sprite_hide_8021F20(titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]);

    sub_801E150(titleScreen->sprites[TS_SPRITE_SS_TEXT], 0, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->xPosition = 121;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->yPosition = 80;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->xScale = 256;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->yScale = 256;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_1F_0 = 0;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_1F_2 = 0;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_E = 2;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SS_TEXT]);

    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 2, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_SUITCASE]->xPosition = 120;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->yPosition = 140;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_1F_0 = 0;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_1F_2 = 1;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_E = 2;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_4 = 1;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SUITCASE]);

    titleScreen->suitcaseX = 30720;
    titleScreen->suitcaseY = 35840;
    titleScreen->skipSuitcaseAnim = FALSE;

    BUFFER_REG_BG2HOFS = 0;
    BUFFER_REG_BG2VOFS = 0;
    BUFFER_REG_BG2PA = 256;
    BUFFER_REG_BG2PB = 0;
    BUFFER_REG_BG2PC = 0;
    BUFFER_REG_BG2PD = 256;
    BUFFER_REG_BG2X = 0;
    BUFFER_REG_BG2Y = 0;
    BUFFER_REG_BG0CNT = BGCNT_PRIORITY(2) | BGCNT_SCREENBASE(24);
    BUFFER_REG_BG0HOFS = 0;
    BUFFER_REG_BG0VOFS = 0;
    BUFFER_REG_DISPCNT |= DISPCNT_BG0_ON;

    titleScreen->titleLogoY = 0;
    titleScreen->titleLogoScaleX = 256;
    titleScreen->titleLogoScaleY = 256;
    titleScreen->itemStates[TS_ITEM_SUITCASE] = -1;
}

// https://decomp.me/scratch/WbD37
#ifndef NONMATCHING
asm_unified(".include \"asm/nonmatching/title_screen_prepare_game_select.s\"");
#else
void title_screen_prepare_game_select(struct TitleScreen* titleScreen, int selection) {
    s16 tmp;

    sprite_hide_8021F20(titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]);
    sprite_hide_8021F20(titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]);

    tmp = 100;
    sub_801E150(titleScreen->sprites[TS_SPRITE_ML_GAME_TEXT], 3, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_ML_GAME_TEXT]->xPosition = 180;
    titleScreen->sprites[TS_SPRITE_ML_GAME_TEXT]->yPosition = tmp;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_ML_GAME_TEXT]);

    tmp = 120;
    sub_801E150(titleScreen->sprites[TS_SPRITE_MB_GAME_TEXT], 4, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_MB_GAME_TEXT]->xPosition = 180;
    titleScreen->sprites[TS_SPRITE_MB_GAME_TEXT]->yPosition = tmp;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_MB_GAME_TEXT]);

    tmp = 140;
    sub_801E150(titleScreen->sprites[TS_SPRITE_OPTIONS_TEXT], 5, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_OPTIONS_TEXT]->xPosition = 180;
    titleScreen->sprites[TS_SPRITE_OPTIONS_TEXT]->yPosition = tmp;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_OPTIONS_TEXT]);

    sub_801E150(titleScreen->sprites[TS_SPRITE_BEAN_POINTER], 13, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->xPosition = 112;
    titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->yPosition = 92 + 20 * titleScreen->selection;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_BEAN_POINTER]);

    sub_801E150(titleScreen->sprites[TS_SPRITE_SS_TEXT], 0, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->xPosition = 121;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->yPosition = 80;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->xScale = 256;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->yScale = 256;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_1F_0 = 0;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_1F_2 = 0;
    titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_E = 2;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SS_TEXT]);

    tmp = 140;
    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 4, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_SUITCASE]->xPosition = 64;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->yPosition = tmp;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_1F_0 = 0;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_1F_2 = 1;
    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_E = 2;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SUITCASE]);

    tmp = 140;
    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL], 3 * (selection - 1) + 1, 0, 0, 0);
    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->xPosition = 64;
    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->yPosition = tmp;
    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->field_1F_0 = 1;
    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->field_E = 1;
    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]);

    titleScreen->suitcaseVisualState = 1;

    off_839EC80[0x01] |= 0x20;
    off_839EC80[0x40] = 0xF0;
    off_839EC80[0x41] = 0x00;
    off_839EC80[0x44] = 0xA0;
    off_839EC80[0x45] = 0x90;

    off_839EC80[0x48] |= 1;
    off_839EC80[0x48] |= 2;
    off_839EC80[0x48] |= 4;
    off_839EC80[0x48] |= 8;
    *(s8*)&off_839EC80[0x48] &= 0xEF;
    off_839EC80[0x48] |= 0x20;

    off_839EC80[0x4A] |= 1;
    off_839EC80[0x4A] |= 2;
    off_839EC80[0x4A] |= 4;
    off_839EC80[0x4A] |= 8;
    off_839EC80[0x4A] |= 0x10;
    off_839EC80[0x4A] |= 0x20;

    (*(vu16*)(0x2000000 + 0x18)) = 0;
    (*(vu16*)(0x2000000 + 0x1A)) = 0;
    (*(vu16*)(0x2000000 + 0x20)) = 256;
    (*(vu16*)(0x2000000 + 0x22)) = 0;
    (*(vu16*)(0x2000000 + 0x24)) = 0;
    (*(vu16*)(0x2000000 + 0x26)) = 256;
    (*(vu32*)(0x2000000 + 0x28)) = 0;
    (*(vu32*)(0x2000000 + 0x2C)) = 0;

    titleScreen->titleLogoY = 0;
    titleScreen->titleLogoScaleX = 256;
    titleScreen->titleLogoScaleY = 256;

    multiplayer_serial_enable();
}
#endif

void title_screen_scanline_effect_update(void)
{
  u16 *dst;
  s32 i;
  u8 j;
  const u8 *table;
  s32 value;
  u16 out;
  u8 limit;
  dword_3000DA0->field_0[0] -= 0x40;
  dword_3000DA0->field_0[1] -= 0x80;
  dword_3000DA0->field_0[2] -= 0x40;
  dword_3000DA0->field_0[3] -= 0x20;
  j = 0;
  dst = &dword_3000DA0->field_14;
  i = 0;
  table = dword_83A74E4;
  do
  {
    value = dword_3000DA0->field_0[i];
    if (value < 0)
    {
      value += 0xFF;
    }
    value <<= 8;
    out = ((u32) value) >> 16;
    limit = *(const u8 *)((u32)i + (u32)table);
    while (j <= limit)
    {
      *dst = out;
      j = (u8) (j + 1);
      dst++;
    }

    i += 1;
  }
  while (i <= 4);
  {
    vu16 *bg = (vu16 *) 0x04000014;
    struct ORSTData *data = dword_3000DA0;
    vu32 *dma;
    *bg = data->field_14;
    dma = (vu32 *) 0x040000B0;
    *((vu16 *) 0x040000BA) = 0;
    dma[0] = (u32) (&data->field_16);
    dma[1] = (u32) bg;
    dma[2] = 0xA2400001;
  }
}
void title_screen_update(struct TitleScreen* titleScreen) {
    int i, j;

    sub_8021F7C();

    switch (titleScreen->process.state) {
        case TS_STATE_FADE_IN:
            titleScreen->brightness--;
            BUFFER_REG_BLDY = titleScreen->brightness;
            if (titleScreen->brightness == 0) {
                titleScreen->process.state = byte_83A74E9[titleScreen->entryStateIdx];
                if (titleScreen->process.state == TS_STATE_PRESS_START_SHOW) {
                    titleScreen->brightness = 60;
                }
            }
            break;

        case TS_STATE_TITLE_ANIMATION:
            for (i = 0; i < TS_ITEM_COUNT; i++) {
                if (titleScreen->itemStates[i] < 0) {
                    continue;
                }

                switch (i) {
                    case TS_ITEM_SUITCASE:
                        switch (titleScreen->itemStates[TS_ITEM_SUITCASE]) {
                            case TS_ITEM_SC_STATE_FALLING:
                                titleScreen->suitcaseY += titleScreen->suitcaseVelocityY;
                                titleScreen->suitcaseVelocityY += 32;
                                if (titleScreen->suitcaseY > 35839) {
                                    titleScreen->suitcaseY = 35840;
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 1, 0, 0, 0);
                                    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_1 = 1;
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_HIT_GROUND;
                                }
                                break;

                            case TS_ITEM_SC_STATE_HIT_GROUND:
                                if (titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_3) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 2, 0, 0, 0);
                                    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_1 = 1;
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_FALL_OVER;
                                }
                                break;

                            case TS_ITEM_SC_STATE_FALL_OVER:
                                if (titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_3) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 3, 0, 0, 0);
                                    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_1 = 1;
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_OPEN;
                                }
                                break;

                            case TS_ITEM_SC_STATE_OPEN:
                                if (titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_3) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 4, 0, 0, 0);
                                    BUFFER_REG_DISPCNT |= DISPCNT_BG2_ON;
                                    titleScreen->titleLogoProgress = 2560;
                                    titleScreen->titleLogoY = 37120;
                                    titleScreen->titleLogoScaleX = 51;
                                    titleScreen->titleLogoScaleY = 51;
                                    titleScreen->titleLogoAffineSource.texX = 30720;
                                    titleScreen->titleLogoAffineSource.texY = 0x4000;
                                    titleScreen->titleLogoAffineSource.scrX = 120;
                                    titleScreen->titleLogoAffineSource.scrY = 64;
                                    titleScreen->titleLogoAffineSource.sx = 256;
                                    titleScreen->titleLogoAffineSource.sy = 256;
                                    titleScreen->titleLogoAffineSource.alpha = 0;
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_OPEN_WAIT;
                                    titleScreen->itemStates[TS_ITEM_ML_LOGO] = 0;
                                    titleScreen->animationTimer = 0;
                                }
                                break;

                            case TS_ITEM_SC_STATE_OPEN_WAIT:
                                if (titleScreen->animationTimer < 0xFFFF) {
                                    switch (titleScreen->animationTimer) {
                                        case 32:
                                            titleScreen->subtitleProgress = 2470;
                                            titleScreen->subtitleY = 37376;
                                            titleScreen->subtitleScaleX = 51;
                                            titleScreen->subtitleScaleY = 51;
                                            sub_801E150(titleScreen->sprites[TS_SPRITE_SS_TEXT], 0, 0, 0, 0);
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->xPosition = 121;
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->yPosition = 146;
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->xScale = 51;
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->yScale = 51;
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_1F_0 = 1;
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_1F_2 = 1;
                                            titleScreen->sprites[TS_SPRITE_SS_TEXT]->field_E = 0;
                                            sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SS_TEXT]);
                                            titleScreen->itemStates[TS_ITEM_SS_TEXT] = 0;
                                            break;

                                        case 64:
                                            titleScreen->licenseTextProgress = 1945;
                                            titleScreen->licenseTextY = 36608;
                                            titleScreen->licenseTextScaleX = 51;
                                            titleScreen->licenseTextScaleY = 51;
                                            sub_801E150(titleScreen->sprites[TS_SPRITE_LICENSE_TEXT], 0, 0, 0,
                                                        0);
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->xPosition = 118;
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->yPosition = 143;
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->xScale = 51;
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->yScale = 51;
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->field_1F_0 = 1;
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->field_1F_2 = 1;
                                            titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->field_E = 0;
                                            sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]);
                                            titleScreen->itemStates[TS_ITEM_LICENSE_TEXT] = 0;
                                            break;
                                    }
                                    titleScreen->animationTimer++;
                                }
                                break;

                            case TS_ITEM_SC_STATE_CLOSE:
                                if (titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_3) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 2, 0, 0, 0);
                                    titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_4 = 1;
                                    sprite_hide_8021F20(titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]);
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = -1;
                                    BUFFER_REG_BG0CNT = BGCNT_PRIORITY(2) | BGCNT_SCREENBASE(24);
                                    BUFFER_REG_BG0HOFS = 0;
                                    BUFFER_REG_BG0VOFS = 0;
                                    BUFFER_REG_DISPCNT |= DISPCNT_BG0_ON;
                                    if (!titleScreen->isSkippingSuitcaseAnim) {
                                        titleScreen->brightness = 60;
                                        titleScreen->process.state = TS_STATE_PRESS_START_SHOW;
                                    }
                                }
                                break;
                        }
                        titleScreen->sprites[TS_SPRITE_SUITCASE]->xPosition = titleScreen->suitcaseX / 256;
                        titleScreen->sprites[TS_SPRITE_SUITCASE]->yPosition = titleScreen->suitcaseY / 256;
                        break;

                    case TS_ITEM_ML_LOGO:
                        switch (titleScreen->itemStates[TS_ITEM_ML_LOGO]) {
                            case 0:
                                titleScreen->titleLogoProgress -= 98;
                                titleScreen->titleLogoY -= titleScreen->titleLogoProgress;
                                titleScreen->titleLogoScaleX += 5;
                                titleScreen->titleLogoScaleY = titleScreen->titleLogoScaleX;
                                if (titleScreen->titleLogoScaleX > 255) {
                                    BUFFER_REG_BG2CNT = BGCNT_PRIORITY(1) | BGCNT_CHARBASE(1)
                                                        | BGCNT_256COLOR | BGCNT_SCREENBASE(25)
                                                        | BGCNT_AFF256x256;
                                    titleScreen->titleLogoScaleX = 256;
                                    titleScreen->itemStates[TS_ITEM_ML_LOGO] = 1;
                                    titleScreen->titleLogoProgress = 0;
                                }
                                break;

                            case 1:
                                titleScreen->titleLogoScaleX = word_83A74EC[2 * titleScreen->titleLogoProgress];
                                titleScreen->titleLogoScaleY = word_83A74EC[2 * titleScreen->titleLogoProgress + 1];
                                titleScreen->titleLogoProgress++;
                                // Is the cast really necessary here?
                                if ((u16)titleScreen->titleLogoProgress == 17) {
                                    titleScreen->itemStates[TS_ITEM_ML_LOGO] = -1;
                                }
                                break;
                        }
                        titleScreen->titleLogoAffineSource.sx =
                            (dword_3001038 + (&loc_819832C - &loc_8198220))(0x10000, titleScreen->titleLogoScaleX);
                        titleScreen->titleLogoAffineSource.sy =
                            (dword_3001038 + (&loc_819832C - &loc_8198220))(0x10000, titleScreen->titleLogoScaleY);
                        titleScreen->titleLogoAffineSource.scrY = titleScreen->titleLogoY / 256;
                        BgAffineSet(&titleScreen->titleLogoAffineSource, &titleScreen->titleLogoAffineDestination, 1);
                        BUFFER_REG_BG2PA = titleScreen->titleLogoAffineDestination.pa;
                        BUFFER_REG_BG2PB = titleScreen->titleLogoAffineDestination.pb;
                        BUFFER_REG_BG2PC = titleScreen->titleLogoAffineDestination.pc;
                        BUFFER_REG_BG2PD = titleScreen->titleLogoAffineDestination.pd;
                        BUFFER_REG_BG2X = titleScreen->titleLogoAffineDestination.dx;
                        BUFFER_REG_BG2Y = titleScreen->titleLogoAffineDestination.dy;
                        break;

                    case TS_ITEM_SS_TEXT:
                        switch (titleScreen->itemStates[TS_ITEM_SS_TEXT]) {
                            case 0:
                                titleScreen->subtitleProgress -= 98;
                                titleScreen->subtitleY -= titleScreen->subtitleProgress;
                                titleScreen->subtitleScaleX += 5;
                                titleScreen->subtitleScaleY = titleScreen->subtitleScaleX;
                                if (titleScreen->subtitleScaleX > 255) {
                                    titleScreen->subtitleScaleX = 256;
                                    titleScreen->itemStates[TS_ITEM_SS_TEXT] = 1;
                                    titleScreen->subtitleProgress = 0;
                                }
                                break;

                            case 1:
                                titleScreen->subtitleScaleX = word_83A7530[2 * titleScreen->subtitleProgress];
                                titleScreen->subtitleScaleY = word_83A7530[2 * titleScreen->subtitleProgress + 1];
                                titleScreen->subtitleProgress++;
                                if ((u16)titleScreen->subtitleProgress == 17) {
                                    titleScreen->itemStates[TS_ITEM_SS_TEXT] = -1;
                                }
                                break;
                        }
                        titleScreen->sprites[TS_SPRITE_SS_TEXT]->yPosition = titleScreen->subtitleY / 256;
                        titleScreen->sprites[TS_SPRITE_SS_TEXT]->xScale = titleScreen->subtitleScaleX;
                        titleScreen->sprites[TS_SPRITE_SS_TEXT]->yScale = titleScreen->subtitleScaleY;
                        break;

                    case TS_ITEM_LICENSE_TEXT:
                        switch (titleScreen->itemStates[TS_ITEM_LICENSE_TEXT]) {
                            case 0:
                                titleScreen->licenseTextProgress -= 98;
                                if (titleScreen->licenseTextProgress < 0) {
                                    titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->field_1F_0 =
                                        titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->field_1F_2 = 0;
                                }
                                titleScreen->licenseTextY -= titleScreen->licenseTextProgress;
                                titleScreen->licenseTextScaleX += 5;
                                titleScreen->licenseTextScaleY = titleScreen->licenseTextScaleX;
                                if (titleScreen->licenseTextScaleX > 255) {
                                    titleScreen->licenseTextScaleX = 256;
                                    titleScreen->itemStates[TS_ITEM_LICENSE_TEXT] = 1;
                                    titleScreen->licenseTextProgress = 0;
                                }
                                break;

                            case 1:
                                titleScreen->licenseTextScaleX = word_83A7574[2 * titleScreen->licenseTextProgress];
                                titleScreen->licenseTextScaleY = word_83A7574[2 * titleScreen->licenseTextProgress + 1];
                                titleScreen->licenseTextProgress++;
                                if ((u16)titleScreen->licenseTextProgress == 17) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 5, 0, 0, 0);
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_CLOSE;
                                    titleScreen->skipSuitcaseAnim = FALSE;
                                    titleScreen->itemStates[TS_ITEM_LICENSE_TEXT] = -1;
                                }
                                break;
                        }
                        titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->yPosition = titleScreen->licenseTextY / 256;
                        titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->xScale = titleScreen->licenseTextScaleX;
                        titleScreen->sprites[TS_SPRITE_LICENSE_TEXT]->yScale = titleScreen->licenseTextScaleY;
                        break;
                }
            }

            if (!titleScreen->isSkippingSuitcaseAnim) {
                if (titleScreen->skipSuitcaseAnim
                    && gGameState.field_2A & (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON)) {
                    titleScreen->isSkippingSuitcaseAnim = TRUE;
                    titleScreen->brightness = 16;
                }
            } else {
                titleScreen->brightness--;
                BUFFER_REG_BLDY = 16 - titleScreen->brightness;
                if (titleScreen->brightness == 0) {
                    titleScreen->process.state = TS_STATE_FADE_IN;
                    titleScreen->entryStateIdx = 1;
                    titleScreen->brightness = 16;
                    title_screen_prepare_press_start(titleScreen);
                    BUFFER_REG_DISPCNT |= DISPCNT_MODE_1 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON
                                          | DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON;
                }
            }
            break;

        case TS_STATE_PRESS_START_SHOW:
            titleScreen->brightness--;
            if (titleScreen->brightness == 0) {
                titleScreen->pressStartY = 30720;
                sub_801E150(titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT], 0, 0, 0, 0);
                titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]->xPosition = 120;
                titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]->yPosition = 120;
                titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]->field_1F_0 = 0;
                titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]->field_1F_2 = 0;
                titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]->field_E = 0;
                sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]);
                titleScreen->process.state = TS_STATE_PRESS_START_WAIT;
            }
            break;

        case TS_STATE_PRESS_START_WAIT:
            if (gGameState.field_2A & (A_BUTTON | START_BUTTON)) {
                titleScreen->pressStartVelocity = 0;
                titleScreen->itemStates[TS_ITEM_PRESS_START_TEXT] = 2;
                titleScreen->suitcaseVelocityX = 0;
                titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_MOVE_LEFT;
                sound_effect_play(96, SOUND_VOLUME_UNCHANGED);
                titleScreen->process.state = TS_STATE_SUITCASE_OPENS;
            }
            break;

        case TS_STATE_SUITCASE_OPENS:
            for (j = 0; j < TS_ITEM_COUNT; j++) {
                if (titleScreen->itemStates[j] < 0) {
                    continue;
                }

                switch (j) {
                    case TS_ITEM_SUITCASE:
                        switch (titleScreen->itemStates[TS_ITEM_SUITCASE]) {
                            case TS_ITEM_SC_STATE_MOVE_LEFT:
                                titleScreen->suitcaseVelocityX -= 102;
                                titleScreen->suitcaseX += titleScreen->suitcaseVelocityX;
                                if (titleScreen->suitcaseX <= 0x2000) {
                                    titleScreen->suitcaseX = 0x4000;
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 6, 0, 0, 0);
                                    titleScreen->animationTimer = 0;
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = TS_ITEM_SC_STATE_BUMP_OPEN;
                                }
                                break;

                            case TS_ITEM_SC_STATE_BUMP_OPEN:
                                if (titleScreen->sprites[TS_SPRITE_SUITCASE]->field_12_3) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE], 4, 0, 0, 0);
                                    titleScreen->itemStates[TS_ITEM_SUITCASE] = -1;
                                }

                                if (titleScreen->animationTimer < 0xFFFF) {
                                    if (titleScreen->animationTimer == 15) {
                                        titleScreen->selectionPointerX = 0x4000;
                                        titleScreen->selectionPointerY = 33280;
                                        titleScreen->selectionPointerVelocityX = 384;
                                        titleScreen->selectionPointerVelocityY = 1536;
                                        sub_801E150(titleScreen->sprites[TS_SPRITE_BEAN_POINTER], 11, 0, 0, 0);
                                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->xPosition = 64;
                                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->yPosition = 130;
                                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->field_1F_0 = 0;
                                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->field_1F_2 = 0;
                                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->field_E = 0;
                                        sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_BEAN_POINTER]);
                                        titleScreen->itemStates[TS_ITEM_POINTER] = 0;
                                    }
                                    titleScreen->animationTimer++;
                                }
                                break;
                        }
                        titleScreen->sprites[TS_SPRITE_SUITCASE]->xPosition = titleScreen->suitcaseX / 256;
                        titleScreen->sprites[TS_SPRITE_SUITCASE]->yPosition = titleScreen->suitcaseY / 256;
                        break;

                    case TS_ITEM_PRESS_START_TEXT:
                        if (titleScreen->itemStates[TS_ITEM_PRESS_START_TEXT] == 2) {
                            titleScreen->pressStartVelocity -= 98;
                            titleScreen->pressStartY -= titleScreen->pressStartVelocity;
                            if (titleScreen->pressStartY > 45055) {
                                sprite_hide_8021F20(titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]);
                                titleScreen->itemStates[TS_ITEM_PRESS_START_TEXT] = -1;
                            }
                        }
                        titleScreen->sprites[TS_SPRITE_PRESS_START_TEXT]->yPosition = titleScreen->pressStartY / 256;
                        break;

                    case TS_ITEM_POINTER:
                        switch (titleScreen->itemStates[TS_ITEM_POINTER]) {
                            case 0:
                                titleScreen->selectionPointerVelocityY -= 98;
                                titleScreen->selectionPointerY -= titleScreen->selectionPointerVelocityY;
                                titleScreen->selectionPointerX += titleScreen->selectionPointerVelocityX;
                                if (titleScreen->selectionPointerVelocityY < 0 && titleScreen->selectionPointerY > 35839) {
                                    titleScreen->selectionPointerY = 35840;
                                    titleScreen->spriteIdx = 2;
                                    titleScreen->itemStates[TS_ITEM_POINTER] = 1;
                                }
                                break;

                            case 1:
                                if (titleScreen->selectionPointerY / 256 <= 20 * titleScreen->spriteIdx + 92) {
                                    sub_801E150(titleScreen->sprites[titleScreen->spriteIdx + 2], titleScreen->spriteIdx + 3, 0, 0,
                                                0);
                                    titleScreen->sprites[titleScreen->spriteIdx + 2]->xPosition = 180;
                                    titleScreen->sprites[titleScreen->spriteIdx + 2]->yPosition =
                                        20 * titleScreen->spriteIdx + 100;
                                    sprite_show_8020CBC(titleScreen->sprites[titleScreen->spriteIdx + 2]);

                                    if (titleScreen->spriteIdx == 0) {
                                        sub_801E150(titleScreen->sprites[TS_SPRITE_BEAN_POINTER], 12, 0, 0, 0);
                                        titleScreen->itemStates[TS_ITEM_POINTER] = 2;
                                    } else {
                                        titleScreen->spriteIdx--;
                                    }
                                }

                                if (titleScreen->itemStates[TS_ITEM_POINTER] == 1) {
                                    titleScreen->selectionPointerY -= 1536;
                                }
                                break;

                            case 2:
                                if (titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->field_12_3) {
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_BEAN_POINTER], 13, 0, 0, 0);
                                    sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL], 0, 0, 0, 0);
                                    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->xPosition = 64;
                                    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->yPosition = 140;
                                    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->field_1F_0 = 1;
                                    titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->field_E = 1;
                                    sprite_show_8020CBC(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]);
                                    titleScreen->suitcaseVisualState = TS_SV_STATE_APPEAR;

                                    off_839EC80[REG_OFFSET_DISPCNT + 1] |= DISPCNT_WIN0_ON >> 8;
                                    off_839EC80[REG_OFFSET_WIN0H] = 240;
                                    off_839EC80[REG_OFFSET_WIN0H + 1] = 0;
                                    off_839EC80[REG_OFFSET_WIN0V] = 160;
                                    off_839EC80[REG_OFFSET_WIN0V + 1] = 144;
                                    off_839EC80[REG_OFFSET_WININ] |= WININ_WIN0_BG0;
                                    off_839EC80[REG_OFFSET_WININ] |= WININ_WIN0_BG1;
                                    off_839EC80[REG_OFFSET_WININ] |= WININ_WIN0_BG2;
                                    off_839EC80[REG_OFFSET_WININ] |= WININ_WIN0_BG3;
                                    *(s8*)&off_839EC80[REG_OFFSET_WININ] &= ~WININ_WIN0_OBJ;
                                    off_839EC80[REG_OFFSET_WININ] |= WININ_WIN0_CLR;
                                    off_839EC80[REG_OFFSET_WINOUT] |= WINOUT_WIN01_BG0;
                                    off_839EC80[REG_OFFSET_WINOUT] |= WINOUT_WIN01_BG1;
                                    off_839EC80[REG_OFFSET_WINOUT] |= WINOUT_WIN01_BG2;
                                    off_839EC80[REG_OFFSET_WINOUT] |= WINOUT_WIN01_BG3;
                                    off_839EC80[REG_OFFSET_WINOUT] |= WINOUT_WIN01_OBJ;
                                    off_839EC80[REG_OFFSET_WINOUT] |= WINOUT_WIN01_CLR;

                                    multiplayer_serial_enable();
                                    titleScreen->process.state = TS_STATE_GAME_SELECT;
                                }
                                break;
                        }
                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->xPosition = titleScreen->selectionPointerX / 256;
                        titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->yPosition = titleScreen->selectionPointerY / 256;
                        break;
                }
            }
            break;

        case TS_STATE_GAME_SELECT:
            if (gGameState.field_2A & (A_BUTTON | START_BUTTON)) {
                BUFFER_REG_BLDCNT = BLDCNT_TGT1_ALL | BLDCNT_EFFECT_LIGHTEN;
                BUFFER_REG_BLDY = 0;
                titleScreen->brightness = 16;
                sound_effect_play(96, SOUND_VOLUME_UNCHANGED);
                music_set_volume(0, 0, 16);
                titleScreen->process.state = TS_STATE_FADE_OUT;
            } else {
                s8 selection = titleScreen->selection;
                if (gGameState.field_2E & DPAD_UP) {
                    titleScreen->selection--;
                    if (titleScreen->selection < 0) {
                        titleScreen->selection = 2;
                    }
                    sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                } else if (gGameState.field_2E & DPAD_DOWN) {
                    titleScreen->selection++;
                    if (titleScreen->selection > 2) {
                        titleScreen->selection = 0;
                    }
                    sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                }

                if (titleScreen->selection != selection) {
                    if (titleScreen->suitcaseVisualState != TS_SV_STATE_DISAPPEAR) {
                        sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL], 3 * selection + 2, 0, 0, 0);
                    }
                    titleScreen->suitcaseVisualState = TS_SV_STATE_DISAPPEAR;
                    titleScreen->sprites[TS_SPRITE_BEAN_POINTER]->yPosition = 20 * titleScreen->selection + 92;
                }
            }
            break;

        case TS_STATE_FADE_OUT:
            titleScreen->brightness--;
            BUFFER_REG_BLDY = 16 - titleScreen->brightness;
            if (titleScreen->brightness != 0) {
                break;
            }

            if (titleScreen != NULL) {
                titleScreen->process.definition = &gTitleScreenProcessDefinition;
                DmaStop(0);
                runtime_install_interrupt_callback(2, 0);

                if (titleScreen->scoreDisplay) {
                    process_remove(&titleScreen->scoreDisplay->process, 3);
                }

                free_heap_8018DA8(dword_3000DA0);
                sub_8021FD4();
                // Turn on sound.
                BUFFER_REG_SOUNDCNT_L = 0x7FFF;
                gGameState.field_2 |= 1;
                BUFFER_REG_DISPCNT = 0;
                gGameState.field_31 = 2;
                sub_8017E34();
                process_remove(&titleScreen->process, 3);
            }

            switch (titleScreen->selection) {
                case 0:
                    multiplayer_serial_disable();
                    sub_801AFE4(0);
                    BUFFER_REG_BLDCNT = 0;
                    //! Change this when other function is matching too.
                    load_init_812538C(alloc_Zero(356, 0, (char*)0x081E2784 /*"LOAD"*/, 0), 8,
                                (char*)0x081E2784 /*"LOAD"*/, 0xFFFF);
                    return;

                case 1:
                    gTitleSaveSummary.titleState = 1;
                    BUFFER_REG_BLDCNT = 0;
                    sub_81DA6C8(64);
                    return;

                case 2:
                    multiplayer_serial_disable();
                    //! Change this when other function is matching too.
                    options_screen_create(alloc_Zero(84, 0, (char*)0x081E278C /*"OPTN"*/, 0), 8,
                              (char*)0x081E278C /*"OPTN"*/, 0);
                    return;

                default:
                    return;
            }
            break;
    }

    switch (titleScreen->suitcaseVisualState) {
        case TS_SV_STATE_APPEAR:
            if (titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->field_12_3) {
                sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL], 3 * titleScreen->selection + 1, 0, 0, 0);
                titleScreen->suitcaseVisualState = TS_SV_STATE_IDLE;
            }
            break;

        case TS_SV_STATE_DISAPPEAR:
            if (titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL]->field_12_3) {
                sub_801E150(titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL], 3 * titleScreen->selection, 0, 0, 0);
                titleScreen->suitcaseVisualState = TS_SV_STATE_APPEAR;
            }
            break;
    }
}

// https://decomp.me/scratch/3i7ME
#ifndef NONMATCHING
asm_unified(".include \"asm/nonmatching/title_screen_score_display_update.s\"");
#else
void title_screen_score_display_update(struct TitleScreenScoreDisplay* display) {
    struct TitleScreen* titleScreen;
    int var1;
    struct Sprite* sprite;
    u16 var2;

    titleScreen = (struct TitleScreen*)display->process.parentProcess;
    sub_8020A78();
    var1 = gGameState.field_880;
    sprite = titleScreen->sprites[TS_SPRITE_SUITCASE_VISUAL];

    if ((u8)(sprite->field_20[1] - 3) <= 2) {
        u32 i;
        struct struc_11* var11;

        var11 = stru_203FFB8.field_38;
        var2 = word_83A75B8[sprite->field_22 - 10] - 34;

        for (i = 0; i < 6; i += 3) {
            var11->field_0 = var2;
            var11->field_2 = 43 + (i * 7);
            var11->field_4 = (display->topScore[i] + 44) | 0x2400;
            var11->field_6 = 0;
            var11->field_8 = 0x40000000;
            var11 = var11->field_10;

            var11->field_0 = var2;
            var11->field_2 = 50 + (i * 7);
            var11->field_4 = (display->topScore[i + 1] + 44) | 0x2400;
            var11->field_6 = 0;
            var11->field_8 = 0x40000000;
            var11 = var11->field_10;

            var11->field_0 = var2;
            var11->field_2 = 57 + (i * 7);
            var11->field_4 = (display->topScore[i + 1] + 44) | 0x2400;
            var11->field_6 = 0;
            var11->field_8 = 0x40000000;
            var11 = var11->field_10;
        }

        var2 = word_83A75C8[sprite->field_22 - 10] - 21;

        var11->field_0 = var2;
        var11->field_2 = 64;
        var11->field_4 = (display->playerScore[0] + 44) | 0x2400;
        var11->field_6 = 0;
        var11->field_8 = 0x40000000;
        var11 = var11->field_10;

        var11->field_0 = var2;
        var11->field_2 = 71;
        var11->field_4 = (display->playerScore[1] + 44) | 0x2400;
        var11->field_6 = 0;
        var11->field_8 = 0x40000000;
        var11 = var11->field_10;

        stru_203FFB8.field_38 = var11;
    }

    dword_3000D48(stru_203FFB8.field_3C, stru_203FFB8.field_3C + 2580);
    gGameState.field_880 = dword_3000D4C(stru_203FFB8.field_3C, var1);
}
#endif

static inline char* write_number_to_string_and_advance(char* string, u32* value) {
    *string = *value % 10;
    *value /= 10;
    return string - 1;
}

/**
 * Initialises the process for the Mario Bros Score visual on the title screen.
 */
struct TitleScreenScoreDisplay* title_screen_score_display_create(
    struct TitleScreenScoreDisplay* display, u8 priority, char* label, u32 topScore,
    u8 playerScore) {
    char* topScoreStr;
    char* playerScoreTens;
    char* playerScoreOnes;

    process_add(&display->process, priority, label);
    display->process.definition = &gTitleScreenScoreDisplayProcessDefinition;

    topScoreStr = &display->topScore[5];
    topScoreStr = write_number_to_string_and_advance(topScoreStr, &topScore);
    topScoreStr = write_number_to_string_and_advance(topScoreStr, &topScore);
    topScoreStr = write_number_to_string_and_advance(topScoreStr, &topScore);
    topScoreStr = write_number_to_string_and_advance(topScoreStr, &topScore);
    topScoreStr = write_number_to_string_and_advance(topScoreStr, &topScore);
    topScoreStr = write_number_to_string_and_advance(topScoreStr, &topScore);

    playerScoreTens = &display->playerScore[0];
    playerScoreOnes = &display->playerScore[1];
    *playerScoreOnes = playerScore % 10;
    playerScore /= 10;
    *playerScoreTens = playerScore % 10;

    return display;
}

//! The contents of this function is also found in title_screen_update.
void title_screen_destroy(struct TitleScreen* titleScreen, int flags) {
    titleScreen->process.definition = &gTitleScreenProcessDefinition;
    DmaStop(0);
    runtime_install_interrupt_callback(2, 0);

    if (titleScreen->scoreDisplay) {
        process_remove(&titleScreen->scoreDisplay->process, 3);
    }

    free_heap_8018DA8(dword_3000DA0);
    sub_8021FD4();
    BUFFER_REG_SOUNDCNT_L = 0x7FFF;
    gGameState.field_2 |= 1;
    BUFFER_REG_DISPCNT = 0;
    gGameState.field_31 = 2;
    sub_8017E34();
    process_remove(&titleScreen->process, flags);
}

//! The contents of this function is also found in title_screen_score_display_update.
void screen_render_process_update(void) {
    int var1 = gGameState.field_880;
    sub_8020A78();
    dword_3000D48(stru_203FFB8.field_3C, stru_203FFB8.field_3C + 2580);
    var1 = dword_3000D4C(stru_203FFB8.field_3C, var1);
    gGameState.field_880 = var1;
}

//! The contents of this function is also found in company_intro_update.
void company_intro_destroy(struct CompanyIntro* intro, int flags) {
    intro->process.definition = &gCompanyIntroProcessDefinition;
    sub_8021FD4();
    if (intro->renderProcess) {
        process_remove(intro->renderProcess, 3);
    }
    process_remove(&intro->process, flags);
}

struct Process* screen_render_process_create(struct Process* process, u8 priority, char* label) {
    process_add(process, priority, label);
    process->definition = &gScreenRenderProcessDefinition;
    return process;
}
