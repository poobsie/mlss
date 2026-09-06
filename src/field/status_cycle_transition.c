#include "field/status_cycle_transition.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.field_status_cycle_transition." #name)))
#define FIELD_RUNTIME (*(struct FieldStatusCycleRuntime**)0x03000FD8)

struct FieldStatusCycleSelection {
    u8 unknown00[0x10];
    s16 objectIndex;
};

struct FieldStatusCycleRuntime {
    u8 unknown000[7];
    u8 flags007;
    u8 unknown008[0x2F4];
    struct RuntimeObject* objects2FC[5];
    struct FieldStatusCycleSelection* selection310;
    u16 phase314;
};

void sub_810971C(struct FieldStatusCycleProcess* process);
void sub_810D4E0(struct FieldStatusCycleProcess* process);

SEC(sub_810958C)
void field_advance_status_cycle_transition(
    struct FieldStatusCycleProcess* process)
{
    struct FieldStatusCycleRuntime* runtime;
    struct RuntimeObject* object;

    sub_810971C(process);
    runtime = FIELD_RUNTIME;
    runtime->phase314 += 0x400;
    if ((s16)runtime->phase314 > 0x1FFF) {
        runtime->phase314 = 0x2000;
        object = runtime->objects2FC[runtime->selection310->objectIndex];
        if (object->update != NULL) {
            process->update = sub_810D4E0;
        } else {
            runtime->flags007 &= 0x1F;
            process->update = sub_810971C;
        }
    }
}

SEC(sub_810D4E0)
void field_finish_status_cycle_when_selected_object_idle(
    struct FieldStatusCycleProcess* process)
{
    struct FieldStatusCycleRuntime* runtime;
    struct RuntimeObject* object;

    sub_810971C(process);
    runtime = FIELD_RUNTIME;
    object = runtime->objects2FC[runtime->selection310->objectIndex];
    if (object->update == NULL) {
        runtime->flags007 &= 0x1F;
        process->update = sub_810971C;
    }
}
