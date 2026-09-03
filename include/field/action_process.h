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

struct FieldNestedVisualOwner {
    u8 unknown00[0x10];
    struct RuntimeObjectVisual* visual;
};

struct FieldNestedVisualProcess {
    u8 unknown00[4];
    void (*update)(struct FieldNestedVisualProcess* process);
    u8 unknown08[4];
    struct FieldNestedVisualOwner* owner;
};

#define field_action_wait_for_visual_then_branch sub_807F648
#define field_action_wait_for_state_flag_clear sub_8081C54
#define field_wait_for_nested_visual_completion sub_8106A10

void field_action_wait_for_visual_then_branch(struct FieldActionProcess* process);
void field_action_wait_for_state_flag_clear(struct FieldActionProcess* process);
void field_wait_for_nested_visual_completion(
    struct FieldNestedVisualProcess* process);

#endif
