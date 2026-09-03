#include "global.h"
#include "object/functions.h"
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

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))

MISC3_SEC(object_on_visual_complete_stop_command_204d_n)
void object_on_visual_complete_stop_command_204d_n(
    struct RuntimeObject* object)
{
    if (object->visual->flags & 8) {
        sub_8082E1C(object, 0, 0x204D, 0);
        object->update = 0;
    }
}

#define DEFINE_STOP_ON_VISUAL_COMPLETE(name, command)                   \
    MISC_SEC(name) void name(struct RuntimeObject* object)              \
    {                                                                    \
        if (object->visual->flags & 8) {                                \
            sub_8082E1C(object, 0, command, 0);                         \
            object->update = 0;                                         \
        }                                                                \
    }

#define DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(name, command)            \
    DEFINE_STOP_ON_VISUAL_COMPLETE(name, command)                        \
    MISC_SEC(name) const u16 name##_padding = 0;

DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_a, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_b, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_c, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_d, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_e, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_f, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_g, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_h, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_i, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_j, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_k, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_l, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_m, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_n, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_o, 0)
DEFINE_PADDED_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_0_p, 0)

DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_a, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_b, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_c, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_d, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_e, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_f, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_g, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_h, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_i, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_j, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_k, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_l, 0x2000)
DEFINE_STOP_ON_VISUAL_COMPLETE(object_on_visual_complete_stop_command_2000_m, 0x2000)
