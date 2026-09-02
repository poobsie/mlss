#include "global.h"

#define SEC(name) __attribute__((section(".text.expand0902." #name)))
#define M2C_FIELD(p, t, o) (*(t)((u8 *)(p) + (o)))
typedef u32 M2C_UNK;

extern int free_heap_memory_8018C68();
extern int stop_sfx_80195A8();
extern int sub_801B0AC();
extern int sub_8047364();
extern int sub_80473DC();
extern int sub_8047E50();
extern int sub_805A99C();
extern int sub_805B490();
extern int sub_805B618();
extern int sub_805C78C();
extern int sub_805C7B4();
extern int sub_806123C();
extern int sub_8065EA0();
extern int sub_8065ED4();
extern int sub_8067A4C();
extern int sub_80681EC();
extern int sub_8068B68();
extern int sub_806A2FC();
extern int sub_806A638();
extern int sub_806B3D0();
extern int sub_806B7BC();
extern int sub_806CD70();
extern int sub_8070534();
extern int sub_8071B14();
extern int sub_80722F8();
extern int sub_8075C8C();
extern int sub_807940C();
extern int sub_807C298();
extern int sub_807D2D0();
extern int sub_807F4FC();
extern int sub_8081F84();
extern int sub_8082E1C();
extern int sub_8086C64();
extern int sub_80873B8();
extern int sub_80874B4();
extern int sub_808750C();
extern int sub_8087540();
extern int sub_8088164();
extern int sub_80886BC();
extern int sub_80886E0();
extern int sub_808942C();
extern int sub_808B2D4();
extern int sub_808C348();
extern int sub_808C62C();
extern int sub_808C65C();
extern int sub_808C68C();
extern int sub_808C6BC();
extern int sub_808C724();
extern int sub_809CA24();
extern int sub_809D2A8();
extern int sub_809EA4C();
extern int sub_80A2BC0();
extern int sub_80DA480();
extern int sub_8104D14();
extern int sub_810B680();
extern int sub_810CA30();
extern int sub_810DD7C();
extern int sub_8110034();
extern int sub_8111CA8();
extern int sub_811458C();
extern int sub_81165CC();
extern int sub_8116610();
void sub_805A954(void *arg0, s16 arg1, s16 arg2);
void sub_805CCD8(void *arg0);
void sub_805F5E4(void *arg0);
void sub_80605A4(void *arg0);
s32 sub_80612B4(void *arg0);
void sub_806424C(void *arg0);
void sub_8064540(void *arg0);
void sub_8065E2C(void *arg0);
void sub_8065E4C(void *arg0);
void sub_80679FC(void *arg0);
s32 sub_8068058(void *arg0);
void sub_806814C(void *arg0);
void sub_8068C70(void *arg0);
s32 sub_8068E60(void *arg0);
void sub_8068EF4(void *arg0);
s32 sub_806A1E8(void *arg0);
void sub_806A22C(void *arg0);
s32 sub_806A760(void *arg0);
void sub_806A77C(void *arg0);
s32 sub_806B288(void *arg0);
void sub_806B318(void *arg0);
s32 sub_806B390(void *arg0);
void sub_806B528(void *arg0);
void sub_806B56C(void *arg0);
void sub_806C190(void *arg0);
void sub_806C1A8(void *arg0);
s32 sub_806C8C0(void *arg0, M2C_UNK arg1);
s32 sub_806D340(void *arg0, M2C_UNK arg1);
void sub_806E754(void *arg0);
void sub_8070510(void *arg0);
void sub_8070C5C(void *arg0);
void sub_8070C84(void *arg0);
void sub_8070EDC(void *arg0);
void sub_8072370(void *arg0);
void sub_80743AC(void *arg0);
void sub_80746C4(void *arg0);
void sub_8075BE8(void *arg0);
s32 sub_8075C48(void *arg0, M2C_UNK arg1);
void sub_8075C64(void *arg0);
void sub_8077094(void *arg0);
void sub_8077118(void *arg0);
void sub_80771D8(void *arg0);
void sub_8079320(void *arg0);
void sub_80793F4(void *arg0);
void sub_8079704(void *arg0);
void sub_807F6D0(void);
void sub_807F6EC(s32 arg0);
void sub_8081C54(void *arg0);
void sub_8082D00(void *arg0, s32 arg1, s32 arg2);
void sub_8082D24(void *arg0, s16 arg1, s16 arg2);
s8 sub_8083E78(void *arg0);
void sub_8087524(void *arg0);
void sub_808862C(void *arg0);
void sub_808863C(void *arg0);
void sub_8089AB0(void *arg0);
void sub_8089AC8(void *arg0);
void sub_808A098(void *arg0);
s32 sub_808C064(void *arg0);
s32 sub_808C190(void *arg0);
void sub_808C324(void *arg0);
void sub_808C39C(void *arg0);
void sub_808C3C0(void *arg0);
void sub_808C3E4(void *arg0);
void sub_808C408(void *arg0);
void sub_808C4C8(void *arg0);
void sub_808DCDC(void *arg0);
void sub_808E0C8(void *arg0);
void sub_808F0D8(void *arg0);
void sub_8090378(void *arg0);
void sub_80906E4(void *arg0);
void sub_8090A50(void *arg0);
void sub_8090E4C(void *arg0);
void sub_8091FDC(void *arg0);
void sub_809316C(void *arg0);
void sub_80942F8(void *arg0);
void sub_8094750(void *arg0);
void sub_8094BA8(void *arg0);
void sub_8095000(void *arg0);
void sub_809C954(void *arg0);
void sub_809CAC8(void *arg0);
s32 sub_809D268(void *arg0);
void sub_809EB58(void *arg0);
void sub_809EB70(void *arg0);
void sub_80A0788(void *arg0);
void sub_80A07B0(void *arg0);
void sub_80D2D34(void);
void sub_80DA45C(void *arg0);
void sub_80DAF30(void *arg0);
void sub_80DAF6C(void *arg0);
void sub_80DC4C0(void *arg0);
void sub_80E57FC(void);
void sub_80E9AF8(void);
void sub_80E9D04(void);
void sub_8106A10(void *arg0);
void sub_810CCB0(void);
void sub_810FEF4(void *arg0);
void sub_81109D0(void *arg0);
void sub_8112064(void *arg0);
void sub_8114790(void *arg0);
void sub_81147B4(void *arg0);

SEC(sub_805A954) void sub_805A954(void *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0x20) = arg1;
    M2C_FIELD(arg0, s16 *, 0x22) = arg2;
}
SEC(sub_805A954) const u16 sub_805A954_padding = 0;

SEC(sub_805CCD8) void sub_805CCD8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
}
SEC(sub_805CCD8) const u16 sub_805CCD8_padding = 0;

SEC(sub_805F5E4) void sub_805F5E4(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0xA0) - 1;
    M2C_FIELD(arg0, s32 *, 0xA0) = temp_r0;
    if (temp_r0 < 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
    }
}

SEC(sub_80605A4) void sub_80605A4(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_80605A4) const u16 sub_80605A4_padding = 0;

SEC(sub_80612B4) s32 sub_80612B4(void *arg0) {
    sub_810DD7C();
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806123C;
    return 0;
}

SEC(sub_806424C) void sub_806424C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_806424C) const u16 sub_806424C_padding = 0;

SEC(sub_8064540) void sub_8064540(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8065E2C) void sub_8065E2C(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 0x14;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8065EA0;
    }
}

SEC(sub_8065E4C) void sub_8065E4C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8065ED4;
    }
}

SEC(sub_80679FC) void sub_80679FC(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x84) - 1;
    M2C_FIELD(arg0, s32 *, 0x84) = temp_r0;
    if (temp_r0 <= 0) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0x300;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8067A4C;
    }
}

SEC(sub_8068058) s32 sub_8068058(void *arg0) {
    sub_810DD7C(arg0, M2C_FIELD(arg0, s32 *, 0x2C), 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_80681EC;
    return 0;
}

SEC(sub_806814C) void sub_806814C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
    }
}

SEC(sub_8068C70) void sub_8068C70(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8068C70) const u16 sub_8068C70_padding = 0;

SEC(sub_8068E60) s32 sub_8068E60(void *arg0) {
    sub_810DD7C(arg0, M2C_FIELD(arg0, s32 *, 0x2C), 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8068B68;
    return 0;
}

SEC(sub_8068EF4) void sub_8068EF4(void *arg0) {
    stop_sfx_80195A8(0x11A);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
}

SEC(sub_806A1E8) s32 sub_806A1E8(void *arg0) {
    sub_810DD7C(arg0, M2C_FIELD(arg0, s32 *, 0x2C), 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806A22C;
    return 0;
}

SEC(sub_806A22C) void sub_806A22C(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 0xC;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806A2FC;
    }
}

SEC(sub_806A760) s32 sub_806A760(void *arg0) {
    sub_810DD7C(arg0, M2C_FIELD(arg0, s32 *, 0x2C), 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806A638;
    return 0;
}

SEC(sub_806A77C) void sub_806A77C(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x18) + 0xFFFFFE00;
    M2C_FIELD(arg0, s32 *, 0x18) = temp_r0;
    if (temp_r0 <= 0) {
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
    }
}

SEC(sub_806B288) s32 sub_806B288(void *arg0) {
    sub_810DD7C(arg0, M2C_FIELD(arg0, s32 *, 0x2C), 0xFF);
    return 0;
}

SEC(sub_806B318) void sub_806B318(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_806B318) const u16 sub_806B318_padding = 0;

SEC(sub_806B390) s32 sub_806B390(void *arg0) {
    sub_810DD7C(arg0, M2C_FIELD(arg0, s32 *, 0x2C), 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806B3D0;
    return 0;
}

SEC(sub_806B528) void sub_806B528(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        sub_807C298(arg0);
    }
}
SEC(sub_806B528) const u16 sub_806B528_padding = 0;

SEC(sub_806B56C) void sub_806B56C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_806C190) void sub_806C190(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        sub_807C298(arg0);
    }
}
SEC(sub_806C190) const u16 sub_806C190_padding = 0;

SEC(sub_806C1A8) void sub_806C1A8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 8;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806B7BC;
    }
}

SEC(sub_806C8C0) s32 sub_806C8C0(void *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, s32 *, 0x9C) = 1;
    sub_810DD7C(arg0, arg1, 0xFF);
    return 0;
}
SEC(sub_806C8C0) const u16 sub_806C8C0_padding = 0;

SEC(sub_806D340) s32 sub_806D340(void *arg0, M2C_UNK arg1) {
    sub_810DD7C(arg0, arg1, 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_806CD70;
    return 0;
}

SEC(sub_806E754) void sub_806E754(void *arg0) {
    s32 temp_r0;
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0x30);
    M2C_FIELD(temp_r2, s32 *, 0x10) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(temp_r2, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s32 *, 0x14);
    M2C_FIELD(temp_r2, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
    temp_r0 = M2C_FIELD(arg0, s32 *, 0x80);
    if (temp_r0 == 0) {
        M2C_FIELD(arg0, s32 *, 0x4C) = temp_r0;
        M2C_FIELD(temp_r2, s32 *, 0x4C) = temp_r0;
    }
}

SEC(sub_8070510) void sub_8070510(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        M2C_FIELD(arg0, s32 *, 0xA8) = (s32) (M2C_FIELD(arg0, s32 *, 0xA8) + 1);
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8070534;
    }
}

SEC(sub_8070C5C) void sub_8070C5C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8070C5C) const u16 sub_8070C5C_padding = 0;

SEC(sub_8070C84) void sub_8070C84(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
}
SEC(sub_8070C84) const u16 sub_8070C84_padding = 0;

SEC(sub_8070EDC) void sub_8070EDC(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8070EDC) const u16 sub_8070EDC_padding = 0;

SEC(sub_8072370) void sub_8072370(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 0x1E;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8071B14;
    }
}

SEC(sub_80743AC) void sub_80743AC(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        sub_807C298(arg0);
    }
}
SEC(sub_80743AC) const u16 sub_80743AC_padding = 0;

SEC(sub_80746C4) void sub_80746C4(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_80746C4) const u16 sub_80746C4_padding = 0;

SEC(sub_8075BE8) void sub_8075BE8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8075BE8) const u16 sub_8075BE8_padding = 0;

SEC(sub_8075C48) s32 sub_8075C48(void *arg0, M2C_UNK arg1) {
    sub_810DD7C(arg0, arg1, 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8075C8C;
    return 0;
}

SEC(sub_8075C64) void sub_8075C64(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8075C64) const u16 sub_8075C64_padding = 0;

SEC(sub_8077094) void sub_8077094(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8077094) const u16 sub_8077094_padding = 0;

SEC(sub_8077118) void sub_8077118(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8077118) const u16 sub_8077118_padding = 0;

SEC(sub_80771D8) void sub_80771D8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_80771D8) const u16 sub_80771D8_padding = 0;

SEC(sub_8079320) void sub_8079320(void *arg0) {
    s32 temp_r0;
    void *temp_r2;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x80);
    if (temp_r0 == 0) {
        M2C_FIELD(arg0, s32 *, 0x4C) = temp_r0;
        temp_r2 = M2C_FIELD(arg0, void **, 0x28);
        M2C_FIELD(temp_r2, s32 *, 0xA4) = 2;
        M2C_FIELD(temp_r2, s8 *, 0x113) = 2;
    }
}

SEC(sub_80793F4) void sub_80793F4(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_807940C;
    }
}

SEC(sub_8079704) void sub_8079704(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_8079704) const u16 sub_8079704_padding = 0;

SEC(sub_807F6D0) void sub_807F6D0(void) {
    sub_8116610(M2C_FIELD(*(void **)0x03000FD8, s32 *, 0x248));
}

SEC(sub_807F6EC) void sub_807F6EC(s32 arg0) {
    sub_81165CC(M2C_FIELD(*(void **)0x03000FD8, s32 *, 0x248), arg0);
}

SEC(sub_8081C54) void sub_8081C54(void *arg0) {
    if (!(1 & M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0x28), u8 *, 0x111))) {
        M2C_FIELD(arg0, M2C_UNK **, 4) = (M2C_UNK *)&sub_8081F84;
    }
}

SEC(sub_8082D00) void sub_8082D00(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, u16 *, 0x778) = (u16) (M2C_FIELD(arg0, u16 *, 0x778) + arg1);
    M2C_FIELD(arg0, u16 *, 0x77A) = (u16) (M2C_FIELD(arg0, u16 *, 0x77A) + arg2);
}

SEC(sub_8082D24) void sub_8082D24(void *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0x778) = arg1;
    M2C_FIELD(arg0, s16 *, 0x77A) = arg2;
}

SEC(sub_8083E78) s8 sub_8083E78(void *arg0) {
    return (s8) M2C_FIELD(M2C_FIELD(arg0, void **, 0xE4), u8 *, 6);
}

SEC(sub_8087524) void sub_8087524(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x21) == 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_80874B4;
    }
}

SEC(sub_808862C) void sub_808862C(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *) M2C_FIELD(arg0, M2C_UNK **, 0x4C);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_80886BC;
}

SEC(sub_808863C) void sub_808863C(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *) M2C_FIELD(arg0, M2C_UNK **, 0x4C);
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_80886E0;
}

SEC(sub_8089AB0) void sub_8089AB0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808942C;
    M2C_FIELD(arg0, s16 *, 0xAC) = 0;
}

SEC(sub_8089AC8) void sub_8089AC8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
    }
}

SEC(sub_808A098) void sub_808A098(void *arg0) {
    sub_807F4FC();
    M2C_FIELD(arg0, s32 *, 0x4C) = 0x0808A201;
}

SEC(sub_808C064) s32 sub_808C064(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808C348;
    return 1;
}

SEC(sub_808C190) s32 sub_808C190(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808C4C8;
    return 1;
}

SEC(sub_808C324) void sub_808C324(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAC) = 0xC;
    sub_80873B8(arg0, 2, 0xC);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *)&sub_808B2D4;
}

SEC(sub_808C39C) void sub_808C39C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAC) = 5;
    sub_80873B8(arg0, 6, 5);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *)&sub_808C62C;
}

SEC(sub_808C3C0) void sub_808C3C0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAC) = 5;
    sub_80873B8(arg0, 2, 5);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *)&sub_808C65C;
}

SEC(sub_808C3E4) void sub_808C3E4(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAC) = 5;
    sub_80873B8(arg0, 6, 5);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *)&sub_808C68C;
}

SEC(sub_808C408) void sub_808C408(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAC) = 5;
    sub_80873B8(arg0, 2, 5);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *)&sub_808C6BC;
}

SEC(sub_808C4C8) void sub_808C4C8(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAC) = 3;
    sub_80873B8(arg0, 7, 3);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = (M2C_UNK *)&sub_808C724;
}

SEC(sub_808DCDC) void sub_808DCDC(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_808E0C8) void sub_808E0C8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_808F0D8) void sub_808F0D8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8090378) void sub_8090378(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_80906E4) void sub_80906E4(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8090A50) void sub_8090A50(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8090E4C) void sub_8090E4C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8091FDC) void sub_8091FDC(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_809316C) void sub_809316C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_80942F8) void sub_80942F8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8094750) void sub_8094750(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8094BA8) void sub_8094BA8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_8095000) void sub_8095000(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0x2000, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}

SEC(sub_809C954) void sub_809C954(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_809CA24;
}

SEC(sub_809CAC8) void sub_809CAC8(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_809CAC8) const u16 sub_809CAC8_padding = 0;

SEC(sub_809D268) s32 sub_809D268(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_809D2A8;
    return 1;
}

SEC(sub_809EB58) void sub_809EB58(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_809EA4C;
    M2C_FIELD(arg0, s16 *, 0xAC) = 0;
}

SEC(sub_809EB70) void sub_809EB70(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
    }
}

SEC(sub_80A0788) void sub_80A0788(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_80A0788) const u16 sub_80A0788_padding = 0;

SEC(sub_80A07B0) void sub_80A07B0(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        sub_8082E1C(arg0, 0, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    }
}
SEC(sub_80A07B0) const u16 sub_80A07B0_padding = 0;

SEC(sub_80D2D34) void sub_80D2D34(void) {
    sub_807C298(M2C_FIELD(M2C_FIELD(*(void **)0x03000FD8, void **, 0x70), s32 *, 0x38));
}

SEC(sub_80DA45C) void sub_80DA45C(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 0;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_80DA480;
    }
}

SEC(sub_80DAF30) void sub_80DAF30(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        sub_8087540(arg0);
    }
}
SEC(sub_80DAF30) const u16 sub_80DAF30_padding = 0;

SEC(sub_80DAF6C) void sub_80DAF6C(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        sub_8087540(arg0);
    }
}
SEC(sub_80DAF6C) const u16 sub_80DAF6C_padding = 0;

SEC(sub_80DC4C0) void sub_80DC4C0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x80) == 0) {
        sub_8087540(arg0);
    }
}
SEC(sub_80DC4C0) const u16 sub_80DC4C0_padding = 0;

SEC(sub_80E57FC) void sub_80E57FC(void) {
    free_heap_memory_8018C68(*(s32 *)0x03000FB4);
}

SEC(sub_80E9AF8) void sub_80E9AF8(void) {
    free_heap_memory_8018C68(*(s32 *)0x03000FC4);
}

SEC(sub_80E9D04) void sub_80E9D04(void) {
    free_heap_memory_8018C68(*(s32 *)0x03000FC0);
    *(s32 *)0x03000FC0 = 0;
}

SEC(sub_8106A10) void sub_8106A10(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), void **, 0x10), u8 *, 0x12)) {
        M2C_FIELD(arg0, M2C_UNK **, 4) = (M2C_UNK *)&sub_8104D14;
    }
}

SEC(sub_810CCB0) void sub_810CCB0(void) {
    M2C_FIELD(sub_807D2D0(&sub_810B680, 0x86, 0), s16 *, 0x14) = 0;
}

SEC(sub_810FEF4) void sub_810FEF4(void *arg0) {
    if (8 & M2C_FIELD(M2C_FIELD(arg0, void **, 8), u8 *, 0x12)) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 0xC;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8110034;
    }
}

SEC(sub_81109D0) void sub_81109D0(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x18) + 0xFFFFFE00;
    M2C_FIELD(arg0, s32 *, 0x18) = temp_r0;
    if (temp_r0 <= 0) {
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_808750C;
    }
}

SEC(sub_8112064) void sub_8112064(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), u8 *, 0x113) == 0) {
        M2C_FIELD(arg0, s16 *, 0xAC) = 0x10;
        M2C_FIELD(arg0, M2C_UNK **, 0x4C) = (M2C_UNK *)&sub_8111CA8;
    }
}

SEC(sub_8114790) void sub_8114790(void *arg0) {
    s32 temp_r2;

    temp_r2 = 0x38 & M2C_FIELD(arg0, u8 *, 0x76);
    if (temp_r2 == 0) {
        M2C_FIELD(arg0, s32 *, 0x4C) = temp_r2;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), void **, 0x28), s8 *, 0x113) = (s8) temp_r2;
    }
}

SEC(sub_81147B4) void sub_81147B4(void *arg0) {
    sub_811458C();
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), s8 *, 0x113) = 0;
}
