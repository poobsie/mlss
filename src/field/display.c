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

MISC3_SEC(field_follow_display_slide_owner)
void field_follow_display_slide_owner(struct FieldDisplaySlideFollower* process)
{
    process->offset = 25 - process->owner->remainingOffset;
    if (process->offset > 23) {
        process->update = 0;
    } else {
        *(u16*)0x0400001A = *(u16*)0x0200001A - 24;
        *(u16*)0x0400001E = *(u16*)0x0200001E - 24;
    }
}

SEC(sub_810CDFC)
void field_update_display_window_geometry(
    struct FieldDisplayWindowProcess* process)
{
    struct FieldDisplayProcess* owner = FIELD_RUNTIME->process290;
    s32 left;

    if (owner->value12 <= 63) {
        left = 8;
    } else {
        left = owner->value12 / 256;
    }
    *(u32*)0x04000018 = (u16)(left - 7) | ((process->value16 - 6) << 16);
    *(u32*)0x04000048 = 0x3F3B3F3F;
    *(u32*)0x04000040 = 0x7FF07FF0;
    *(u32*)0x04000044 =
        (*(volatile u16*)0x0200001A + 0x99) |
        ((*(volatile u16*)0x0200001A + 0x8E) << 8) |
        (((*(volatile u16*)0x0200001A + 0x99) |
          ((*(volatile u16*)0x0200001A + 0x8E) << 8)) << 16);
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

void sub_81092B8(void* context);
void sub_810971C(void* context);

SEC(sub_810D228)
void sub_810D228(s32 x, s32 y, s32 z)
{
    u8* state = *(u8**)((u8*)FIELD_RUNTIME + 0x278);

    *(u32*)(state + 0x84) = (u32)x << 8;
    *(u32*)(state + 0x10) = (u32)x << 8;
    *(u32*)(state + 0x88) = (u32)y << 8;
    *(u32*)(state + 0x14) = (u32)y << 8;
    *(u32*)(state + 0x8C) = (u32)z << 8;
    *(u32*)(state + 0x18) = (u32)z << 8;
}

void sub_8108F14(s32 value);

struct FieldDisplayGlobalFlags {
    u8 unknown00[0x3E];
    u16 flags3E;
};

#define DISPLAY_GLOBAL_FLAGS \
    (*(volatile struct FieldDisplayGlobalFlags*)0x0300034C)

MISC3_SEC(sub_810D57C)
void sub_810D57C(void)
{
    if (DISPLAY_GLOBAL_FLAGS.flags3E & 1) {
        u8* state = *(u8**)((u8*)FIELD_RUNTIME + 0x80) + 0xEC;
        if (*(s16*)state == -1)
            sub_8108F14(0);
        else
            sub_8108F14(1);
    }
    if (DISPLAY_GLOBAL_FLAGS.flags3E & 2) {
        u8* state = *(u8**)((u8*)FIELD_RUNTIME + 0x80) + 0xEC;
        if (*(s16*)state == -2)
            sub_8108F14(0);
        else
            sub_8108F14(1);
    }
}

static const u16 sub_810D57C_padding
    __attribute__((section(".text.misc_helpers_03.sub_810D57C"))) = 0;

struct FieldDisplayProgressState {
    u8 unknown00[0x16];
    s16 value16;
};

struct FieldDisplayProgressProcess {
    u8 unknown00[4];
    void (*update)(struct FieldDisplayProgressProcess* process);
    u8 unknown08[4];
    struct FieldDisplayProgressState* state0C;
};

SEC(sub_810D694)
void sub_810D694(struct FieldDisplayProgressProcess* process)
{
    struct FieldDisplayProgressState* state = process->state0C;

    state->value16 += 3;
    if (state->value16 > *(volatile u16*)0x0200001A) {
        state->value16 = *(volatile u16*)0x0200001A;
        process->update = (void*)0x0810CEC1;
    }
}

SEC(sub_810D6C4)
void sub_810D6C4(void* context)
{
    s16* value = (s16*)((u8*)FIELD_RUNTIME + 0x314);

    *value -= 0x400;
    if (*value > 0) {
        sub_810971C(context);
    } else {
        *value = 0;
        sub_81092B8(context);
        sub_810971C(context);
    }
}

static const u16 sub_810D6C4_padding
    __attribute__((section(".text.field_display.sub_810D6C4"))) = 0;

MISC3_SEC(sub_810D70C)
void sub_810D70C(struct FieldDisplayRegisterProcess* process)
{
    *(volatile u16*)0x0400001A =
        *(volatile u16*)0x0200001A + process->value14;
    *(volatile u16*)0x0400001E =
        *(volatile u16*)0x0200001E + process->value14;
    process->update = 0;
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
