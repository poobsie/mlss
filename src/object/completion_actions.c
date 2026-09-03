#include "global.h"
#include "object/runtime_object.h"
#define SEC(name)         __attribute__((section(".text.object_flag_actions." #name)))
extern void sub_8082E1C(struct RuntimeObject*, s32, s32, s32);
#define DEFINE_FLAG_ACTION(name)                                                                       \
    SEC(name) void name(struct RuntimeObject* object) {                                                 \
        if (object->visual->flags & 8) {                                                               \
            sub_8082E1C(object, 0, 0x204D, 0);                                                         \
            object->update = 0;                                                                        \
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
