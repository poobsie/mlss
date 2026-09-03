#include "global.h"
#include "audio/sound_effects.h"
#include "object/repeating_command.h"
#include "object/runtime_object.h"

#define SEC(name)         __attribute__((section(".text.misc_helpers_03." #name)))
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;
extern int sub_806EADC();
extern int sub_8095548();
extern int sub_80DC638();

extern int script_cmd_return();
extern int sub_8018818();
extern int sub_8027030();
extern int sub_8047A5C();
extern int sub_805DA78();
extern int sub_805DF88();
extern int sub_80602B4();
extern int sub_8060438();
extern int sub_8060500();
extern int sub_8060694();
extern int sub_8060A58();
extern int sub_8061DA8();
extern int sub_8062188();
extern int sub_806259C();
extern int sub_8063AD4();
extern int sub_8064E30();
extern int sub_80651B0();
extern int sub_8065510();
extern int sub_8065D10();
extern int sub_8066334();
extern int sub_8066540();
extern int sub_806688C();
extern int sub_8067DC8();
extern int sub_806822C();
extern int sub_8068A28();
extern int sub_8068AA8();
extern int sub_806C454();
extern int sub_806CBCC();
extern int sub_806CED0();
extern int sub_806E414();
extern int sub_806FBD0();
extern int sub_80700C8();
extern int sub_8070DCC();
extern int sub_80712D8();
extern int sub_80752BC();
extern int sub_8078894();
extern int sub_80789B4();
extern int sub_8078A5C();
extern int sub_807940C();
extern int sub_8079BA8();
extern int sub_807C298();
extern int sub_807F4FC();
extern int sub_807F708();
extern int sub_807F754();
extern int sub_807FB64();
extern int sub_807FEB4();
extern int sub_80801BC();
extern int sub_8082B00();
extern int sub_8082C20();
extern int sub_8082CCC();
extern int sub_8082D00();
extern int sub_8082E1C();
extern int sub_8085260();
extern int sub_8085A6C();
extern int sub_8087124();
extern int sub_80871A8();
extern int sub_80873B8();
extern int sub_80874B4();
extern int sub_808750C();
extern int sub_8087CE4();
extern int sub_8087DE4();
extern int sub_8088964();
extern int sub_80894B8();
extern int sub_808A27C();
extern int sub_808A3C4();
extern int sub_808A4D0();
extern int sub_808A660();
extern int sub_808A7B0();
extern int sub_808A8F8();
extern int sub_808AA60();
extern int sub_80904C4();
extern int sub_8090830();
extern int sub_80970B8();
extern int sub_8097F30();
extern int sub_8099448();
extern int sub_80997E4();
extern int sub_8099BE4();
extern int sub_809B0A8();
extern int sub_809BA28();
extern int sub_809C4F8();
extern int sub_809C660();
extern int sub_80AC610();
extern int sub_80B325C();
extern int sub_80C0CC0();
extern int sub_80D69D8();
extern int sub_80D9A98();
extern int sub_80DA1EC();
extern int sub_80DA208();
extern int sub_80DABFC();
extern int sub_80DC27C();
extern int sub_80DDA78();
extern int sub_80DE4A4();
extern int sub_80DEC60();
extern int sub_80DEDEC();
extern int sub_80EA5C8();
extern int sub_80F2524();
extern int sub_80F7068();
extern int sub_80F7538();
extern int sub_80F8984();
extern int sub_80F94A8();
extern int sub_80FADD4();
extern int sub_81054D4();
extern int sub_810C05C();
extern int sub_810DD7C();
extern int sub_81100B0();
extern int sub_81101BC();
extern int sub_8111848();
extern int sub_8112740();
extern int sub_8112CE4();
extern int sub_8113458();
extern int sub_81140C0();
extern int sub_811458C();
extern int sub_81147B4();
extern int sub_81147D0();
extern int sub_81165CC();
void sub_80DED84(void* arg0);
void sub_810FF4C(void* arg0);
void sub_810D70C(void* arg0);
void sub_80F75D8(s32 arg0);
void sub_80F8C60(void* arg0, void* arg1);
void sub_805F690(void* arg0);
void sub_80605CC(void* arg0);
void sub_8061F3C(void* arg0);
void sub_8061FC8(void* arg0);
void sub_8062DE0(void* arg0);
void sub_8063C60(void* arg0);
void sub_8066D78(void* arg0);
void sub_8066EB4(void* arg0);
void sub_8068F10(void* arg0);
void sub_8069450(void* arg0);
void sub_806CBA0(void* arg0);
void sub_8070A50(void* arg0);
void sub_8072738(void* arg0);
void sub_80900A8(void* arg0);
void sub_809551C(void* arg0);
void sub_809A0F4(void* arg0);
void sub_809A120(void* arg0);
void sub_809A14C(void* arg0);
void sub_811254C(void* arg0);
void sub_808C754(void* arg0);
s32 sub_80F0540(void* arg3);
s32 sub_80F0AE0(void* arg0, s32* arg2);
s32 sub_80F10E0(void* arg0, s32* arg1, void* arg2);
void sub_810CBDC(void* arg0);
void sub_808C7B8(void* arg0);
void sub_808C7E4(void* arg0);
void sub_808C810(void* arg0);
void sub_808C83C(void* arg0);
void sub_808C8E0(void* arg0);
void sub_808C90C(void* arg0);
void sub_808C968(void* arg0);
void sub_810D228(s32 arg0, s32 arg1, s32 arg2);
void sub_810D5F4(void* arg0);
void sub_805A95C(void* arg0);
void sub_806D4F0(void* arg0);
void sub_806D51C(void* arg0);
void sub_80605F8(void* arg0);
void sub_806398C(void* arg0);
void sub_806E8E8(void* arg0);
void sub_806EAA8(void* arg0);
void sub_80703F0(void* arg0);
void sub_8070F64(void* arg0);
void sub_80F8C8C(void* arg0, void* arg1);
void sub_807F4C4(void* arg0, s32 arg1);
void sub_8107118(void* arg0);
void sub_8099FFC(void* arg0);
void sub_809A06C(void* arg0);
void sub_809B038(void* arg0);
void sub_809C448(void* arg0);
s32 sub_80F0B4C(void* arg1);
s32 sub_80FA7E4(void* arg0, void* arg1);
void sub_8063BF0(void* arg0);
void sub_810CAD0(void);
void sub_8114558(void* arg0);
void sub_807FBD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void sub_8077570(void* arg0);
void sub_8106D20(void* arg0);
void sub_808A0B0(void* arg0);
void sub_8060CB8(void* arg0);
void sub_80DB0FC(void* arg0);
void sub_80DC5CC(void* arg0);
void sub_807FC54(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void sub_80C0980(void* arg0);
void sub_806657C(void* arg0);
void sub_806E5F4(void* arg0);
void sub_80710E0(void* arg0);
s32 sub_80F7D0C(void* arg2);
void sub_8114528(void* arg0);
void sub_806A19C(void* arg0);
void sub_8079C0C(void* arg0);
void sub_80603D8(void* arg0);
void sub_8068074(void* arg0);
void sub_80687EC(void* arg0);
void sub_807953C(void* arg0);
void sub_8064C80(void* arg0);
void sub_806CB3C(void* arg0);
void sub_807F448(void);
void sub_810D170(void);
void sub_80F7770(void* arg0);
void sub_8060404(void* arg0);
void sub_80680A0(void* arg0);
void sub_8079654(void* arg0);
void sub_80689AC(void* arg0);
void sub_80799B4(void* arg0);
void sub_80D2D6C(void* arg0);
u8 script_cmd_btl_return(s32 arg0, s32 arg1, s32* arg2);
void sub_8114854(void* arg0);
void sub_81145C8(void* arg0);
void sub_8112498(void* arg0);
s32 sub_80F7CD0(void* arg2);
void sub_810707C(void* arg0);
void sub_810D00C(void);
void sub_810D1A4(void* arg0);
void sub_807127C(void* arg0);
void sub_8089928(void* arg0);
void sub_80D8D18(void* arg0);
s32 sub_80F09A8(void* arg0, void* arg2);
s32 sub_80F8900(void* arg0, s32* arg1, void* arg2, void* arg3);
void sub_806025C(void* arg0);
void sub_8060288(void* arg0);
void sub_8112840(void* arg0);
void sub_8065E68(void* arg0);
void sub_8065B48(void* arg0);
void sub_806021C(void* arg0);
void sub_807991C(void* arg0);
s32 sub_81132D4(void* arg0, void* arg1);
void sub_80644DC(void* arg0);
s32 sub_80F7BB4(void* arg0, void* arg1, s32* arg2);
s32 sub_8065310(void* arg0);
void sub_8087360(void);
void sub_80B30AC(void* arg0);
void sub_8068DBC(void* arg0);
void sub_809B3DC(void* arg0);
void sub_808EC58(void* arg0);

SEC(sub_80F75D8) void sub_80F75D8(s32 arg0) {
    void* temp_r2;

    temp_r2 = FIELD_AT(FIELD_AT(*(void**)0x03000FD8, void**, 0x244), void**, 0x2C);
    FIELD_AT(temp_r2, s32*, 0x1788) = (s32)(FIELD_AT(temp_r2, s32*, 0x1788) | arg0);
    FIELD_AT(temp_r2, s32*, 0x1798) = (s32)(FIELD_AT(temp_r2, s32*, 0x1798) | arg0);
}

SEC(sub_80F8C60) void sub_80F8C60(void* arg0, void* arg1) {
    if (FIELD_AT(FIELD_AT(arg0, void**, 0x2C), s32*, 0x1788) & 0x4000) {
        FIELD_AT(arg1, u16*, 0xA0) = (u16)(0xFDFF & FIELD_AT(arg1, u16*, 0xA0));
    }
}

SEC(sub_805F690) void sub_805F690(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_805DF88;
    }
}

SEC(sub_80605CC) void sub_80605CC(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 2, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80602B4;
    }
}

SEC(sub_8061F3C) void sub_8061F3C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8061DA8;
    }
}

SEC(sub_8061FC8) void sub_8061FC8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_8062DE0) void sub_8062DE0(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xB, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806259C;
    }
}

SEC(sub_8063C60) void sub_8063C60(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80874B4;
    }
}

SEC(sub_8066D78) void sub_8066D78(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xB, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_8066EB4) void sub_8066EB4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 7, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806688C;
    }
}

SEC(sub_8068F10) void sub_8068F10(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xB, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_8069450) void sub_8069450(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 9, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_806CBA0) void sub_806CBA0(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0x15, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806C454;
    }
}

SEC(sub_8070A50) void sub_8070A50(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 5, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8070DCC;
    }
}

SEC(sub_8072738) void sub_8072738(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0x15, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80712D8;
    }
}

SEC(sub_80900A8) void sub_80900A8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0x204D, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_809551C) void sub_809551C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 8, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8095548;
    }
}

SEC(sub_809A0F4) void sub_809A0F4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 8, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_809A120;
    }
}

SEC(sub_809A120) void sub_809A120(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 9, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_809A14C;
    }
}

SEC(sub_809A14C) void sub_809A14C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xA, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8099BE4;
    }
}

SEC(sub_811254C) void sub_811254C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xE, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8111848;
    }
}

SEC(sub_810CBDC) void sub_810CBDC(void* arg0) {
    s32 temp_r0;

    temp_r0 = FIELD_AT(FIELD_AT(arg0, void**, 8), s32*, 4);
    if (temp_r0 == 0) {
        FIELD_AT(arg0, s32*, 4) = temp_r0;
        return;
    }
    FIELD_AT((void*)0x0400001A, u16*, 0) = (u16) * (u16*)0x0200001A;
    FIELD_AT((void*)0x0400001A, u16*, 4) = (u16) * (u16*)0x0200001E;
}

SEC(sub_808C7B8) void sub_808C7B8(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 8, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808AA60;
    }
}

SEC(sub_808C7E4) void sub_808C7E4(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A8F8;
    }
}

SEC(sub_808C810) void sub_808C810(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 8, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A7B0;
    }
}

SEC(sub_808C83C) void sub_808C83C(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A660;
    }
}

SEC(sub_808C8E0) void sub_808C8E0(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 9, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A4D0;
    }
}

SEC(sub_808C90C) void sub_808C90C(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 5, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A3C4;
    }
}

SEC(sub_808C968) void sub_808C968(void* arg0) {
    u16 temp_r1;

    temp_r1 = FIELD_AT(arg0, u16*, 0xAC);
    FIELD_AT(arg0, u16*, 0xAC) = (u16)(temp_r1 - 1);
    if ((s32)(temp_r1 << 0x10) <= 0) {
        sub_8082E1C(arg0, 5, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A27C;
    }
}

SEC(sub_810D5F4) void sub_810D5F4(void* arg0) {
    s32 temp_r0;

    temp_r0 = FIELD_AT(FIELD_AT(arg0, void**, 8), s32*, 4);
    if (temp_r0 == 0) {
        FIELD_AT(arg0, s32*, 4) = temp_r0;
    }
    FIELD_AT((void*)0x0400001A, u16*, 0) = (u16) * (u16*)0x0200001A;
    FIELD_AT((void*)0x0400001A, u16*, 4) = (u16) * (u16*)0x0200001E;
}

SEC(sub_805A95C) void sub_805A95C(void* arg0) {
    FIELD_AT((void*)0x02000010, s16*, 0) = (s16)(0x1FF & FIELD_AT(arg0, u16*, 0x30));
    *(s16*)0x02000014 = 0x1FF & FIELD_AT(arg0, u16*, 0x32);
    FIELD_AT((void*)0x02000010, s16*, 2) = (s16)(0xFF & FIELD_AT(arg0, u16*, 0x34));
    *(s16*)0x02000016 = 0xFF & FIELD_AT(arg0, u16*, 0x36);
}

SEC(sub_806D4F0) void sub_806D4F0(void* arg0) {
    sub_8082E1C(arg0, 2, 0, 0);
    FIELD_AT(arg0, s32*, 0x84) = 0x300;
    FIELD_AT((arg0 + 0x84), s32*, 8) = 0x33;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806CED0;
}

SEC(sub_806D51C) void sub_806D51C(void* arg0) {
    sub_8082E1C(arg0, 2, 0, 0);
    FIELD_AT(arg0, s32*, 0x84) = 0x300;
    FIELD_AT((arg0 + 0x84), s32*, 8) = 0x33;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806CBCC;
}

SEC(sub_80605F8) void sub_80605F8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 6, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 1;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8060694;
    }
}

SEC(sub_806398C) void sub_806398C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xA, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 3;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8063AD4;
    }
}

SEC(sub_806E8E8) void sub_806E8E8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 5, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 0xA;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806E414;
    }
}

SEC(sub_806EAA8) void sub_806EAA8(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xA, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 0x3C;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806EADC;
    }
}

SEC(sub_80703F0) void sub_80703F0(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0x27, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 1;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80700C8;
    }
}

SEC(sub_8070F64) void sub_8070F64(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0x1D, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 5;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806FBD0;
    }
}

SEC(sub_810CAD0) void sub_810CAD0(void) {
    void* temp_r1;
    void* temp_r1_2;

    temp_r1 = FIELD_AT(*(void**)0x03000FD8, void**, 0x27C);
    if (temp_r1 != NULL) {
        FIELD_AT(temp_r1, UnknownWord**, 4) = (UnknownWord*)&sub_810C05C;
    }
    temp_r1_2 = FIELD_AT(*(void**)0x03000FD8, void**, 0x280);
    if (temp_r1_2 != NULL) {
        FIELD_AT(temp_r1_2, UnknownWord**, 4) = (UnknownWord*)&sub_810C05C;
    }
}

SEC(sub_8114558) void sub_8114558(void* arg0) {
    UnknownWord* var_r1;
    s32 temp_r0;

    if (8
        & FIELD_AT(FIELD_AT(FIELD_AT(FIELD_AT(arg0, void**, 0x30), void**, 0x30), void**, 8), u8*,
                   0x12)) {
        temp_r0 = FIELD_AT(arg0, s32*, 0xA0) - 1;
        FIELD_AT(arg0, s32*, 0xA0) = temp_r0;
        var_r1 = (UnknownWord*)&sub_81140C0;
        if (temp_r0 != 0) {
            var_r1 = (UnknownWord*)&sub_811458C;
        }
        FIELD_AT(arg0, UnknownWord**, 0x4C) = var_r1;
    }
}

SEC(sub_807FBD8) void sub_807FBD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    sub_8082C20(FIELD_AT(*(void**)0x03000FD8, s32*, 0x24C), arg0, arg1, arg2, arg3);
}

SEC(sub_8077570) void sub_8077570(void* arg0) {
    s32 var_r0;

    FIELD_AT(arg0, s32*, 0x18) = (s32)(FIELD_AT(arg0, s32*, 0x18) + FIELD_AT(arg0, s32*, 0x8C));
    FIELD_AT(arg0, s32*, 0x8C) = (s32)(FIELD_AT(arg0, s32*, 0x8C) - 0x80);
    var_r0 = FIELD_AT(arg0, s32*, 0x18);
    if (var_r0 < 0) {
        var_r0 += 0xFF;
    }
    if ((s32)(var_r0 >> 8) <= 0x28) {
        FIELD_AT(arg0, s32*, 0x18) = 0x2800;
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}
SEC(sub_8077570) const u16 sub_8077570_padding = 0;
SEC(sub_808A0B0) void sub_808A0B0(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        FIELD_AT(arg0, s16*, 0xAC) = 0x1E;
        sub_80873B8(arg0, 3, 0);
        FIELD_AT(arg0, UnknownWord**, 0x50) = (UnknownWord*)&sub_80894B8;
    }
}

SEC(sub_8060CB8) void sub_8060CB8(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 5, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 2;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8060A58;
    }
}

SEC(sub_80DB0FC) void sub_80DB0FC(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 3, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 0x18;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80DABFC;
    }
}

SEC(sub_80DC5CC) void sub_80DC5CC(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 7, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 0x20;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80DC638;
    }
}

SEC(sub_807FC54) void sub_807FC54(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    sub_8082CCC(FIELD_AT(*(void**)0x03000FD8, s32*, 0x24C), arg0, arg1, arg2, arg3, arg4);
}

SEC(sub_80C0980) void sub_80C0980(void* arg0) {
    void* temp_r5;

    temp_r5 = FIELD_AT(arg0, void**, 0x2C);
    sub_8087CE4();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        FIELD_AT(arg0, s32*, 0x4C) = 0;
        FIELD_AT(temp_r5, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80C0CC0;
    }
}

SEC(sub_806657C) void sub_806657C(void* arg0) {
    sub_8066540(FIELD_AT(arg0, s32*, 0x30), FIELD_AT(arg0, s32*, 0x10), FIELD_AT(arg0, s32*, 0x14),
                FIELD_AT(arg0, s32*, 0x18));
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        FIELD_AT(arg0, s16*, 0xAC) = 0x1E;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8066334;
    }
}

SEC(sub_806E5F4) void sub_806E5F4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        FIELD_AT(FIELD_AT(arg0, void**, 0x2C), s32*, 0x4C) = 0;
        sub_8082E1C(arg0, 7, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_80710E0) void sub_80710E0(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 7, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
        FIELD_AT(FIELD_AT(arg0, void**, 0x2C), s32*, 0x4C) = 0;
    }
}

SEC(sub_8114528) void sub_8114528(void* arg0) {
    u8 temp_r1;

    temp_r1 = sub_8087CE4(FIELD_AT(FIELD_AT(arg0, void**, 0x30), s32*, 0x30));
    if (temp_r1 == 0) {
        FIELD_AT(FIELD_AT(arg0, void**, 0x28), u8*, 0x113) = temp_r1;
        FIELD_AT(arg0, s32*, 0x50) = 0x081141F5;
        FIELD_AT(arg0, s32*, 0x4C) = 0x081141F5;
    }
}

SEC(sub_806A19C) void sub_806A19C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0x4071, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_8079C0C) void sub_8079C0C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xD, 0x4029, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8079C70;
    }
}

SEC(sub_8064C80) void sub_8064C80(void* arg0) {
    void* temp_r1;

    temp_r1 = FIELD_AT(arg0, void**, 8);
    FIELD_AT(temp_r1, u16*, 0xC) = (u16)(FIELD_AT(temp_r1, u16*, 0xC) + 0x1000);
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        FIELD_AT(FIELD_AT(arg0, void**, 0x28), s16*, 0xB4) = 1;
        sub_807C298(arg0);
    }
}
SEC(sub_8064C80) const u16 sub_8064C80_padding = 0;
SEC(sub_810D170) void sub_810D170(void) {
    void* temp_r1;

    temp_r1 = FIELD_AT(*(void**)0x03000FD8, void**, 0x278);
    if (temp_r1 != NULL) {
        FIELD_AT(temp_r1, s32*, 0x80) = 0;
        sub_807C298(temp_r1);
        FIELD_AT(*(void**)0x03000FD8, void**, 0x278) = NULL;
    }
}

SEC(sub_80F7770) void sub_80F7770(void* arg0) {
    void* temp_r1;

    sub_80F2524(FIELD_AT(*(void**)0x03000FD8, s32*, 0x244), FIELD_AT(arg0, u8*, 0xF4),
                FIELD_AT(arg0, s32*, 0xE8));
    temp_r1 = *(void**)0x03000FD8;
    FIELD_AT(temp_r1, u8*, 0x2BF) = (u8)(FIELD_AT(temp_r1, u8*, 0x2BF) | 4);
}

SEC(sub_8060404) void sub_8060404(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0xC, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 8;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8060500;
    }
}

SEC(sub_8079654) void sub_8079654(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 1, 0, 0);
        FIELD_AT(arg0, s32*, 0x9C) = 4;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80789B4;
    }
}

SEC(sub_80689AC) void sub_80689AC(void* arg0) {
    s32 temp_r5;
    void* temp_r1;

    temp_r5 = FIELD_AT(arg0, s32*, 0x80);
    if (temp_r5 == 0) {
        sub_8082E1C(arg0, 0, 0, 0);
        temp_r1 = FIELD_AT(arg0, void**, 0x30);
        FIELD_AT(temp_r1, s32*, 0x10) = (s32)(FIELD_AT(arg0, s32*, 0x38) + 0x2200);
        FIELD_AT(temp_r1, s32*, 0x14) = (s32)FIELD_AT(arg0, s32*, 0x3C);
        FIELD_AT(temp_r1, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8068A28;
        FIELD_AT(arg0, s32*, 0x4C) = temp_r5;
    }
}

SEC(sub_80799B4) void sub_80799B4(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, FIELD_AT(arg0, s32*, 0xA8) + 5, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 0x14;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8078A5C;
    }
}

SEC(script_cmd_btl_return) u8 script_cmd_btl_return(s32 arg0, s32 arg1, s32* arg2) {
    void* temp_r1;

    if (*arg2 != 0) {
        temp_r1 = *(void**)0x03000FD8;
        FIELD_AT(temp_r1, u8*, 0x2BF) = (u8)(FIELD_AT(temp_r1, u8*, 0x2BF) | 2);
    }
    return script_cmd_return(arg0 + 0x1C, arg1);
}

SEC(sub_8114854) void sub_8114854(void* arg0) {
    void* temp_r1;

    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        temp_r1 = *(void**)0x03000FD8;
        FIELD_AT(FIELD_AT(temp_r1, void**, 0x60), s32*, 0x54) = 0;
        FIELD_AT(FIELD_AT(temp_r1, void**, 0x64), s32*, 0x54) = 0;
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_8112498) void sub_8112498(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        FIELD_AT(arg0, u16*, 0xAC) = (u16)(FIELD_AT(arg0, u16*, 0xAC) + 1);
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8112740;
    }
}

SEC(sub_810707C) void sub_810707C(void* arg0) {
    UnknownWord (*temp_r1)(void*);

    if (!(0x20 & FIELD_AT(FIELD_AT(*(void**)0x03000FD8, void**, 0x7C), u8*, 0x122))) {
        temp_r1 = FIELD_AT(*(void**)0x03000FDC, UnknownWord(**)(void*), 0x8E58);
        FIELD_AT(arg0, UnknownWord(**)(void*), 4) = temp_r1;
        temp_r1(arg0);
    }
}

SEC(sub_80D8D18) void sub_80D8D18(void* arg0) {
    void* temp_r1;
    void* temp_r4;
    void* temp_r5;

    temp_r5 = FIELD_AT(*(void**)0x03000FD8, void**, 0x74);
    temp_r4 = temp_r5 + 8;
    sub_8087DE4(temp_r4);
    temp_r1 = FIELD_AT(temp_r4, void**, 0x30);
    FIELD_AT(temp_r1, s32*, 0x10) = (s32)FIELD_AT(temp_r4, s32*, 0x10);
    FIELD_AT(temp_r1, s32*, 0x14) = (s32)FIELD_AT(temp_r4, s32*, 0x14);
    FIELD_AT(temp_r1, s32*, 0x18) = (s32)FIELD_AT(temp_r4, s32*, 0x18);
    if (0x20 & FIELD_AT(temp_r5, u8*, 0x81)) {
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80D69D8;
    }
}

SEC(sub_806025C) void sub_806025C(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x5C);
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8060404;
    }
}

SEC(sub_8060288) void sub_8060288(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x5C);
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8060438;
    }
}

SEC(sub_8112840) void sub_8112840(void* arg0) {
    sub_8082E1C(arg0, -1, -1, 0);
    FIELD_AT(arg0, s32*, 0x4C) = 0;
    sub_810DD7C(FIELD_AT(*(void**)0x03000FD8, s32*, 0x58) + 8, arg0, 0xFF);
}

SEC(sub_8065E68) void sub_8065E68(void* arg0) {
    s32 temp_r0;

    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        temp_r0 = FIELD_AT(arg0, s32*, 0x9C) - 1;
        FIELD_AT(arg0, s32*, 0x9C) = temp_r0;
        if (temp_r0 <= 0) {
            sub_8082E1C(arg0, 8, 0, 0);
            FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8065D10;
        }
    }
}

SEC(sub_8065B48) void sub_8065B48(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8065510;
        sound_effect_stop(0x81);
    }
}

SEC(sub_806021C) void sub_806021C(void* arg0) {
    FIELD_AT(arg0, s32*, 0x10) = (s32)(FIELD_AT(arg0, s32*, 0x10) + 0xFFFFFE9A);
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 1, 0, 0);
        FIELD_AT(arg0, s16*, 0xAC) = 8;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80603D8;
    }
}

SEC(sub_807991C) void sub_807991C(void* arg0) {
    UnknownWord* temp_r0;
    UnknownWord* temp_r2;

    temp_r0 = FIELD_AT(arg0, UnknownWord**, 0x30);
    if (temp_r0 == NULL) {
        FIELD_AT(arg0, UnknownWord**, 0x4C) = temp_r0;
        return;
    }
    sub_8082E1C(arg0, 0x11, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8079BA8;
    temp_r2 = FIELD_AT(arg0, UnknownWord**, 0x30);
    FIELD_AT(temp_r2, s32*, 0xA0) = (s32)FIELD_AT(arg0, s32*, 0x9C);
    FIELD_AT(temp_r2, UnknownWord**, 0x4C) = (UnknownWord*)&sub_807940C;
}

SEC(sub_8087360) void sub_8087360(void) {
    void* temp_r2;

    temp_r2 = *(void**)0x03000FD8;
    if (0x80 & FIELD_AT(temp_r2, u8*, 0xC)) {
        sub_8097F30(FIELD_AT(temp_r2, s32*, 0x7C) + 8);
        return;
    }
    sub_80970B8(FIELD_AT(temp_r2, s32*, 0x7C) + 8);
}

SEC(sub_80B30AC) void sub_80B30AC(void* arg0) {
    sub_8087CE4();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        sub_807FB64(FIELD_AT(arg0, s32*, 8));
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80B325C;
    }
}

SEC(sub_8068DBC) void sub_8068DBC(void* arg0) {
    if (sub_8082B00() == 0) {
        sub_8082E1C(arg0, 2, 0, 0);
        FIELD_AT(arg0, s32*, 0x8C) = 0x300;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8068AA8;
    }
}

SEC(sub_809B3DC) void sub_809B3DC(void* arg0) {
    s32 temp_r0;
    void* temp_r1;

    temp_r1 = FIELD_AT(arg0, void**, 8);
    if (FIELD_AT(temp_r1, u8*, 0x21) != 0) {
        if (8 & FIELD_AT(temp_r1, u8*, 0x12)) {
            sub_8082E1C(arg0, 0, 0, 0);
            goto block_3;
        }
    } else {
    block_3:
        temp_r0 = FIELD_AT(arg0, s32*, 0x30);
        if (temp_r0 == 0) {
            FIELD_AT(arg0, s32*, 0x4C) = temp_r0;
        }
    }
}

SEC(sub_808EC58) void sub_808EC58(void* arg0) {
    if (0x38 & FIELD_AT(arg0, u8*, 0x76)) {
        runtime_object_finish_action(arg0);
        return;
    }
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        runtime_object_finish_action(arg0);
    }
}
SEC(sub_808EC58) const u16 sub_808EC58_padding = 0;
