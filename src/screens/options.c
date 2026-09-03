#include "global.h"
#include "audio/music.h"
#include "audio/sound_effects.h"
#include "common.h"
#include "process/process.h"
#include "screens/title_screen.h"
#include "screens/options.h"

#ifndef NONMATCHING
asm_unified(".include \"asm/nonmatching/window_animation_prepare.s\"");
#endif

void window_animation_update(struct WindowAnimation* animation)
{
    u8 xOff, yOff;
    s32 xSize;
    s32 ySize;
    s32 xySize;

    if (animation->progress == 0)
        return;

    xSize = animation->width * animation->progress;
    if (xSize < 0)
        xSize += 0xF;
    xOff = xSize >> 4;

    ySize = animation->height * animation->progress;
    if (ySize < 0)
        ySize += 0xF;
    yOff = ySize >> 4;

    {
        u8 *ptr = *(u8**)0x0839EC80;
        ySize = (animation->width >> 1) + animation->centerX;
        xySize = xOff + ySize;
        ptr += 0x40;
        *ptr = xySize;
    }

    {
        u8 *ptr = *(u8**)0x0839EC80;
        xSize = (animation->width >> 1) + animation->centerX;
        xSize = xSize - xOff;
        ptr += 0x41;
        *ptr = xSize;
    }

    {
        u8 *ptr = *(u8**)0x0839EC80;
        xSize = (animation->height >> 1) + animation->centerY;
        ySize = yOff + xSize;
        ptr += 0x44;
        *ptr = ySize;
    }

    {
        u8 *ptr = *(u8**)0x0839EC80;
        xSize = (animation->height >> 1) + animation->centerY;
        xSize = xSize - yOff;
        ptr += 0x45;
        *ptr = xSize;
    }

    if (!animation->isClosing) {
        if (animation->progress == 8) {
            (*(s8**)0x0839EC80)[1] &= 0xDF;
            animation->progress = 0;
        } else {
            animation->progress++;
        }
    } else {
        if (--animation->progress == 0) {
            (*(s8**)0x0839EC80)[1] &= 0xDF;
            *(vu16*)0x02000000 &= 0xFDFF;
        }
    }
}

// https://decomp.me/scratch/PDUDz
#ifndef NONMATCHING
asm_unified(".include \"asm/nonmatching/options_screen_create.s\"");
#else
struct OptionsScreen* options_screen_create(
    struct OptionsScreen* optionsScreen, u8 priority, char* label, int entryArgument) {
    struct Process* renderProcess;
    u16* graphicsBuffer;
    u16* v10;
    int v11;

    u16* v21;
    int v22;

    volatile int v31;

    process_add(&optionsScreen->process, priority, label);
    optionsScreen->process.definition = &gOptionsScreenProcessDefinition;

    (*(vu16*)(0x2000000 + 0x50)) = 191;
    (*(vu16*)(0x2000000 + 0x54)) = 16;
    (*(vu16*)(0x2000000 + 0x00)) = 0;

    sub_8017E34();

    gGameState.field_31 = 8;
    optionsScreen->entryArgument = entryArgument;

    sub_801A548();

    renderProcess = (struct Process*)alloc_Zero(0x1C, 0, "ODTR", 0);
    process_add(renderProcess, 8, "ODTR");
    renderProcess->definition = &gOptionsScreenRenderProcessDefinition;
    optionsScreen->renderProcess = renderProcess;
    renderProcess->parentProcess = &optionsScreen->process;

    optionsScreen->selectedOption = 0;
    optionsScreen->fadeTimer = 16;
    optionsScreen->windowAnimationTilemap = alloc_zero_8018DB4(2048, 1, "WINW", 0);
    optionsScreen->pendingSettings =
        gGameState.field_88A_4 | gGameState.field_88B_0 << 1 | dword_3000FFC->field_8_5 << 2;
    optionsScreen->inputCooldown = 0;

    dword_3001034(0, (void*)&optionsScreen->dialogWindow, 8);
    graphicsBuffer = alloc_zero_8018DB4(0x8000, 1, "CGDW", 0);
    dword_3000C84(dword_83A0E94, graphicsBuffer);
    CpuFastSet(
        graphicsBuffer,
        (void*)0x6000000,
        (sub_80198B0(dword_83A0E94) >> 2) & 0x1FFFFF);
    dword_3000C84(dword_83A1F60, graphicsBuffer);
    CpuFastSet(
        graphicsBuffer,
        (void*)0x6010000,
        (sub_80198B0(dword_83A1F60) >> 2) & 0x1FFFFF);

    // Set background map.
    CpuFastSet(dword_83A13A0, graphicsBuffer, 512);
    v10 = &graphicsBuffer[192];
    v11 = 3;
    while (v11 != 0) {
        u16* v13;
        u16* v14;
        int i;

        // Corners.
        v10[4] = 1;
        v10[36] = 3;
        v10[25] = 1025;
        v10[57] = 1027;

        // Top and bottom row.
        v13 = &v10[37];
        v14 = &v10[5];
        i = 0;
        while (i <= 19) {
            v14[i + 0] = 2;  // Top
            v13[i + 0] = 17; // Bottom
            v14[i + 1] = 2;
            v13[i + 1] = 17;
            v14[i + 2] = 2;
            v13[i + 2] = 17;
            v14[i + 3] = 2;
            v13[i + 3] = 17;
            v14[i + 4] = 2;
            v13[i + 4] = 17;
            v14[i + 5] = 2;
            v13[i + 5] = 17;
            v14[i + 6] = 2;
            v13[i + 6] = 17;
            v14[i + 7] = 2;
            v13[i + 7] = 17;
            v14[i + 8] = 2;
            v13[i + 8] = 17;
            v14[i + 9] = 2;
            v13[i + 9] = 17;
            i += 10;
        }

        // Skip to next row.
        v11--;
        v10 = &v10[96];
    }
    CpuFastSet(graphicsBuffer, (void*)0x600D800, 512);
    if (graphicsBuffer) {
        free_heap_8018D9C(graphicsBuffer);
    }

    sub_8020994(0x3000, 8, 0, 0x80u);

    optionsScreen->cursor = sub_8020DD0(5, 24581, 1, -1, -1, -1, -1);
    sub_801E150(optionsScreen->cursor, 0, -1, 0, 0);
    sprite_show_8020CBC(optionsScreen->cursor);
    optionsScreen->cursor->xPosition = 40;
    optionsScreen->cursor->yPosition = 55;

    if (gGameState.gameBoyPlayerDetected == 0) {
        CpuFastSet(off_83A2880, (void*)0x2000280, 16);
        CpuFastSet(dword_83A1BA0, (void*)0x2000080, 120);
    } else {
        CpuFastSet(off_83A28C0, (void*)0x2000280, 16);
        CpuFastSet(dword_83A1D80, (void*)0x2000080, 120);
    }

    gGameState.field_0 = -1;
    gGameState.field_2 = -1;

    optionsScreen->textEngineCode = alloc_zero_8018DB4(sub_8198784 - sub_819941C, 0, "BBWF", 1);
    sub_81994EC(optionsScreen->textEngineCode, off_851F9E8);
    optionsScreen->textContext = alloc_Zero(20, 0, "BBWI", 1);
    optionsScreen->graphicsWorkAllocation = alloc_zero_8018DB4(115231, 1, "BWCW", 1);
    optionsScreen->optionLabelTiles = (u8*)((int)&optionsScreen->graphicsWorkAllocation[31] & 0xFFFFFFE0);
    optionsScreen->confirmationDialogTiles = &optionsScreen->optionLabelTiles[57600];

    optionsScreen->confirmationDialogTilemaps = alloc_zero_8018DB4(3840, 1, "BWSW", 1);
    v21 = &optionsScreen->confirmationDialogTilemaps[192];
    v22 = 0;
    while (v22 < 3) {
        u16 v23;
        u16* v26;
        u16* v27;
        int j;

        v23 = ((v22 << 6) + 128) | 0xE000;
        v26 = &v21[36];
        v27 = &v21[4];

        for (j = 0; j < 21;) {
            v27[0] = v23;
            v26[0] = v23 + 32;
            v23++;
            v27[1] = v23;
            v26[1] = v23 + 32;
            v27 += 2;
            v26 += 2;
            j += 2;
            v23++;
        }
        v22++;
        v21 = &v21[96];
    }
    CpuFastSet(optionsScreen->confirmationDialogTilemaps, (void*)0x600D000, 512);

    v31 = 0;
    CpuFastSet((void*)&v31, (void*)0x6004000, 0x1000008);
    options_screen_build_option_labels(optionsScreen, 0);
    dword_3001034(0, (void*)optionsScreen->confirmationDialogTiles, 57600);

    sub_8052C50(optionsScreen, 1);
    sub_8017E34();
    sub_8052C50(optionsScreen, 2);
    sub_8017E34();
    sub_8052C50(optionsScreen, 3);
    sub_8017E34();
    sub_8052C50(optionsScreen, 4);
    sub_8017E34();
    sub_8052C50(optionsScreen, 5);
    sub_8017E34();
    sub_8052C50(optionsScreen, 6);
    sub_8017E34();
    sub_8052C50(optionsScreen, 7);
    sub_8017E34();
    sub_801A548();

    (*(vu16*)(0x2000000 + 0x08)) = 0x1805;
    (*(vu16*)(0x2000000 + 0x0A)) = 0x1901;
    (*(vu16*)(0x2000000 + 0x0C)) = 0x1A03;
    (*(vu16*)(0x2000000 + 0x0E)) = 0x1B03;
    (*(vu16*)(0x2000000 + 0x10)) = 0;
    (*(vu16*)(0x2000000 + 0x12)) = 0;
    (*(vu16*)(0x2000000 + 0x14)) = 0;
    (*(vu16*)(0x2000000 + 0x16)) = 0;
    (*(vu16*)(0x2000000 + 0x18)) = 0;
    (*(vu16*)(0x2000000 + 0x1A)) = 0;
    (*(vu16*)(0x2000000 + 0x1C)) = 0;
    (*(vu16*)(0x2000000 + 0x1E)) = 0;
    (*(vu16*)(0x2000000 + 0x00)) = 0x1C40;

    music_play(0, 30, MUSIC_VOLUME_UNCHANGED);
    music_set_volume(0, 0xFFu, 0x10u);

    return optionsScreen;
}
#endif

void options_screen_update(struct OptionsScreen* optionsScreen) {
    switch (optionsScreen->process.state) {
        case OPTIONS_SCREEN_STATE_FADE_IN:
            optionsScreen->fadeTimer--;
            BUFFER_REG_BLDY = optionsScreen->fadeTimer;
            if (optionsScreen->fadeTimer == 0) {
                optionsScreen->process.state = OPTIONS_SCREEN_STATE_SELECT_OPTION;
            }
            break;

        case OPTIONS_SCREEN_STATE_SELECT_OPTION:
            if (optionsScreen->inputCooldown > 0) {
                optionsScreen->inputCooldown--;
            }
            if (optionsScreen->dialogWindow.progress > 0) {
                window_animation_update(&optionsScreen->dialogWindow);
                break;
            }
            if (optionsScreen->inputCooldown != 0 || gGameState.field_2A & A_BUTTON) {
                break;
            }
            if (gGameState.field_2A & B_BUTTON) {
                if ((bool8)options_screen_save_settings(optionsScreen)) {
                    optionsScreen->fadeTimer = 16;
                    music_set_volume(0, 0, 16);
                    optionsScreen->process.state = OPTIONS_SCREEN_STATE_LEAVE;
                } else {
                    optionsScreen->process.state = OPTIONS_SCREEN_STATE_SAVE_ERROR;
                }
                break;
            }
            if (gGameState.field_2E & DPAD_UP) {
                optionsScreen->selectedOption--;
                if (optionsScreen->selectedOption < 0) {
                    optionsScreen->selectedOption = 2;
                }
                sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
            } else if (gGameState.field_2E & DPAD_DOWN) {
                optionsScreen->selectedOption++;
                if (optionsScreen->selectedOption > 2) {
                    optionsScreen->selectedOption = 0;
                }
                sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
            }
            optionsScreen->cursor->yPosition = 24 * optionsScreen->selectedOption + 55;
            switch (optionsScreen->selectedOption) {
                case 0:
                    if ((optionsScreen->pendingSettings ^ OPTION_SETTINGS_EASY_SLEEP) & OPTION_SETTINGS_EASY_SLEEP) {
                        if (gGameState.field_2A & DPAD_LEFT) {
                            optionsScreen->pendingSettings |= OPTION_SETTINGS_EASY_SLEEP;
                            options_screen_prepare_confirmation_dialog(optionsScreen, word_83A2900[0], word_83A2900[1]);
                            sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                            optionsScreen->process.state = OPTIONS_SCREEN_STATE_EASY_SLEEP_CONFIRMATION;
                        }
                    } else {
                        if (gGameState.field_2A & DPAD_RIGHT) {
                            optionsScreen->pendingSettings &= ~OPTION_SETTINGS_EASY_SLEEP;
                            sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                        }
                    }
                    break;

                case 1:
                    if (gGameState.gameBoyPlayerDetected == 1) {
                        if (!(optionsScreen->pendingSettings & OPTION_SETTINGS_RUMBLE)) {
                            if (gGameState.field_2A & DPAD_LEFT) {
                                optionsScreen->pendingSettings |= OPTION_SETTINGS_RUMBLE;
                                options_screen_prepare_confirmation_dialog(optionsScreen, word_83A2900[2], word_83A2900[3]);
                                sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                                optionsScreen->process.state = OPTIONS_SCREEN_STATE_RUMBLE_CONFIRMATION;
                            }
                        } else {
                            if (gGameState.field_2A & DPAD_RIGHT) {
                                optionsScreen->pendingSettings &= ~OPTION_SETTINGS_RUMBLE;
                                gGameState.field_88B_0 = 0;
                                sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                            }
                        }
                    }
                    break;

                case 2:
                    if (!(optionsScreen->pendingSettings & OPTION_SETTINGS_AUTO_SLEEP)) {
                        if (gGameState.field_2A & DPAD_LEFT) {
                            optionsScreen->pendingSettings |= OPTION_SETTINGS_AUTO_SLEEP;
                            options_screen_prepare_confirmation_dialog(optionsScreen, word_83A2900[4], word_83A2900[5]);
                            sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                            optionsScreen->process.state = OPTIONS_SCREEN_STATE_AUTO_SLEEP_CONFIRMATION;
                        }
                    } else {
                        if (gGameState.field_2A & DPAD_RIGHT) {
                            optionsScreen->pendingSettings &= ~OPTION_SETTINGS_AUTO_SLEEP;
                            sound_effect_play(95, SOUND_VOLUME_UNCHANGED);
                        }
                    }
                    break;
            }
            break;

        case OPTIONS_SCREEN_STATE_EASY_SLEEP_CONFIRMATION:
            if (optionsScreen->dialogWindow.progress == 0) {
                if (gGameState.field_2A & A_BUTTON) {
                    optionsScreen->cursor->xPosition = 40;
                    optionsScreen->cursor->yPosition = 24 * optionsScreen->selectedOption + 55;
                    off_839EC80[REG_OFFSET_DISPCNT + 1] |= DISPCNT_HBLANK_INTERVAL;
                    optionsScreen->dialogWindow.isClosing = 1;
                    optionsScreen->dialogWindow.progress = 7;
                    BUFFER_REG_DISPCNT &= ~DISPCNT_BG0_ON;
                    sound_effect_play(96, SOUND_VOLUME_UNCHANGED);
                    optionsScreen->process.state = OPTIONS_SCREEN_STATE_SELECT_OPTION;
                }
            } else {
                window_animation_update(&optionsScreen->dialogWindow);

                if (optionsScreen->dialogWindow.progress == 6) {
                    sub_8018218(optionsScreen->confirmationDialogTiles, (void*)0x6004020, 0x4B00, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 7) {
                    sub_8018218(optionsScreen->confirmationDialogTilemaps, (void*)0x600C000, 0x500, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 0) {
                    optionsScreen->cursor->xPosition = optionsScreen->okButtonX + 6;
                    optionsScreen->cursor->yPosition = optionsScreen->okButtonY + 7;
                    BUFFER_REG_DISPCNT |= DISPCNT_BG0_ON;
                }
            }
            break;

        case OPTIONS_SCREEN_STATE_RUMBLE_CONFIRMATION:
            if (optionsScreen->dialogWindow.progress == 0) {
                if (gGameState.field_2A & A_BUTTON) {
                    optionsScreen->cursor->xPosition = 40;
                    optionsScreen->cursor->yPosition = 24 * optionsScreen->selectedOption + 55;
                    off_839EC80[REG_OFFSET_DISPCNT + 1] |= DISPCNT_HBLANK_INTERVAL;
                    optionsScreen->dialogWindow.isClosing = 1;
                    optionsScreen->dialogWindow.progress = 7;
                    BUFFER_REG_DISPCNT &= ~DISPCNT_BG0_ON;
                    gGameState.field_88B_0 = 1;
                    optionsScreen->inputCooldown = 16;
                    sub_801ABE8(0, 16, 0);
                    sound_effect_play(96, SOUND_VOLUME_UNCHANGED);
                    optionsScreen->process.state = OPTIONS_SCREEN_STATE_SELECT_OPTION;
                }
            } else {
                window_animation_update(&optionsScreen->dialogWindow);
                if (optionsScreen->dialogWindow.progress == 6) {
                    sub_8018218(optionsScreen->confirmationDialogTiles + 0x4B00, (void*)0x6004020, 0x4B00, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 7) {
                    sub_8018218(optionsScreen->confirmationDialogTilemaps + 0x280, (void*)0x600C000, 0x500, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 0) {
                    optionsScreen->cursor->xPosition = optionsScreen->okButtonX + 6;
                    optionsScreen->cursor->yPosition = optionsScreen->okButtonY + 7;
                    BUFFER_REG_DISPCNT |= DISPCNT_BG0_ON;
                }
            }
            break;

        case OPTIONS_SCREEN_STATE_AUTO_SLEEP_CONFIRMATION:
            if (optionsScreen->dialogWindow.progress == 0) {
                if (gGameState.field_2A & A_BUTTON) {
                    optionsScreen->cursor->xPosition = 40;
                    optionsScreen->cursor->yPosition = 24 * optionsScreen->selectedOption + 55;
                    off_839EC80[REG_OFFSET_DISPCNT + 1] |= DISPCNT_HBLANK_INTERVAL;
                    optionsScreen->dialogWindow.isClosing = 1;
                    optionsScreen->dialogWindow.progress = 7;
                    BUFFER_REG_DISPCNT &= ~DISPCNT_BG0_ON;
                    sound_effect_play(96, SOUND_VOLUME_UNCHANGED);
                    optionsScreen->process.state = OPTIONS_SCREEN_STATE_SELECT_OPTION;
                }
            } else {
                window_animation_update(&optionsScreen->dialogWindow);
                if (optionsScreen->dialogWindow.progress == 6) {
                    sub_8018218(optionsScreen->confirmationDialogTiles + 0x9600, (void*)0x6004020, 0x4B00, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 7) {
                    sub_8018218(optionsScreen->confirmationDialogTilemaps + 0x500, (void*)0x600C000, 0x500, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 0) {
                    optionsScreen->cursor->xPosition = optionsScreen->okButtonX + 6;
                    optionsScreen->cursor->yPosition = optionsScreen->okButtonY + 7;
                    BUFFER_REG_DISPCNT |= DISPCNT_BG0_ON;
                }
            }
            break;

        case OPTIONS_SCREEN_STATE_SAVE_ERROR:
            options_screen_build_save_error_dialog(optionsScreen);
            options_screen_prepare_save_error_dialog(optionsScreen);
            optionsScreen->fadeTimer = 240;
            optionsScreen->process.state = OPTIONS_SCREEN_STATE_SAVE_ERROR_CONFIRMATION;
            break;

        case OPTIONS_SCREEN_STATE_SAVE_ERROR_CONFIRMATION:
            if (optionsScreen->dialogWindow.progress == 0) {
                optionsScreen->fadeTimer--;
                if (optionsScreen->fadeTimer == 0
                    || gGameState.field_2A & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                    optionsScreen->fadeTimer = 16;
                    music_set_volume(0, 0, 16);
                    optionsScreen->process.state = OPTIONS_SCREEN_STATE_LEAVE;
                }
            } else {
                window_animation_update(&optionsScreen->dialogWindow);
                if (optionsScreen->dialogWindow.progress == 6) {
                    sub_8018218(optionsScreen->confirmationDialogTiles, (void*)0x6004020, 0x4B00, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 7) {
                    sub_8018218(optionsScreen->confirmationDialogTilemaps, (void*)0x600C000, 0x500, 32, 0);
                } else if (optionsScreen->dialogWindow.progress == 0) {
                    BUFFER_REG_DISPCNT |= DISPCNT_BG0_ON;
                }
            }
            break;

        case OPTIONS_SCREEN_STATE_LEAVE:
            optionsScreen->fadeTimer--;
            BUFFER_REG_BLDY = 16 - optionsScreen->fadeTimer;
            if (optionsScreen->fadeTimer == 0) {
                if (optionsScreen) {
                    optionsScreen->process.definition = &gOptionsScreenProcessDefinition;
                    sub_8021FD4();
                    if (optionsScreen->renderProcess) {
                        process_remove(optionsScreen->renderProcess, 3);
                    }
                    if (optionsScreen->windowAnimationTilemap) {
                        free_heap_8018D9C(optionsScreen->windowAnimationTilemap);
                    }
                    if (optionsScreen->graphicsWorkAllocation) {
                        free_heap_8018D9C(optionsScreen->graphicsWorkAllocation);
                    }
                    if (optionsScreen->confirmationDialogTilemaps) {
                        free_heap_8018D9C(optionsScreen->confirmationDialogTilemaps);
                    }
                    if (optionsScreen->textEngineCode) {
                        free_heap_8018D9C(optionsScreen->textEngineCode);
                    }
                    free_heap_8018DA8((void*)optionsScreen->textContext);
                    sub_801A6B0();
                    gGameState.field_31 = 2;
                    BUFFER_REG_DISPCNT = 0;
                    BUFFER_REG_BLDCNT = BLDCNT_TGT1_OBJ | BLDCNT_EFFECT_NONE;
                    process_remove(&optionsScreen->process, 3);
                }
                //! Fix this when other functions are also matching.
                title_screen_create(
                    alloc_Zero(sizeof(struct TitleScreen), 0, (char*)0x081E2714 /*"OPEN"*/, 0), 8,
                    (char*)0x081E2714 /*"OPEN"*/, 3);
                return;
            }
            break;
    }

    sub_8021F7C();
}

int options_screen_save_settings(struct OptionsScreen* optionsScreen) {
    gGameState.field_88A_4 = ((optionsScreen->pendingSettings >> OPTION_SETTINGS_SHIFT_EASY_SLEEP) & 1) != 0;
    gGameState.field_88B_0 = ((optionsScreen->pendingSettings >> OPTION_SETTINGS_SHIFT_RUMBLE) & 1) != 0;
    dword_3000FFC->field_8_3 = ((optionsScreen->pendingSettings >> OPTION_SETTINGS_SHIFT_EASY_SLEEP) & 1) != 0;
    dword_3000FFC->field_8_4 = ((optionsScreen->pendingSettings >> OPTION_SETTINGS_SHIFT_RUMBLE) & 1) != 0;
    dword_3000FFC->field_8_5 = ((optionsScreen->pendingSettings >> OPTION_SETTINGS_SHIFT_AUTO_SLEEP) & 1) != 0;

    return sub_812454C();
}

void options_screen_build_option_labels(struct OptionsScreen* optionsScreen, int copyToVram) {
    int i;

    dword_3001034(0, (void*)optionsScreen->optionLabelTiles, 6144);

    for (i = 0; i < 3; i++) {
        if (gGameState.gameBoyPlayerDetected != 1 && i == 1) {
            sub_8199D78(optionsScreen->textContext, optionsScreen->optionLabelTiles, 32, 4, 0, 0, 1, 2, 7, 0);
        } else {
            sub_8199D78(optionsScreen->textContext, optionsScreen->optionLabelTiles, 32, 4, 0, 0, 1, 2, 5, 0);
        }
        sub_8199D5C(optionsScreen->textContext, 0, 16 * i + 2, *off_83A2920[i] + 2);
        do {
            u8* command = optionsScreen->textContext->field_8;
            if (command[0] == 255 && command[1] == 11 && command[2] == 1) {
                optionsScreen->textContext->field_8 += 3;
            }
        } while (sub_8199624(optionsScreen->textContext) != 0);
    }

    if (copyToVram) {
        sub_8018218((void*)optionsScreen->optionLabelTiles, (void*)0x6001000, 6144, 32, 0);
    } else {
        CpuFastSet((void*)optionsScreen->optionLabelTiles, (void*)0x6001000, 0x600);
    }
}
