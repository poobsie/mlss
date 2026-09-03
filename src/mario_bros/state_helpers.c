#include "global.h"
#include "mario_bros/functions.h"
#include "mario_bros/runtime.h"

#define MB_SECTION(name) __attribute__((section(".text.mariobros_helpers_" #name)))

struct MarioBrosStateController {
    u8 unknown00;
    u8 state;
    u8 unknown02[0x3C];
    u8 flags3E;
    u8 unknown3F[2];
    u8 value41;
};

void sub_8F66360(void*, u32);
void sub_8F8CCB4(void*, u32);
void sub_8F568DC(u32, u32, void*);
void sub_8F57F2C(void);

MB_SECTION(sub_8F66A40) u32 mario_bros_normalize_variant_a(u8 value) {
    switch (value) {
    case 2:
        return 2;
    default:
        return 1;
    }
}
MB_SECTION(sub_8F8D394) u32 mario_bros_normalize_variant_b(u8 value) {
    switch (value) {
    case 2:
        return 2;
    default:
        return 1;
    }
}

#define DEFINE_STATE_RESET(name, callback)                                                            \
    MB_SECTION(name) void name(struct MarioBrosStateController* obj) {                                \
        if (obj->state <= 7) {                                                                        \
            callback(obj, 1);                                                                         \
            obj->flags3E = 0x80;                                                                      \
            obj->value41 = 0;                                                                         \
            obj->state = 3;                                                                           \
        }                                                                                             \
    }

DEFINE_STATE_RESET(mario_bros_reset_state_controller_a, sub_8F66360)
DEFINE_STATE_RESET(mario_bros_reset_state_controller_b, sub_8F8CCB4)

#define DEFINE_GLOBAL_INCREMENT(name)                                                                 \
    MB_SECTION(name) void name(void) {                                                                \
        struct MarioBrosEventSource* source = gMarioGlobal_03000F50.root->eventSource;                 \
        sub_8F568DC(0x19, 0x58, source->eventArgument);                                                \
        sub_8F57F2C();                                                                                \
        gMarioGlobal_03000F50.sequenceIndex++;                                                        \
    }

DEFINE_GLOBAL_INCREMENT(mario_bros_emit_event_and_advance_sequence_a)
DEFINE_GLOBAL_INCREMENT(mario_bros_emit_event_and_advance_sequence_b)
