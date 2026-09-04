#include "object/action_factory.h"

#define SEC(name) __attribute__((section(".text.text_upper_helpers." #name)))

extern void sub_81728A4(void);
extern void sub_8172C2C(void);
extern void sub_8173004(void);
extern void sub_81733E4(void);
extern void sub_81736C0(void);
extern void sub_81743E4(void);
extern void sub_8174E9C(void);
extern void sub_817518C(void);
extern void sub_817547C(void);
extern void sub_8175768(void);
extern void sub_81744FC(void);
extern void sub_817399C(void);
extern void sub_8173104(void);
extern void sub_81729C4(void);
extern void sub_81723C0(void);
extern void sub_81881E0(void);
extern void sub_81873FC(void);
extern void sub_8185B40(void);
extern void sub_8185054(void);
extern void sub_8184654(void);
extern void sub_81829EC(void);
extern void sub_8180BE4(void);
extern void sub_817E608(void);
extern void sub_817C8BC(void);
extern void sub_817B980(void);
extern void sub_817A84C(void);
extern void sub_817A00C(void);
extern void sub_81798C8(void);
extern void sub_8178038(void);
extern void sub_81773F8(void);
extern void sub_818353C(void);
extern void sub_8183338(void);
extern void sub_8183134(void);
extern void sub_8183008(void);
extern void sub_8182EDC(void);
extern void sub_8183740(void);
extern void sub_818386C(void);
extern void sub_8183AF8(void);
extern void sub_8183D84(void);
extern void sub_8184010(void);
extern void sub_818429C(void);
extern void sub_8184528(void);
extern void sub_818475C(void);
extern void sub_8184CF4(void);
extern void sub_8184E14(void);
extern void sub_8184F34(void);
extern void sub_81858C4(void);
extern void sub_8185A00(void);
extern void sub_81866E4(void);
extern void sub_8186864(void);
extern void sub_81869C0(void);
extern void sub_8186F7C(void);
extern void sub_81870FC(void);
extern void sub_818727C(void);
extern void sub_8187E24(void);

#define DEFINE_OBJECT_ACTION_FACTORY(name, event_id, callback, visual_id, visual_variant, path_mode, \
                                     point_count, point_data, trailing_point_count)                  \
    SEC(name) void name(u32 coordinate0, u32 coordinate1, u32 coordinate2, u32 orientation) {        \
        object_create_scripted_action(                                                                \
            coordinate0, coordinate1, coordinate2, event_id, callback, visual_id, visual_variant,   \
            path_mode, point_count, orientation, orientation, point_data, trailing_point_count);     \
    }

#define DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(                                                     \
    name, event_id, callback, visual_id, visual_variant, path_mode, point_count,                     \
    object_orientation, visual_orientation, point_data, trailing_point_count)                        \
    SEC(name) void name(u32 coordinate0, u32 coordinate1, u32 coordinate2, u32 orientation) {        \
        object_create_scripted_action(                                                                \
            coordinate0, coordinate1, coordinate2, event_id, callback, visual_id, visual_variant,   \
            path_mode, point_count, object_orientation, visual_orientation, point_data,              \
            trailing_point_count);                                                                    \
    }

DEFINE_OBJECT_ACTION_FACTORY(sub_81768D0, 0, sub_817547C, 0x0000207D, 7, 0, 5, (void*)0x08504884, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_817690C, 0, sub_817518C, 0x0000207D, 7, 0, 5, (void*)0x08504870, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176948, 0, sub_8174E9C, 0x0000207D, 2, 0, 5, (void*)0x0850485C, 5)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_8175768, 0, sub_8175768, 0x00002080, 1, 0, 5, (void*)0x08504898, 5)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_81744FC, 0, sub_81744FC, 0x00002080, 2, 0, 4, (void*)0x0850482C, 5)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_817399C, 0x1D, sub_817399C, 0x0000207D, 7, 0, 6, (void*)0x085047FC, 5)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_8173104, 0, sub_8173104, 0x0000208E, 1, 0, 1, (void*)0x085047C8, 1)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_81729C4, 0, sub_81729C4, 0x0000207D, 10, 0, 4, (void*)0x085047A8, 3)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_81723C0, 0, sub_81723C0, 0x00002080, 2, 0, 2, (void*)0x08504788, 2)
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(object_create_action_81881E0, 0, sub_81881E0, 0x4159, 0, 0, 2, orientation, 0, (void*)0x08505050, 2)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_81873FC, 0x15, sub_81873FC, 0x40AA, 0x2E, 0, 1, (void*)0x08504FA4, 6)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_8185B40, 0x22, sub_8185B40, 0x4165, 0, 0, 5, (void*)0x08504EAC, 5)
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(object_create_action_8185054, 0, sub_8185054, 0x4159, 1, 0, 8, orientation, 0, (void*)0x08504E6C, 2)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_8184654, 5, sub_8184654, 0x40D3, 0, 0, 1, (void*)0x08504E30, 1)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_81829EC, 0xB5, sub_81829EC, 0x416C, 0, 0, 3, (void*)0x08504D5C, 3)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_8180BE4, 0x29, sub_8180BE4, 0x4165, 0, 0, 8, (void*)0x08504CDC, 5)
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(object_create_action_817E608, 0, sub_817E608, 0x415C, 5, 0, 4, orientation, 0, (void*)0x08504C0C, 3)
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(object_create_action_817C8BC, 0x17, sub_817C8BC, 0x4175, 0, 0, 4, 0, orientation, (void*)0x08504B48, 4)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_817B980, 3, sub_817B980, 0x416A, 0, 0, 1, 0, 0)
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(object_create_action_817A84C, 0, sub_817A84C, 0x4159, 0, 0, 2, orientation, 0, (void*)0x08504A78, 2)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_817A00C, 0x13, sub_817A00C, 0x4172, 3, 0, 5, (void*)0x08504A48, 6)
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(object_create_action_81798C8, 0, sub_81798C8, 0x415B, 5, 0, 1, orientation, 0, 0, 0)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_8178038, 0x10, sub_8178038, 0x4172, 0, 0, 6, (void*)0x08504970, 6)
DEFINE_OBJECT_ACTION_FACTORY(object_create_action_81773F8, 0x22, sub_81773F8, 0x4165, 0, 0, 5, (void*)0x0850490C, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176ADC, 0, sub_81743E4, 0x0000207D, 9, 0, 1, (void*)0x08504828, 1)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176CF8, 0x1f, sub_81736C0, 0x0000207D, 7, 0, 5, (void*)0x085047E8, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176D34, 0x19, sub_81733E4, 0x0000207D, 7, 0, 5, (void*)0x085047D4, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176DE8, 0, sub_8173004, 0x0000207F, 2, 0, 1, (void*)0x085047C4, 1)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176E9C, 0, sub_8172C2C, 0x0000207C, 0xc, 0, 2, (void*)0x085047B4, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_8176F18, 0, sub_81728A4, 0x0000207D, 0, 0, 1, (void*)0x085047A0, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_818B778, 0x29, sub_8187E24, 0x000040B0, 1, 0, 1, (void*)0x08505018, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_818B970, 0x65, sub_818727C, 0x000040AD, 0, 0, 1, (void*)0x08504F8C, 6)
DEFINE_OBJECT_ACTION_FACTORY(sub_818B9AC, 0x65, sub_81870FC, 0x000040AC, 0, 0, 1, (void*)0x08504F74, 6)
DEFINE_OBJECT_ACTION_FACTORY(sub_818B9E8, 0x65, sub_8186F7C, 0x000040AF, 0, 0, 1, (void*)0x08504F5C, 6)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BB14, 0x33, sub_81869C0, 0x00004079, 0, 0, 1, (void*)0x08504F28, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BB50, 0x33, sub_8186864, 0x00004079, 0, 0, 1, (void*)0x08504F14, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BB8C, 0x65, sub_81866E4, 0x00004110, 0, 0, 1, (void*)0x08504EFC, 6)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BCB8, 0x51, sub_8185A00, 0x0000416C, 0, 0, 1, (void*)0x08504E9C, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BCF4, 0x51, sub_81858C4, 0x0000416C, 1, 0, 1, (void*)0x08504E8C, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BE30, 0x29, sub_8184F34, 0x00004183, 0, 0, 1, (void*)0x08504E64, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BE6C, 0x24, sub_8184E14, 0x00004183, 0, 0, 1, (void*)0x08504E5C, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BEA8, 0x20, sub_8184CF4, 0x00004183, 0, 0, 1, (void*)0x08504E54, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_818BF98, 0x15, sub_818475C, 0x00004165, 0, 0, 4, (void*)0x08504E34, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C010, 0x8d, sub_8184528, 0x000040D3, 1, 0, 1, (void*)0x08504E28, 2)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C04C, 0x47, sub_818429C, 0x000040C4, 0, 0, 0xc, (void*)0x08504E18, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C088, 0x47, sub_8184010, 0x000040C4, 0, 0, 3, (void*)0x08504E08, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C0C4, 0x47, sub_8183D84, 0x000040C4, 0, 0, 3, (void*)0x08504DF8, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C100, 0x47, sub_8183AF8, 0x000040C4, 0, 0, 3, (void*)0x08504DE8, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C13C, 0x47, sub_818386C, 0x000040C4, 0, 0, 3, (void*)0x08504DD8, 4)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C178, 0x29, sub_8183740, 0x0000416D, 0, 0, 1, (void*)0x08504DCC, 3)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C1B4, 0x97, sub_818353C, 0x0000416D, 0, 0, 0xa, (void*)0x08504DB8, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C1F0, 0x83, sub_8183338, 0x0000416D, 0, 0, 1, (void*)0x08504DA4, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C22C, 0x83, sub_8183134, 0x0000416E, 0, 0, 1, (void*)0x08504D90, 5)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C268, 0x97, sub_8183008, 0x0000416D, 0, 0, 1, (void*)0x08504D84, 3)
DEFINE_OBJECT_ACTION_FACTORY(sub_818C2A4, 0x97, sub_8182EDC, 0x0000416D, 0, 0, 1, (void*)0x08504D78, 3)
extern void sub_8182C50(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C2E0, 0x47, sub_8182C50, 0x416c, 0, 0, 0x3, (void*)0x8504d68, 0x4)
extern void sub_81828A4(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C358, 0x43, sub_81828A4, 0x415f, 0, 0, 0x1, (void*)0x8504d4c, 0x4)
extern void sub_8182784(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C394, 0x25, sub_8182784, 0x415f, 0, 0, 0x1, (void*)0x8504d44, 0x2)
extern void sub_818251C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C3D0, 0xa1, sub_818251C, 0x415f, 0, 0, 0x2, (void*)0x8504d38, 0x3)
extern void sub_81822B4(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C40C, 0xa1, sub_81822B4, 0x415f, 0, 0, 0x2, (void*)0x8504d2c, 0x3)
extern void sub_818204C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C448, 0xa1, sub_818204C, 0x415f, 0, 0, 0x2, (void*)0x8504d20, 0x3)
extern void sub_8181DE4(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C484, 0xa1, sub_8181DE4, 0x415f, 0, 0, 0x2, (void*)0x8504d14, 0x3)
extern void sub_8181B7C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C4C0, 0xa1, sub_8181B7C, 0x415f, 0, 0, 0x2, (void*)0x8504d08, 0x3)
extern void sub_81818AC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C4FC, 0xf1, sub_81818AC, 0x4165, 0, 0, 0x8, (void*)0x8504d04, 0x1)
extern void sub_81815FC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C538, 0xf1, sub_81815FC, 0x415f, 0, 0, 0x8, (void*)0x8504d00, 0x1)
extern void sub_8181354(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C574, 0xf1, sub_8181354, 0x415f, 0, 0, 0x8, (void*)0x8504cfc, 0x1)
extern void sub_81810AC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C5B0, 0xf1, sub_81810AC, 0x415e, 0, 0, 0xa, (void*)0x8504cf8, 0x1)
extern void sub_8180988(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C664, 0x79, sub_8180988, 0x4165, 0, 0, 0x8, (void*)0x8504cd0, 0x3)
extern void sub_8180730(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C6A0, 0x79, sub_8180730, 0x4165, 0, 0, 0x8, (void*)0x8504cc4, 0x3)
extern void sub_818054C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C6DC, 0x1f, sub_818054C, 0x4165, 0, 0, 0xa, (void*)0x8504cbc, 0x2)
extern void sub_818036C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C718, 0x1f, sub_818036C, 0x4165, 0, 0, 0xa, (void*)0x8504cb4, 0x2)
extern void sub_8180108(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C754, 0x47, sub_8180108, 0x4165, 0, 0, 0x8, (void*)0x8504ca8, 0x3)
extern void sub_817FEA4(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C790, 0x47, sub_817FEA4, 0x4165, 0, 0, 0x8, (void*)0x8504c9c, 0x3)
extern void sub_817FC40(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C7CC, 0x1f, sub_817FC40, 0x4165, 0, 0, 0x8, (void*)0x8504c90, 0x3)
extern void sub_817F9AC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C808, 0x15, sub_817F9AC, 0x4165, 0, 0, 0x6, (void*)0x8504c7c, 0x5)
extern void sub_817F728(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C844, 0, sub_817F728, 0x4159, 0, 0, 0x8, (void*)0x8504c70, 0x3)
extern void sub_817F4A4(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C880, 0, sub_817F4A4, 0x4159, 0, 0, 0x8, (void*)0x8504c64, 0x3)
extern void sub_817F234(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C8BC, 0, sub_817F234, 0x4159, 0, 0, 0x8, (void*)0x8504c58, 0x3)
extern void sub_817F104(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C8F8, 0x11, sub_817F104, 0x4184, 0x1, 0, 0x1, (void*)0x8504c50, 0x2)
extern void sub_817EFF8(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C934, 0xc, sub_817EFF8, 0x4184, 0, 0, 0x1, (void*)0x8504c48, 0x2)
extern void sub_817EEEC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C970, 0xc, sub_817EEEC, 0x4184, 0x1, 0, 0x1, (void*)0x8504c40, 0x2)
extern void sub_817EDBC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C9AC, 0x11, sub_817EDBC, 0x4184, 0, 0, 0x1, (void*)0x8504c38, 0x2)
extern void sub_817ECB0(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818C9E8, 0xc, sub_817ECB0, 0x4184, 0x1, 0, 0x1, (void*)0x8504c30, 0x2)
extern void sub_817EBA4(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818CA24, 0xc, sub_817EBA4, 0x4184, 0, 0, 0x1, (void*)0x8504c28, 0x2)
extern void sub_817E410(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818CB58, 0x13, sub_817E410, 0x4165, 0, 0, 0x5, (void*)0x8504bf4, 0x6)
extern void sub_817D41C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818CD44, 0x1a, sub_817D41C, 0x417d, 0, 0, 0x9, (void*)0x8504b88, 0x6)
extern void sub_817D1F0(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818CD80, 0x1a, sub_817D1F0, 0x417c, 0, 0, 0x9, (void*)0x8504b70, 0x6)
extern void sub_817A634(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D3E4, 0x15, sub_817A634, 0x4175, 0, 0, 0x8, (void*)0x8504a70, 0x2)
extern void sub_817A41C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D420, 0x13, sub_817A41C, 0x4175, 0, 0, 0x8, (void*)0x8504a68, 0x2)
extern void sub_817A204(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D45C, 0x11, sub_817A204, 0x4175, 0, 0, 0x8, (void*)0x8504a60, 0x2)
extern void sub_8179E3C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D4D8, 0x13, sub_8179E3C, 0x4175, 0, 0, 0x5, (void*)0x8504a38, 0x4)
extern void sub_81786E8(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D76C, 0, sub_81786E8, 0x4173, 0x4, 0, 0x4, (void*)0x85049b8, 0x7)
extern void sub_8178428(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D7A8, 0, sub_8178428, 0x4173, 0x4, 0, 0x4, (void*)0x850499c, 0x7)
extern void sub_8178230(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D7E4, 0x1a, sub_8178230, 0x4172, 0, 0, 0xa, (void*)0x8504988, 0x5)
extern void sub_8177DCC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D85C, 0x25, sub_8177DCC, 0x4165, 0, 0, 0x6, (void*)0x850495c, 0x5)
extern void sub_8177B5C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D898, 0x1b, sub_8177B5C, 0x4165, 0, 0, 0x6, (void*)0x8504948, 0x5)
extern void sub_81778EC(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D8D4, 0x1b, sub_81778EC, 0x4165, 0, 0, 0x6, (void*)0x8504934, 0x5)
extern void sub_8177680(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D910, 0x1b, sub_8177680, 0x4165, 0, 0, 0x6, (void*)0x8504920, 0x5)
extern void sub_8177180(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818D988, 0x1a, sub_8177180, 0x4164, 0, 0, 0x5, (void*)0x85048fc, 0x4)
extern void sub_8187CD0(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818B7B4, 0x3d, sub_8187CD0, 0x40c8, 0x8, 0, 0x1, (void*)0x8505000, 0x6)
extern void sub_8187B7C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818B7F4, 0x3d, sub_8187B7C, 0x40c6, 0x8, 0, 0x1, (void*)0x8504fe8, 0x6)
extern void sub_8187A5C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818B834, 0x9, sub_8187A5C, 0x40e1, 0x1, 0, 0x5, (void*)0x8504fe0, 0x2)
extern void sub_818793C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818B874, 0x9, sub_818793C, 0x40e0, 0x1, 0, 0x5, (void*)0x8504fd8, 0x2)
extern void sub_818781C(void);
DEFINE_OBJECT_ACTION_FACTORY(sub_818B8B4, 0x9, sub_818781C, 0x40e6, 0x1, 0, 0x5, (void*)0x8504fd0, 0x2)
extern void sub_817E884(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CAD8, 0x79, sub_817E884, 0x400c, 0x5, 0, 0x1, orientation, orientation, (void*)0x8504c18,
                    0x2)
extern void sub_817E2F0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CB94, 0, sub_817E2F0, 0x4159, 0x5, 0, 0x1, 0, 0, (void*)0x8504be4, 0x4)
extern void sub_817E1D0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CBD4, 0, sub_817E1D0, 0x4159, 0x5, 0, 0x1, 0, 0, (void*)0x8504bd4, 0x4)
extern void sub_817DDB0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CC50, 0, sub_817DDB0, 0x415b, 0x1, 0, 0xc, orientation, 0, (void*)0x8504bc4, 0x2)
extern void sub_817CB1C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CE68, 0, sub_817CB1C, 0x415b, 0x1, 0, 0x8, orientation, 0, (void*)0x8504b58, 0x3)
extern void sub_817C6C4(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CEE4, 0x13, sub_817C6C4, 0x4172, 0x3, 0, 0x5, orientation, orientation, (void*)0x8504b30,
                    0x6)
extern void sub_817C4CC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CF24, 0x13, sub_817C4CC, 0x4172, 0x3, 0, 0x5, orientation, orientation, (void*)0x8504b18,
                    0x6)
extern void sub_817B788(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D1B4, 0, sub_817B788, 0x4159, 0x1, 0, 0x8, orientation, 0, (void*)0x8504ab8, 0x2)
extern void sub_817B590(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D1F4, 0, sub_817B590, 0x4159, 0x1, 0, 0x8, orientation, 0, (void*)0x8504ab0, 0x2)
extern void sub_817B398(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D234, 0, sub_817B398, 0x4159, 0x1, 0, 0x8, orientation, 0, (void*)0x8504aa8, 0x2)
extern void sub_817B1A0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D274, 0, sub_817B1A0, 0x415a, 0x1, 0, 0x8, orientation, 0, (void*)0x8504aa0, 0x2)
extern void sub_817AFA8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D2B4, 0, sub_817AFA8, 0x4159, 0x1, 0, 0x8, orientation, 0, (void*)0x8504a98, 0x2)
extern void sub_81799CC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D550, 0, sub_81799CC, 0x415b, 0x4, 0, 0x8, orientation, 0, (void*)0x8504a20, 0x3)
extern void sub_8172F04(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176E24, 0, sub_8172F04, 0x207f, 0x2, 0, 0x1, orientation, 0, (void*)0x85047c0, 0x1)
extern void sub_8172784(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176F54, 0, sub_8172784, 0x207d, 0, 0, 0x1, orientation, 0, (void*)0x8504798, 0x2)
extern void sub_81886D0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818B610, 0x1a, sub_81886D0, 0x4165, 0, 0, 0x1, orientation, 0, (void*)0x8505074, 0x7)
extern void sub_8188590(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818B64C, 0x14, sub_8188590, 0x415f, 0x1, 0, 0x1, orientation, 0, (void*)0x8505060, 0x5)
extern void sub_81880BC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818B700, 0, sub_81880BC, 0x415a, 0, 0, 0x1, orientation, 0, (void*)0x8505040, 0x4)
extern void sub_8187F7C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818B73C, 0x11, sub_8187F7C, 0x415f, 0x1, 0, 0x1, orientation, 0, (void*)0x850502c, 0x5)
extern void sub_8186E6C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BA24, 0x1f, sub_8186E6C, 0x40f4, 0, 0, 0x1, orientation, 0, (void*)0x8504f54, 0x2)
extern void sub_8186D50(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BA60, 0x1a, sub_8186D50, 0x4183, 0, 0, 0x1, orientation, 0, (void*)0x8504f4c, 0x2)
extern void sub_8186C34(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BA9C, 0x1a, sub_8186C34, 0x4183, 0, 0, 0x1, orientation, 0, (void*)0x8504f44, 0x2)
extern void sub_8186B18(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BAD8, 0x1a, sub_8186B18, 0x4183, 0, 0, 0x1, orientation, 0, (void*)0x8504f3c, 0x2)
extern void sub_8184BD8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BEE4, 0x1a, sub_8184BD8, 0x4183, 0, 0, 0x1, orientation, 0, (void*)0x8504e4c, 0x2)
extern void sub_8184ABC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BF20, 0x1a, sub_8184ABC, 0x4183, 0, 0, 0x1, orientation, 0, (void*)0x8504e44, 0x2)
extern void sub_81849A0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BF5C, 0x1a, sub_81849A0, 0x4183, 0, 0, 0x1, orientation, 0, (void*)0x8504e3c, 0x2)
extern void sub_817DFEC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CC14, 0, sub_817DFEC, 0x415b, 0, 0, 0xc, orientation, 0, (void*)0x8504bcc, 0x2)
extern void sub_817DB40(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CC90, 0, sub_817DB40, 0x415b, 0, 0, 0x8, orientation, 0, (void*)0x8504bb8, 0x3)
extern void sub_817D8C4(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CCCC, 0, sub_817D8C4, 0x4159, 0, 0, 0x4, orientation, 0, (void*)0x8504bac, 0x3)
extern void sub_817D648(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CD08, 0, sub_817D648, 0x415b, 0, 0, 0x4, orientation, 0, (void*)0x8504ba0, 0x3)
extern void sub_817CFB8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CDBC, 0x15, sub_817CFB8, 0x4175, 0, 0, 0x8, 0, orientation, (void*)0x8504b64, 0x3)
extern void sub_817C3C0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CF64, 0, sub_817C3C0, 0x4159, 0x4, 0, 0x1, orientation, 0, (void*)0x8504b14, 0x1)
extern void sub_817C2A8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CFA0, 0, sub_817C2A8, 0x415b, 0, 0, 0x1, orientation, 0, (void*)0x8504b0c, 0x2)
extern void sub_817C174(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CFDC, 0, sub_817C174, 0x4159, 0, 0, 0x1, orientation, 0, (void*)0x8504afc, 0x4)
extern void sub_817C040(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D018, 0, sub_817C040, 0x4159, 0, 0, 0x1, orientation, 0, (void*)0x8504aec, 0x4)
extern void sub_817BF0C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D054, 0, sub_817BF0C, 0x415b, 0, 0, 0x1, orientation, 0, (void*)0x8504adc, 0x4)
extern void sub_817BDD8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D090, 0, sub_817BDD8, 0x415b, 0, 0, 0x1, orientation, 0, (void*)0x8504acc, 0x4)
extern void sub_8179C04(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D514, 0, sub_8179C04, 0x415b, 0, 0, 0x8, orientation, 0, (void*)0x8504a2c, 0x3)
extern void sub_817969C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D5C8, 0, sub_817969C, 0x4159, 0, 0, 0x8, orientation, 0, (void*)0x8504a14, 0x3)
extern void sub_8179460(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D604, 0, sub_8179460, 0x4159, 0, 0, 0x8, orientation, 0, (void*)0x8504a08, 0x3)
extern void sub_8179224(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D640, 0, sub_8179224, 0x4159, 0, 0, 0x8, orientation, 0, (void*)0x85049fc, 0x3)
extern void sub_8178FF8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D67C, 0xf, sub_8178FF8, 0x4174, 0, 0, 0x4, 0, orientation, (void*)0x85049f0, 0x3)
extern void sub_8178DD0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D6B8, 0xf, sub_8178DD0, 0x4174, 0, 0, 0x4, 0, orientation, (void*)0x85049e4, 0x3)
extern void sub_8178BC0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D6F4, 0x13, sub_8178BC0, 0x4174, 0, 0, 0x4, 0, orientation, (void*)0x85049dc, 0x2)
extern void sub_81789A8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D730, 0xf, sub_81789A8, 0x4174, 0, 0, 0x4, 0, orientation, (void*)0x85049d4, 0x2)
extern void sub_81883B8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818B688, 0, sub_81883B8, 0x415b, 0, 0, 0x2, orientation, 0, (void*)0x8505058, 0x2)
extern void sub_817BA9C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D144, 0xc, sub_817BA9C, 0x416b, 0, 0, 0x1, orientation, orientation, (void*)0x8504ac0, 0x1)
extern void sub_817ADD4(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D2F4, 0, sub_817ADD4, 0x4159, 0, 0, 0x2, orientation, orientation, (void*)0x8504a90, 0x2)
extern void sub_817AC00(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D330, 0, sub_817AC00, 0x4159, 0, 0, 0x2, orientation, orientation, (void*)0x8504a88, 0x2)
extern void sub_817AA20(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D36C, 0, sub_817AA20, 0x4159, 0, 0, 0x2, orientation, 0, (void*)0x8504a80, 0x2)
extern void sub_8177078(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D9C4, 0x5, sub_8177078, 0x4169, 0, 0, 0x1, orientation, orientation, (void*)0x85048f8, 0x1)
extern void sub_8174D88(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176984, 0, sub_8174D88, 0x2080, 0, 0, 0x1, orientation, orientation, (void*)0x8504858, 0x1)
extern void sub_8174C74(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_81769BC, 0, sub_8174C74, 0x2080, 0, 0, 0x1, orientation, orientation, (void*)0x8504854, 0x1)
extern void sub_8174B60(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_81769F4, 0, sub_8174B60, 0x2080, 0, 0, 0x1, orientation, orientation, (void*)0x8504850, 0x1)
extern void sub_8174A4C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176A2C, 0, sub_8174A4C, 0x2080, 0, 0, 0x1, orientation, orientation, (void*)0x850484c, 0x1)
extern void sub_8171FF8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8177040, 0, sub_8171FF8, 0x2080, 0, 0, 0x2, orientation, orientation, (void*)0x8504778, 0x2)
extern void sub_81742F0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176B18, 0, sub_81742F0, 0x207c, 0x9, 0, 0x1, orientation, orientation, (void*)0, 0)
extern void sub_817CEA8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CDF8, 0, sub_817CEA8, 0x415b, 0x5, 0, 0x1, orientation, 0, (void*)0, 0)
extern void sub_81741DC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176B50, 0, sub_81741DC, 0x207f, 0x1, 0, 0x1, orientation, orientation, (void*)0x8504824, 0x1)
extern void sub_81740C8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176B8C, 0, sub_81740C8, 0x207e, 0x1, 0, 0x1, orientation, 0, (void*)0x8504820, 0x1)
extern void sub_8173FB4(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176BC8, 0, sub_8173FB4, 0x207f, 0x1, 0, 0x1, orientation, orientation, (void*)0x850481c, 0x1)
extern void sub_8173EA0(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176C04, 0, sub_8173EA0, 0x207f, 0x1, 0, 0x1, orientation, 0, (void*)0x8504818, 0x1)
extern void sub_8173D8C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176C40, 0, sub_8173D8C, 0x207f, 0x1, 0, 0x1, orientation, orientation, (void*)0x8504814, 0x1)
extern void sub_8173C78(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176C7C, 0, sub_8173C78, 0x207f, 0x1, 0, 0x1, orientation, 0, (void*)0x8504810, 0x1)
extern void sub_817BCC8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D0CC, 0, sub_817BCC8, 0x4159, 0x1, 0, 0x1, orientation, 0, (void*)0x8504ac8, 0x1)
extern void sub_817BBB8(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818D108, 0, sub_817BBB8, 0x4159, 0x1, 0, 0x1, orientation, 0, (void*)0x8504ac4, 0x1)
extern void sub_8176298(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_81767A4, 0, sub_8176298, 0x2080, 0x2, 0, 0x5, orientation, orientation, (void*)0x85048e0, 0x3)
extern void sub_8176030(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_81767E0, 0, sub_8176030, 0x2080, 0x1, 0, 0x5, orientation, orientation, (void*)0x85048d4, 0x3)
extern void sub_8175A50(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176858, 0, sub_8175A50, 0x2080, 0x1, 0, 0x4, orientation, orientation, (void*)0x85048ac, 0x5)
extern void sub_81747EC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176A64, 0, sub_81747EC, 0x2080, 0x5, 0, 0x6, orientation, orientation, (void*)0x8504840, 0x3)
extern void sub_8176500(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176768, 0, sub_8176500, 0x2080, 0x3, 0, 0x6, orientation, orientation, (void*)0x85048ec, 0x3)
extern void sub_8175D40(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_817681C, 0, sub_8175D40, 0x2080, 0x1, 0, 0x5, orientation, orientation, (void*)0x85048c0, 0x5)
extern void sub_8173204(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176D70, 0, sub_8173204, 0x2080, 0x2, 0, 0x5, orientation, orientation, (void*)0x85047cc, 0x2)
extern void sub_81725A4(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176F90, 0, sub_81725A4, 0x2080, 0x3, 0, 0x2, orientation, orientation, (void*)0x8504790, 0x2)
extern void sub_81721DC(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8177004, 0, sub_81721DC, 0x2080, 0x1, 0, 0x2, orientation, orientation, (void*)0x8504780, 0x2)
extern void sub_8187568(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818B8F4, 0x15, sub_8187568, 0x4175, 0, 0, 0x5, orientation, orientation, (void*)0x8504fbc,
                    0x5)
extern void sub_8186404(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BBC8, 0x22, sub_8186404, 0x4165, 0, 0, 0x5, orientation, orientation, (void*)0x8504ee8,
                    0x5)
extern void sub_8186120(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BC04, 0x22, sub_8186120, 0x4165, 0, 0, 0x5, orientation, orientation, (void*)0x8504ed4,
                    0x5)
extern void sub_8185E30(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BC40, 0x22, sub_8185E30, 0x4165, 0, 0, 0x5, orientation, orientation, (void*)0x8504ec0,
                    0x5)
extern void sub_8180E78(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818C5EC, 0x3d, sub_8180E78, 0x4165, 0, 0, 0x2, orientation, orientation, (void*)0x8504cf0,
                    0x2)
extern void sub_817EA9C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CA60, 0x41, sub_817EA9C, 0x40dc, 0, 0, 0x1, orientation, orientation, (void*)0x8504c24,
                    0x1)
extern void sub_8185674(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BD30, 0, sub_8185674, 0x415b, 0x1, 0, 0x4, orientation, 0, (void*)0x8504e84, 0x2)
extern void sub_818548C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BD70, 0, sub_818548C, 0x415b, 0x1, 0, 0x8, orientation, 0, (void*)0x8504e7c, 0x2)
extern void sub_818523C(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818BDB0, 0, sub_818523C, 0x4159, 0x1, 0, 0x4, orientation, 0, (void*)0x8504e74, 0x2)
extern void sub_8172E04(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_8176E60, 0, sub_8172E04, 0x2092, 0, 0, 0x1, orientation, orientation, (void*)0x85047bc, 0x1)
extern void sub_817E994(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CA9C, 0x9, sub_817E994, 0x4182, 0, 0, 0x1, orientation, orientation, (void*)0x8504c20, 0x1)
extern void sub_817CD98(void);
DEFINE_OBJECT_ACTION_FACTORY_ORIENTATION(sub_818CE30, 0, sub_817CD98, 0x4159, 0x5, 0, 0x1, orientation, 0, (void*)0, 0)
