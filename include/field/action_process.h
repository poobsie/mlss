#ifndef GUARD_FIELD_ACTION_PROCESS_H
#define GUARD_FIELD_ACTION_PROCESS_H

#include "object/runtime_object.h"

struct FieldActionProcess;
typedef void (*FieldActionProcessCallback)(struct FieldActionProcess* process);

struct FieldActionProcess {
    u8 unknown00[4];
    FieldActionProcessCallback update;
    struct RuntimeObject* object;
};

#define field_action_wait_for_visual_then_branch sub_807F648

void field_action_wait_for_visual_then_branch(struct FieldActionProcess* process);

#endif
