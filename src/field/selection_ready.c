#include "field/selection_sequence.h"

s32 sub_8082B00(void);
void sub_8087360(void);
void sub_810192C(struct FieldSelectionProcess* process);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define FIELD_RUNTIME (*(struct FieldSelectionRuntime**)0x03000FD8)

SEC(sub_81072A8)
void field_when_ready_prepare_selection_and_continue(
    struct FieldSelectionProcess* process)
{
    if (!(FIELD_RUNTIME->flags00B & 4) && ((sub_8082B00() << 0x18) == 0)) {
        sub_8087360();
        process->update = sub_810192C;
    }
}
