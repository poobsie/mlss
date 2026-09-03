#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
#define SEC(name)         __attribute__((section(".text.object_flag_actions." #name)))
extern void sub_8082E1C();
#define DEFINE_FLAG_ACTION(name)                                                                       \
    SEC(name) void name(void* arg0) {                                                                  \
        if (FIELD_AT(FIELD_AT(arg0, void**, 8), u8*, 0x12) & 8) {                                      \
            sub_8082E1C(arg0, 0, 0x204D, 0);                                                           \
            FIELD_AT(arg0, s32*, 0x4C) = 0;                                                            \
        }                                                                                              \
    }
DEFINE_FLAG_ACTION(sub_808DCB0)
DEFINE_FLAG_ACTION(sub_808E09C)
DEFINE_FLAG_ACTION(sub_808F0AC)
DEFINE_FLAG_ACTION(sub_809034C)
DEFINE_FLAG_ACTION(sub_80906B8)
DEFINE_FLAG_ACTION(sub_8090A24)
DEFINE_FLAG_ACTION(sub_8090E20)
DEFINE_FLAG_ACTION(sub_8091FB0)
DEFINE_FLAG_ACTION(sub_8093140)
DEFINE_FLAG_ACTION(sub_80942CC)
DEFINE_FLAG_ACTION(sub_8094724)
DEFINE_FLAG_ACTION(sub_8094B7C)
DEFINE_FLAG_ACTION(sub_8094FD4)
