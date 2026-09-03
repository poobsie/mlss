#include "field/action_process.h"

u8 sub_8080168(struct RuntimeObject* object);
void sub_807DC8C(struct FieldActionProcess* process);
void sub_80801A0(struct FieldActionProcess* process);
void sub_8081F84(struct FieldActionProcess* process);
void sub_8104D14(struct FieldNestedVisualProcess* process);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(symbol))))

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
