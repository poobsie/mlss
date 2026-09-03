#ifndef GUARD_FIELD_SELECTION_SEQUENCE_H
#define GUARD_FIELD_SELECTION_SEQUENCE_H

#include "global.h"

struct FieldSelectionRuntime {
    u8 unknown000[0x0B];
    u8 flags00B;
    u8 unknown00C[0x70];
    void* activeObject;
    void* object80;
    void* object84;
    u8 unknown088[0x237];
    u8 flags2BF;
    u8 flags2C0;
    u8 unknown2C1[0x4F];
    s32 blocker310;
    u8 unknown314[0x32];
    u8 mode346;
    u8 unknown347[2];
    u8 selectedEntry349;
};

struct FieldSelectionProcess {
    u8 unknown00[4];
    void (*update)(struct FieldSelectionProcess* process);
};

void field_wait_then_prepare_active_object(struct FieldSelectionProcess* process);
void field_wait_then_commit_selected_entry(struct FieldSelectionProcess* process);
void field_wait_then_prepare_selected_entry(struct FieldSelectionProcess* process);
void field_wait_then_finish_selection_setup(struct FieldSelectionProcess* process);

#define field_start_alternate_actor_action sub_80FD8BC

void field_start_alternate_actor_action(struct FieldSelectionProcess* process);

#define field_when_ready_prepare_selection_and_continue sub_81072A8

void field_when_ready_prepare_selection_and_continue(
    struct FieldSelectionProcess* process);

#endif
