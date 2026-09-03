#include "field/action_process.h"

u8 sub_8080168(struct RuntimeObject* object);
void sub_807DC8C(struct FieldActionProcess* process);
void sub_8080A40(struct FieldObjectUpdateProcess* process);
void sub_8081288(struct FieldActionProcess* process);
void sub_80813A0(void);
void sub_8081F84(struct FieldActionProcess* process);
void sub_8082A28(void);
u32 sub_8082B00(void);
void sub_8104D14(struct FieldNestedVisualProcess* process);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(symbol))))
#define MISC2_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

SEC(sub_807F648)
void field_action_wait_for_visual_then_branch(struct FieldActionProcess* process)
{
    u8 branch;
    struct RuntimeObject* object;

    object = process->object;
    branch = sub_8080168(object);
    if (object->visual->flags & 8) {
        if (branch == 0) {
            sub_807DC8C(process);
            return;
        }
        process->update = sub_80801A0;
    }
}

MISC2_SEC(field_action_finish_when_branch_clear)
void field_action_finish_when_branch_clear(struct FieldActionProcess* process)
{
    if (sub_8080168(process->object) == 0)
        sub_807DC8C(process);
}

MISC2_SEC(field_process_run_global_setup_when_ready)
void field_process_run_global_setup_when_ready(struct FieldActionProcess* process)
{
    if ((sub_8082B00() << 24) == 0) {
        sub_8082A28();
        sub_80813A0();
        process->update = sub_8081288;
    }
}

MISC2_SEC(field_wait_for_runtime_object_update_to_stop)
void field_wait_for_runtime_object_update_to_stop(
    struct FieldObjectUpdateProcess* process)
{
    RuntimeObjectCallback update;
    struct RuntimeObject* object;

    object = process->object;
    update = object->update;
    if (update == 0 || (update(object), object->update == 0))
        process->update = sub_8080A40;
}

MISC_SEC(field_action_wait_for_state_flag_clear)
void field_action_wait_for_state_flag_clear(struct FieldActionProcess* process)
{
    if (!(process->object->state->flags111 & 1))
        process->update = sub_8081F84;
}

MISC_SEC(field_wait_for_nested_visual_completion)
void field_wait_for_nested_visual_completion(
    struct FieldNestedVisualProcess* process)
{
    if (process->owner->visual->flags & 8)
        process->update = sub_8104D14;
}
