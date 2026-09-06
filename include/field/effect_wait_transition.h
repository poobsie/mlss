#ifndef GUARD_FIELD_EFFECT_WAIT_TRANSITION_H
#define GUARD_FIELD_EFFECT_WAIT_TRANSITION_H

#include "global.h"

struct FieldEffectWaitTransition {
    u8 unknown00[4];
    void (*callback)(struct FieldEffectWaitTransition* transition);
    u8 unknown08[8];
    s16 timer10;
};

#define field_wait_create_effect_and_continue sub_8106C10
#define field_countdown_refresh_and_continue sub_8106DF0
#define field_countdown_commit_and_stop sub_8107360

void field_wait_create_effect_and_continue(
    struct FieldEffectWaitTransition* transition);
void field_countdown_refresh_and_continue(
    struct FieldEffectWaitTransition* transition);
void field_countdown_commit_and_stop(
    struct FieldEffectWaitTransition* transition);

#endif
