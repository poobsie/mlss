#ifndef GUARD_FIELD_STATUS_CYCLE_TRANSITION_H
#define GUARD_FIELD_STATUS_CYCLE_TRANSITION_H

#include "global.h"

struct FieldStatusCycleProcess {
    u8 unknown00[4];
    void (*update)(struct FieldStatusCycleProcess* process);
};

#define field_advance_status_cycle_transition sub_810958C
#define field_finish_status_cycle_when_selected_object_idle sub_810D4E0
void field_advance_status_cycle_transition(
    struct FieldStatusCycleProcess* process);
void field_finish_status_cycle_when_selected_object_idle(
    struct FieldStatusCycleProcess* process);

#endif
