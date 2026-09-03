#include "field/action_process.h"

u8 sub_8080168(struct RuntimeObject* object);
void sub_807DC8C(struct FieldActionProcess* process);
void sub_80801A0(struct FieldActionProcess* process);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

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
