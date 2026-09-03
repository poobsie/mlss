#include "field/display.h"
#include "object/runtime_object.h"

#define SEC(name) __attribute__((section(".text.field_display." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))
#define FIELD_RUNTIME (*(struct FieldDisplayRuntime**)0x03000FD8)

void sub_807FB34(void* resource);
void sub_8085260(void* manager, s32 layer);
void sub_8084578(void* manager, s32, s32, s32, s32, s32, s32);
void sub_80847B0(void* manager, s32, s32, s32);
void sub_808520C(void* manager, s32, s32, s32, s32, s32);
void sub_807C298(struct RuntimeObject* object);
void sub_810C05C(struct FieldDisplayProcess* process);

MISC3_SEC(field_finish_display_processes_27c_280)
void field_finish_display_processes_27c_280(void)
{
    struct FieldDisplayProcess* process;
    struct FieldDisplayProcess* secondProcess;

    process = FIELD_RUNTIME->process27C;
    if (process != 0)
        process->update = sub_810C05C;
    secondProcess = FIELD_RUNTIME->process280;
    if (secondProcess != 0)
        secondProcess->update = sub_810C05C;
}

MISC3_SEC(field_update_register_pair_when_owner_active)
void field_update_register_pair_when_owner_active(
    struct FieldDisplayRegisterProcess* process)
{
    s32 active;

    active = process->owner->active;
    if (active == 0) {
        process->update = (void*)active;
        return;
    }
    *(u16*)0x0400001A = *(u16*)0x0200001A;
    *(u16*)0x0400001E = *(u16*)0x0200001E;
}

MISC3_SEC(field_release_display_object_278)
void field_release_display_object_278(void)
{
    struct RuntimeObject* object;

    object = FIELD_RUNTIME->object278;
    if (object != 0) {
        object->value80 = 0;
        sub_807C298(object);
        FIELD_RUNTIME->object278 = 0;
    }
}

MISC3_SEC(field_update_register_pair_and_stop_when_owner_inactive)
void field_update_register_pair_and_stop_when_owner_inactive(
    struct FieldDisplayRegisterProcess* process)
{
    s32 active;

    active = process->owner->active;
    if (active == 0)
        process->update = (void*)active;
    *(u16*)0x0400001A = *(u16*)0x0200001A;
    *(u16*)0x0400001E = *(u16*)0x0200001E;
}

SEC(sub_810C950) void sub_810C950(void)
{
    struct FieldDisplayProcess* process;
    struct FieldDisplayProcess* secondProcess;

    process = FIELD_RUNTIME->process284;
    if (process != 0) {
        sub_807FB34(process->resource);
        FIELD_RUNTIME->process284 = 0;
        process->update = 0;
    }
    secondProcess = FIELD_RUNTIME->process288;
    if (secondProcess != 0) {
        sub_807FB34(secondProcess->resource);
        FIELD_RUNTIME->process288 = 0;
        secondProcess->update = 0;
    }
}

SEC(sub_810CCF4) void sub_810CCF4(void)
{
    struct FieldDisplayProcess* process;
    struct FieldDisplayRuntime* runtime = FIELD_RUNTIME;

    process = runtime->process28C;
    if (process != 0) {
        runtime->process28C = 0;
        process->update = 0;
        sub_8085260(runtime->displayManager, 2);
        sub_8085260(FIELD_RUNTIME->displayManager, 3);
    }
}

SEC(sub_810CDB4) void sub_810CDB4(void)
{
    struct FieldDisplayRuntime* runtime = FIELD_RUNTIME;

    if (runtime->process290 != 0) {
        sub_8085260(runtime->displayManager, 4);
        sub_8085260(FIELD_RUNTIME->displayManager, 5);
        FIELD_RUNTIME->process290->update = (void*)0x0810CD99;
    }
}

SEC(sub_810D00C) void sub_810D00C(void)
{
    sub_8085260(FIELD_RUNTIME->displayManager, 0);
    sub_8085260(FIELD_RUNTIME->displayManager, 1);
}

SEC(sub_810D038) void sub_810D038(s32 value)
{
    sub_810D00C();
    sub_8084578(FIELD_RUNTIME->displayManager, 0, 0, 0xD, 0, 0x12, 3);
    sub_80847B0(FIELD_RUNTIME->displayManager, 1, 0, 0);
    sub_808520C(FIELD_RUNTIME->displayManager, 0, 7, 6, value, 0x91);
}

void field_release_display_processes_284_288(void)
    __attribute__((alias("sub_810C950")));
void field_release_display_process_28c_and_layers_2_3(void)
    __attribute__((alias("sub_810CCF4")));
void field_finish_display_process_290_and_layers_4_5(void)
    __attribute__((alias("sub_810CDB4")));
void field_disable_display_layers_0_1(void)
    __attribute__((alias("sub_810D00C")));
void field_configure_display_layer(s32 value)
    __attribute__((alias("sub_810D038")));
