#include "field/effect_wait_transition.h"
#include "field/runtime_flags.h"
#include "field/value_transfer.h"

#define SEC(symbol) __attribute__((section(".text.field_effect_wait_transition." #symbol)))

void* sub_8084338(s32 id, s32, s32, s32);
void sub_801E150(void* effect, u8, s32, s32, s32);
void sub_8101A6C(struct FieldEffectWaitTransition* transition);
void sub_8100E5C(struct FieldEffectWaitTransition* transition);
void sub_810CA30(void);

SEC(sub_8106C10)
void field_wait_create_effect_and_continue(
    struct FieldEffectWaitTransition* transition)
{
    u8 blocked;
    void* effect;

    if (transition->timer10 > 0) {
        transition->timer10--;
        return;
    }

    blocked = field_runtime_test_flag_10();
    if (blocked != 0)
        return;

    effect = sub_8084338(0x7002, 0, 0, 0);
    sub_801E150(effect, 0, -1, 0, blocked);
    field_commit_runtime_value_transfer();
    transition->callback = sub_8101A6C;
}

SEC(sub_8106DF0)
void field_countdown_refresh_and_continue(
    struct FieldEffectWaitTransition* transition)
{
    if (--transition->timer10 <= 0 &&
        (field_runtime_test_flag_10() << 24) == 0) {
        sub_810CA30();
        transition->callback = sub_8100E5C;
    }
}

SEC(sub_8107360)
void field_countdown_commit_and_stop(
    struct FieldEffectWaitTransition* transition)
{
    s32 timer = transition->timer10;

    if (timer != 0) {
        transition->timer10--;
    } else {
        field_commit_runtime_value_transfer();
        transition->callback = (void*)timer;
    }
}
