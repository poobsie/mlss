#include "field/selection_sequence.h"

#define SEC(name) __attribute__((section(".text.field_selection_sequence." #name)))
#define FIELD_RUNTIME (*(struct FieldSelectionRuntime**)0x03000FD8)

void nullsub_4(void);
void sub_8081E2C(void* object);
void sub_8081EAC(u8 entry);
void sub_8095584(void* object);
void sub_80F7068(u8 entry, s32 value);
void sub_80F75B4(u32 flags);
void sub_80F75D8(u32 flags);
void sub_8100D18(struct FieldSelectionProcess* process);
void sub_8100E5C(struct FieldSelectionProcess* process);
s32 sub_8082B00(void);

SEC(sub_8106E1C)
void sub_8106E1C(struct FieldSelectionProcess* process)
{
    s32 activeObject;
    struct FieldSelectionRuntime* runtime = FIELD_RUNTIME;

    if (runtime->blocker310 == 0) {
        activeObject = (s32)runtime->activeObject;
        nullsub_4();
        sub_8081E2C((void*)(activeObject + 8));
        process->update = sub_8100D18;
        sub_80F75D8(4);
    }
}

SEC(sub_8106E58)
void sub_8106E58(struct FieldSelectionProcess* process)
{
    struct FieldSelectionRuntime* runtime;

    if ((sub_8082B00() << 0x18) == 0) {
        runtime = FIELD_RUNTIME;
        if (!(runtime->flags00B & 4)) {
            sub_8095584((u8*)runtime->activeObject + 8);
            sub_80F7068(FIELD_RUNTIME->selectedEntry349, -1);
            FIELD_RUNTIME->selectedEntry349 = 0xFF;
            process->update = sub_8100E5C;
            sub_80F75B4(8);
        }
    }
}

SEC(sub_8106EB0)
void sub_8106EB0(struct FieldSelectionProcess* process)
{
    struct FieldSelectionRuntime* runtime = FIELD_RUNTIME;

    if (runtime->blocker310 == 0) {
        sub_8081EAC(runtime->selectedEntry349);
        process->update = sub_8106E58;
        sub_80F75D8(4);
    }
}

void field_wait_then_prepare_active_object(struct FieldSelectionProcess* process)
    __attribute__((alias("sub_8106E1C")));
void field_wait_then_commit_selected_entry(struct FieldSelectionProcess* process)
    __attribute__((alias("sub_8106E58")));
void field_wait_then_prepare_selected_entry(struct FieldSelectionProcess* process)
    __attribute__((alias("sub_8106EB0")));
