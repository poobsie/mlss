#ifndef GUARD_FIELD_SELECTION_SEQUENCE_H
#define GUARD_FIELD_SELECTION_SEQUENCE_H

#include "global.h"

struct FieldSelectionRuntime {
    u8 unknown000[0x0B];
    u8 flags00B;
    u8 unknown00C[0x70];
    void* activeObject;
    u8 unknown080[0x23F];
    u8 flags2BF;
    u8 unknown2C0[0x50];
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

#endif
