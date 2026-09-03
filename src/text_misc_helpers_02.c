#include "global.h"
#include "audio/sound_effects.h"

#define SEC(name)         __attribute__((section(".text.misc_helpers_02." #name)))
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;

extern int free_heap_8018DA8();
extern int heap_free_block();
extern int script_cmd_return();
extern int script_test_condition();
extern int sub_801ABE8();
extern int sub_8021308();
extern int sub_8027378();
extern int sub_8028F2C();
extern int sub_8028F40();
extern int sub_8029070();
extern int sub_80290CC();
extern int sub_8029170();
extern int sub_80291C8();
extern int sub_8029380();
extern int sub_803C508();
extern int sub_803C898();
extern int sub_803E9F0();
extern int sub_80475A0();
extern int sub_8050FD0();
extern int sub_805113C();
extern int sub_8058278();
extern int sub_80582DC();
extern int sub_80584F8();
extern int sub_80587BC();
extern int sub_8059F24();
extern int sub_805DEDC();
extern int sub_805F6BC();
extern int sub_805FF80();
extern int sub_80605A4();
extern int sub_80613FC();
extern int sub_8061480();
extern int sub_8062420();
extern int sub_8062E98();
extern int sub_8063384();
extern int sub_80633D0();
extern int sub_8063568();
extern int sub_8063C24();
extern int sub_80643DC();
extern int sub_8064424();
extern int sub_8064558();
extern int sub_8065384();
extern int sub_8065428();
extern int sub_8065494();
extern int sub_80659E0();
extern int sub_8065C5C();
extern int sub_8066DA4();
extern int sub_8066EE0();
extern int sub_806829C();
extern int sub_8068EF4();
extern int sub_806A3F8();
extern int sub_806A8B0();
extern int sub_806AA18();
extern int sub_806B56C();
extern int sub_806B824();
extern int sub_806F034();
extern int sub_8070938();
extern int sub_8070C5C();
extern int sub_8071080();
extern int sub_8071900();
extern int sub_807197C();
extern int sub_8072550();
extern int sub_80725D0();
extern int sub_8072944();
extern int sub_8072BE8();
extern int sub_80744B4();
extern int sub_8074508();
extern int sub_807470C();
extern int sub_80758BC();
extern int sub_8079C3C();
extern int sub_807B7A8();
extern int sub_807BDDC();
extern int sub_807C298();
extern int sub_807DC8C();
extern int sub_807FE40();
extern int sub_8080168();
extern int sub_8080A40();
extern int sub_8081288();
extern int sub_80813A0();
extern int sub_8082A28();
extern int sub_8082B00();
extern int sub_8082E1C();
extern int sub_80842D8();
extern int sub_8086C64();
extern int sub_8086D80();
extern int sub_8087124();
extern int sub_80871A8();
extern int sub_808750C();
extern int sub_8087540();
extern int sub_8087CE4();
extern int sub_80884AC();
extern int sub_808A5DC();
extern int sub_8099034();
extern int sub_80993C8();
extern int sub_80D9F34();
extern int sub_80D9F50();
extern int sub_80DB014();
extern int sub_80E57FC();
extern int sub_80E6FB8();
extern int sub_80E7118();
extern int sub_80FBDE0();
extern int sub_810B908();
extern int sub_810DD7C();
extern int sub_8111234();
extern int sub_81125CC();
extern int sub_8116620();
extern int sub_8120E90();
extern int sub_81218C8();
extern int sub_81218D4();
extern int sub_81219C4();
extern int sub_8199F30();
extern int sub_81DD77C();
s32 sub_80899C4(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80899E4(s32 arg0, s32 arg1, s32 arg2);
s32 sub_808A174(s32 arg0, s32 arg1, s32 arg2);
s32 sub_808A194(s32 arg0, s32 arg1, s32 arg2);
s32 sub_808A1B4(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80D909C(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80D90BC(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80DB184(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80DB1A4(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80DB1C4(s32 arg0, s32 arg1, s32 arg2);
void sub_80E8D74(void);
s32 sub_80F0704(void* arg0, void* arg1);
s32 sub_80F0724(void* arg0, void* arg1);
s32 sub_80FA6BC(void* arg0, void* arg1);
void sub_8065CA0(void* arg0);
void sub_8060464(void* arg0);
void sub_8060DC4(void* arg0);
void sub_80612D4(void* arg0);
void sub_8066864(void* arg0);
void sub_80706E8(void* arg0);
void sub_8072650(void* arg0);
void sub_8072500(void* arg0);
void sub_8072528(void* arg0);
void sub_8062134(void* arg0);
void sub_8075B54(void* arg0);
void sub_8097F10(void* arg0);
void sub_8098934(void* arg0);
void sub_80652B0(void* arg0);
void sub_806B400(void* arg0);
void sub_806B584(void* arg0);
void sub_808C42C(void* arg0);
void sub_810FE1C(void* arg0);
void sub_811108C(void* arg0);
void sub_81132AC(void* arg0);
void sub_8113E78(void* arg0);
void sub_809F068(void* arg0);
void sub_80D2D4C(void* arg0);
void sub_807FB64(s32 arg0);
s32 sub_80DBC3C(void* arg0);
void sub_80DBC60(void* arg0);
void sub_810CBC8(void);
s32 sub_80DE960(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80DE980(s32 arg0, s32 arg1, s32 arg2);
s32 sub_80DEB58(s32 arg0, s32 arg1, s32 arg2);
void sub_805DE90(void* arg0);
void sub_806B3AC(void* arg0);
void sub_8065B20(void* arg0);
void sub_806A814(void* arg0);
void sub_809E49C(void* arg0);
void sub_805DEB4(void* arg0);
void sub_805FF58(void* arg0);
void sub_80604B8(void* arg0);
void sub_8061458(void* arg0);
void sub_80623F8(void* arg0);
void sub_8062E70(void* arg0);
void sub_8063B58(void* arg0);
void sub_8064E08(void* arg0);
void sub_80653CC(void* arg0);
void sub_8065C34(void* arg0);
void sub_8066D50(void* arg0);
void sub_8067A24(void* arg0);
void sub_8068274(void* arg0);
void sub_806A8E0(void* arg0);
void sub_80A1A90(void* arg0);
void sub_80A2C58(void* arg0);
s32 sub_80DC3B8(void);
void sub_8087C4C(void* arg0);
s32 sub_8063B80(void* arg0);
void sub_80742D4(void* arg0);
void sub_8079BA8(void* arg0);
s32 sub_80EA8DC(UnknownWord arg0, void* arg1, void* arg2);
void sub_80E8EFC(s32* arg0, s32 arg1);
void sub_80F032C(void);
s32 sub_80632E4(void* arg0);
void sub_80801A0(void* arg0);
void sub_808759C(void* arg0);
void sub_80DA340(void* arg0);
void sub_80DD560(void* arg0);
void sub_80DDABC(void* arg0);
void sub_80DEA98(void* arg0);
void sub_80DEE80(void* arg0);
void sub_805FF30(void* arg0);
void sub_8068A28(void* arg0);
void sub_8082158(void* arg0);
s32 sub_806236C(void* arg0, s32 arg1);
s32 sub_806A7EC(void* arg0, s32 arg1);
void sub_807600C(void* arg0);
void sub_81126BC(void* arg0);
void sub_809E438(s32 arg0);
void sub_80DBC84(void* arg0);
void sub_80DAF84(void* arg0);
void sub_8070D60(void* arg0);
void sub_809F084(void* arg0);
s32 sub_80DA300(void* arg0);
void sub_808C1FC(void* arg0);
void sub_80E9484(void* arg0, s32 arg1);
void sub_8111214(void* arg0);
void sub_8081FB0(void* arg0);
void sub_80E8DC0(void);
void sub_8113E20(s32 arg0);
void sub_8059FE4(s32 arg0);

SEC(sub_80E8D74) void sub_80E8D74(void) {
    if (*(s32*)0x03000FBC != 0) {
        heap_free_block();
        *(s32*)0x03000FBC = 0;
    }
}

SEC(sub_80F0704) s32 sub_80F0704(void* arg0, void* arg1) {
    if ((sub_803C508(FIELD_AT(arg0, s32*, 0x14)) << 0x18) != 0) {
        FIELD_AT(arg1, s32*, 0) = (s32)FIELD_AT(arg1, s32*, 0x14);
        return 0;
    }
    return 1;
}

SEC(sub_80F0724) s32 sub_80F0724(void* arg0, void* arg1) {
    if ((sub_803E9F0(FIELD_AT(arg0, s32*, 0x14)) << 0x18) != 0) {
        FIELD_AT(arg1, s32*, 0) = (s32)FIELD_AT(arg1, s32*, 0x14);
        return 0;
    }
    return 1;
}

SEC(sub_80FA6BC) s32 sub_80FA6BC(void* arg0, void* arg1) {
    if ((sub_81219C4(FIELD_AT(arg0, s32*, 0x14)) << 0x18) != 0) {
        FIELD_AT(arg1, s32*, 0) = (s32)FIELD_AT(arg1, s32*, 0x14);
        return 0;
    }
    return 1;
}

SEC(sub_8065CA0) void sub_8065CA0(void* arg0) {
    sub_8082E1C(arg0, 2, 0, 0);
    FIELD_AT(FIELD_AT(arg0, void**, 8), s8*, 0x20) = 0x10;
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8065494;
}

SEC(sub_8060464) void sub_8060464(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 4, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80605A4;
    }
}

SEC(sub_8060DC4) void sub_8060DC4(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 9, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_80612D4) void sub_80612D4(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 7, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80613FC;
    }
}

SEC(sub_8066864) void sub_8066864(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_80706E8) void sub_80706E8(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 0x18, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8070C5C;
    }
}

SEC(sub_8072650) void sub_8072650(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_8082E1C(arg0, 0x16, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_807197C;
    }
}

SEC(sub_8072500) void sub_8072500(void* arg0) {
    sub_8082E1C(FIELD_AT(*(void**)0x03000FD8, s32*, 0x58) + 8, 0x2F, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8072550;
}

SEC(sub_8072528) void sub_8072528(void* arg0) {
    sub_8082E1C(FIELD_AT(*(void**)0x03000FD8, s32*, 0x58) + 8, 0x2F, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80725D0;
}

SEC(sub_8062134) void sub_8062134(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x30) != 0) {
        sub_807C298();
    }
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
}

SEC(sub_8075B54) void sub_8075B54(void* arg0) {
    s32 temp_r5;

    temp_r5 = FIELD_AT(arg0, s32*, 0x80);
    if (temp_r5 == 0) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, s32*, 0x4C) = temp_r5;
    }
}

SEC(sub_8097F10) void sub_8097F10(void* arg0) {
    void* temp_r1;
    void* temp_r4;

    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    temp_r4 = *FIELD_AT(FIELD_AT(temp_r1, void**, 4), void***, 8);
    if (temp_r4 == NULL) {
        sub_807C298(temp_r1);
        FIELD_AT(arg0, void**, 0x30) = temp_r4;
        FIELD_AT(arg0, void**, 0x4C) = temp_r4;
    }
}

SEC(sub_8098934) void sub_8098934(void* arg0) {
    void* temp_r1;
    void* temp_r4;

    temp_r1 = FIELD_AT(arg0, void**, 0x30);
    temp_r4 = *FIELD_AT(FIELD_AT(temp_r1, void**, 4), void***, 8);
    if (temp_r4 == NULL) {
        sub_807C298(temp_r1);
        FIELD_AT(arg0, void**, 0x30) = temp_r4;
        FIELD_AT(arg0, void**, 0x4C) = temp_r4;
    }
}

SEC(sub_80652B0) void sub_80652B0(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x30) == 0) {
        sub_8082E1C(arg0, 0, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    }
}

SEC(sub_806B400) void sub_806B400(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x30) == 0) {
        sub_8082E1C(arg0, 8, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806B56C;
    }
}

SEC(sub_806B584) void sub_806B584(void* arg0) {
    sub_8082E1C(arg0, 5, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806AA18;
    FIELD_AT(arg0, s16*, 0xAC) = 0;
}

SEC(sub_808C42C) void sub_808C42C(void* arg0) {
    FIELD_AT(arg0, s32*, 0x80) = 0;
    FIELD_AT((arg0 + 0x80), s16*, 0x2C) = 0;
    sub_8082E1C(arg0, 2, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808A5DC;
}

SEC(sub_810FE1C) void sub_810FE1C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_811108C) void sub_811108C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_81132AC) void sub_81132AC(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_8113E78) void sub_8113E78(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, -1, -1, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_809F068) void sub_809F068(void* arg0) {
    if (FIELD_AT(FIELD_AT(FIELD_AT(arg0, void**, 0x28), void**, 0x10), u8*, 0x21) == 0) {
        sub_807C298(arg0);
    }
}
SEC(sub_809F068) const u16 sub_809F068_padding = 0;

SEC(sub_80D2D4C) void sub_80D2D4C(void* arg0) {
    sub_80884AC();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_807FB64) void sub_807FB64(s32 arg0) {
    sub_807BDDC();
    sub_80842D8(arg0);
}

SEC(sub_80DBC3C) s32 sub_80DBC3C(void* arg0) {
    s32 temp_r0;

    FIELD_AT(arg0, UnknownWord**, 0x54) = (UnknownWord*)FIELD_AT(arg0, UnknownWord**, 0x4C);
    temp_r0 = sub_8086C64(arg0);
    if (temp_r0 == 0) {
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80DBC60;
    }
    return temp_r0;
}

SEC(sub_80DBC60) void sub_80DBC60(void* arg0) {
    if (FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x21) == 0) {
        sub_8082E1C(arg0, 2, 0, 0);
        FIELD_AT(arg0, s32*, 0x4C) = (s32)FIELD_AT(arg0, s32*, 0x54);
    }
}

SEC(sub_810CBC8) void sub_810CBC8(void) {
    sub_810B908(0);
    sub_810B908(1);
}
SEC(sub_810CBC8) const u16 sub_810CBC8_padding = 0;

SEC(sub_805DE90) void sub_805DE90(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_805DEB4;
        sound_effect_stop(0x11B);
    }
}

SEC(sub_806B3AC) void sub_806B3AC(void* arg0) {
    s32 temp_r1;

    temp_r1 = FIELD_AT(arg0, s32*, 0x10) - FIELD_AT(arg0, s32*, 0x9C);
    FIELD_AT(arg0, s32*, 0x10) = temp_r1;
    if (temp_r1 <= (s32)FIELD_AT(arg0, s32*, 0x84)) {
        sub_807C298(arg0);
    }
}
SEC(sub_806B3AC) const u16 sub_806B3AC_padding = 0;

SEC(sub_8065B20) void sub_8065B20(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sub_807C298(FIELD_AT(arg0, s32*, 0x30));
        FIELD_AT(arg0, s16*, 0xAC) = 3;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8065C5C;
    }
}

SEC(sub_806A814) void sub_806A814(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x81);
        FIELD_AT(arg0, s16*, 0xAC) = 0xFF;
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_806A8B0;
    }
}

SEC(sub_809E49C) void sub_809E49C(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, -1, 0);
        FIELD_AT(arg0, s32*, 0x4C) = 0;
    }
}

SEC(sub_80A1A90) void sub_80A1A90(void* arg0) {
    sub_8087CE4();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        FIELD_AT(arg0, s32*, 0x4C) = 0;
        FIELD_AT(arg0, s8*, 0x74) = 0;
    }
}
SEC(sub_80A1A90) const u16 sub_80A1A90_padding = 0;

SEC(sub_80A2C58) void sub_80A2C58(void* arg0) {
    sub_8087CE4();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        FIELD_AT(arg0, s32*, 0x4C) = 0;
        FIELD_AT(arg0, s8*, 0x74) = 0;
    }
}
SEC(sub_80A2C58) const u16 sub_80A2C58_padding = 0;

SEC(sub_8087C4C) void sub_8087C4C(void* arg0) {
    UnknownWord (*temp_r1)(void*);
    s32 temp_r5;

    temp_r5 = FIELD_AT(arg0, s32*, 0x80);
    if (temp_r5 == 0) {
        temp_r1 = FIELD_AT(arg0, UnknownWord(**)(void*), 0x68);
        if (temp_r1 != NULL) {
            temp_r1(arg0);
        }
        FIELD_AT(arg0, s32*, 0x6C) = temp_r5;
    }
}

SEC(sub_8063B80) s32 sub_8063B80(void* arg0) {
    s32 temp_r0;

    temp_r0 = sub_8086C64();
    if (temp_r0 == 0) {
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8063C24;
        FIELD_AT(arg0, s32*, 0x84) = 0x10;
    }
    return temp_r0;
}

SEC(sub_80742D4) void sub_80742D4(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_play(0x10E, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8072BE8;
    }
}

SEC(sub_8079BA8) void sub_8079BA8(void* arg0) {
    if (FIELD_AT(FIELD_AT(arg0, void**, 0x30), s32*, 0x4C) == 0) {
        sub_8082E1C(arg0, 0x12, 0, 0);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8079C3C;
    }
}

SEC(sub_80EA8DC) s32 sub_80EA8DC(UnknownWord arg0, void* arg1, void* arg2) {
    if ((script_test_condition(arg0, FIELD_AT(arg2, u8*, 0), FIELD_AT(arg2, s32*, 4),
                               FIELD_AT(arg1, s32*, 0x98))
         << 0x18)
        != 0) {
        FIELD_AT(arg1, s32*, 0) = (s32)FIELD_AT(arg2, s32*, 8);
    }
    return 1;
}
SEC(sub_80EA8DC) const u16 sub_80EA8DC_padding = 0;

SEC(sub_80E8EFC) void sub_80E8EFC(s32* arg0, s32 arg1) {
    heap_free_block(*arg0);
    if (1 & arg1) {
        free_heap_8018DA8(arg0);
    }
}

SEC(sub_80F032C) void sub_80F032C(void) {
    sub_80E6FB8(*(s32*)0x03000FCC, 4);
    sub_80E7118(*(s32*)0x03000FCC, 0x10);
}

SEC(sub_80632E4) s32 sub_80632E4(void* arg0) {
    sub_810DD7C(arg0, FIELD_AT(arg0, s32*, 0x2C), 0xFF);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80633D0;
    sound_effect_stop(0x11C);
    return 0;
}

SEC(sub_80801A0) void sub_80801A0(void* arg0) {
    if ((sub_8080168(FIELD_AT(arg0, s32*, 8)) << 0x18) == 0) {
        sub_807DC8C(arg0);
    }
}

SEC(sub_808759C) void sub_808759C(void* arg0) {
    if (sub_8082B00() == 0) {
        FIELD_AT(FIELD_AT(arg0, void**, 0x6C), UnknownWord(**)(void*), 4)(arg0);
    }
}

SEC(sub_80DA340) void sub_80DA340(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 6, 0, 0);
        sub_8087540(arg0);
    }
}

SEC(sub_80DD560) void sub_80DD560(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        sub_8087540(arg0);
    }
}

SEC(sub_80DDABC) void sub_80DDABC(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        sub_8087540(arg0);
    }
}

SEC(sub_80DEA98) void sub_80DEA98(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        sub_8087540(arg0);
    }
}

SEC(sub_80DEE80) void sub_80DEE80(void* arg0) {
    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        sub_8087540(arg0);
    }
}

SEC(sub_805FF30) void sub_805FF30(void* arg0) {
    UnknownWord (*temp_r1)(void*);

    if (8 & FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12)) {
        temp_r1 = FIELD_AT(arg0, UnknownWord(**)(void*), 0x68);
        if (temp_r1 != NULL) {
            temp_r1(arg0);
        }
        FIELD_AT(arg0, s32*, 0x6C) = 0;
    }
}
SEC(sub_805FF30) const u16 sub_805FF30_padding = 0;

SEC(sub_8068A28) void sub_8068A28(void* arg0) {
    s32 temp_r2;
    s32 var_r0;

    temp_r2 = FIELD_AT(arg0, s32*, 0x10);
    var_r0 = temp_r2 + 0x200;
    FIELD_AT(arg0, s32*, 0x10) = var_r0;
    if (var_r0 < 0) {
        var_r0 = temp_r2 + 0x2FF;
    }
    if ((s32)(var_r0 >> 8) > 0xFF) {
        sub_807C298(arg0);
    }
}
SEC(sub_8068A28) const u16 sub_8068A28_padding = 0;

SEC(sub_8082158) void sub_8082158(void* arg0) {
    UnknownWord (*temp_r1)(void*);
    void* temp_r4;

    temp_r4 = FIELD_AT(arg0, void**, 0xC);
    temp_r1 = FIELD_AT(temp_r4, UnknownWord(**)(void*), 0x4C);
    if ((temp_r1 == NULL)
        || (temp_r1(temp_r4), (FIELD_AT(temp_r4, UnknownWord(**)(void*), 0x4C) == NULL))) {
        FIELD_AT(arg0, UnknownWord**, 4) = (UnknownWord*)&sub_8080A40;
    }
}

SEC(sub_806236C) s32 sub_806236C(void* arg0, s32 arg1) {
    sound_effect_stop(0x81);
    sub_810DD7C(arg0, arg1, 0xFF);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    return 0;
}

SEC(sub_806A7EC) s32 sub_806A7EC(void* arg0, s32 arg1) {
    sound_effect_stop(0x81);
    sub_810DD7C(arg0, arg1, 0xFF);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_808750C;
    return 0;
}

SEC(sub_807600C) void sub_807600C(void* arg0) {
    sub_8082E1C(arg0, 0xA, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80758BC;
    sound_effect_play(0xAF, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_81126BC) void sub_81126BC(void* arg0) {
    sub_8082E1C(arg0, 9, 0, 0);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8111234;
    sound_effect_play(0x86, SOUND_VOLUME_UNCHANGED);
}

SEC(sub_809E438) void sub_809E438(s32 arg0) {
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_807C298(arg0);
    }
}
SEC(sub_809E438) const u16 sub_809E438_padding = 0;

SEC(sub_80DBC84) void sub_80DBC84(void* arg0) {
    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x11A);
        sub_8087540(arg0);
    }
}

SEC(sub_80DAF84) void sub_80DAF84(void* arg0) {
    if (sub_8082B00() == 0) {
        sound_effect_play(0x8D, SOUND_VOLUME_UNCHANGED);
        FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_80DB014;
    }
}

SEC(sub_8070D60) void sub_8070D60(void* arg0) {
    sub_8082E1C(arg0, 5, 0, 0);
    sound_effect_play(0x46, SOUND_VOLUME_UNCHANGED);
    FIELD_AT(arg0, UnknownWord**, 0x4C) = (UnknownWord*)&sub_8071080;
}

SEC(sub_809F084) void sub_809F084(void* arg0) {
    sub_8087CE4();
    if (0x20 & FIELD_AT(arg0, u8*, 0x79)) {
        sub_807C298(arg0);
    }
}
SEC(sub_809F084) const u16 sub_809F084_padding = 0;

SEC(sub_80DA300) s32 sub_80DA300(void* arg0) {
    s32 temp_r0;
    s32 temp_r5;

    temp_r5 = FIELD_AT(arg0, s32*, 0x28) + 8;
    temp_r0 = sub_8087124(temp_r5);
    if (temp_r0 == 0) {
        sub_80D9F34(temp_r5);
    }
    return temp_r0;
}
SEC(sub_80DA300) const u16 sub_80DA300_padding = 0;

SEC(sub_808C1FC) void sub_808C1FC(void* arg0) {
    void* temp_r0;

    if (FIELD_AT(arg0, s32*, 0x80) == 0) {
        sound_effect_stop(0x6C);
        temp_r0 = FIELD_AT(arg0, void**, 8);
        FIELD_AT(temp_r0, u8*, 0x11) = (u8)(FIELD_AT(temp_r0, u8*, 0x11) | 0x40);
        sub_8087540(arg0);
    }
}

SEC(sub_80E9484) void sub_80E9484(void* arg0, s32 arg1) {
    if (FIELD_AT(arg0, s32*, 0xC) != 0) {
        heap_free_block();
        FIELD_AT(arg0, s32*, 0xC) = 0;
    }
    if (1 & arg1) {
        free_heap_8018DA8(arg0);
    }
}

SEC(sub_8111214) void sub_8111214(void* arg0) {
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_807C298(FIELD_AT(arg0, void**, 0x30));
        sub_807C298(arg0);
    }
}

SEC(sub_8081FB0) void sub_8081FB0(void* arg0) {
    if ((sub_8082B00() << 0x18) == 0) {
        sub_8082A28();
        sub_80813A0();
        FIELD_AT(arg0, UnknownWord**, 4) = (UnknownWord*)&sub_8081288;
    }
}

SEC(sub_80E8DC0) void sub_80E8DC0(void) {
    sub_80E57FC();
    if (*(s32*)0x03000FB8 != 0) {
        heap_free_block();
        *(s32*)0x03000FB8 = 0;
    }
    sub_80E8D74();
}

SEC(sub_8113E20) void sub_8113E20(s32 arg0) {
    if ((sub_8087CE4() << 0x18) == 0) {
        sub_807C298(arg0);
        sound_effect_stop(0x10C);
    }
}
SEC(sub_8113E20) const u16 sub_8113E20_padding = 0;

SEC(sub_8059FE4) void sub_8059FE4(s32 arg0) {
    sub_8059F24();
    sub_80582DC(arg0);
    sub_80587BC(arg0, 0);
    sub_8058278(arg0);
    sub_80584F8(arg0);
}
