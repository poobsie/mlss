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

struct FieldObjectUpdateProcess {
    u8 unknown00[4];
    void (*update)(struct FieldObjectUpdateProcess* process);
    u8 unknown08[4];
    struct RuntimeObject* object;
};

#define field_action_wait_for_visual_then_branch sub_807F648
#define field_action_finish_when_branch_clear sub_80801A0
#define field_process_run_global_setup_when_ready sub_8081FB0
#define field_wait_for_runtime_object_update_to_stop sub_8082158
#define field_action_wait_for_state_flag_clear sub_8081C54
#define field_wait_for_nested_visual_completion sub_8106A10

void field_action_wait_for_visual_then_branch(struct FieldActionProcess* process);
void field_action_finish_when_branch_clear(struct FieldActionProcess* process);
void field_process_run_global_setup_when_ready(struct FieldActionProcess* process);
void field_wait_for_runtime_object_update_to_stop(
    struct FieldObjectUpdateProcess* process);
void field_action_wait_for_state_flag_clear(struct FieldActionProcess* process);
void field_wait_for_nested_visual_completion(
    struct FieldNestedVisualProcess* process);

#endif
