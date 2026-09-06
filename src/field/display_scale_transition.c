#include "field/display_scale_transition.h"

#define SEC(name) __attribute__((section(".text.field_display_scale_transition." #name)))
#define FIELD_RUNTIME (*(struct FieldDisplayScaleRuntime**)0x03000FD8)

struct FieldDisplayScale {
    u8 unknown00[4];
    s16 scale4;
    s16 scale6;
    u8 unknown08[0xA];
    u8 flags12;
};

struct FieldDisplayScaleRuntime {
    u8 unknown000[0xB];
    u8 flags00B;
    u8 unknown00C[0x278];
    struct FieldDisplayScaleProcess* processes284[2];
};

void sub_807FB34(struct FieldDisplayScale* resource);
void sub_807BC90(struct FieldDisplayScale* resource);
void sub_810C2B4(struct FieldDisplayScaleProcess* process);

SEC(sub_810C398)
void field_update_or_release_display_scale(
    struct FieldDisplayScaleProcess* process)
{
    struct FieldDisplayScaleRuntime* runtime;
    struct FieldDisplayScaleProcess* ownedProcess;
    struct FieldDisplayScale* scale;
    s32 slot;
    s8* flags;

    runtime = FIELD_RUNTIME;
    if (runtime->flags00B & 0x80) {
        slot = process->slotAndState16 & 1;
        ownedProcess = runtime->processes284[slot];
        if (ownedProcess != NULL) {
            sub_807FB34(ownedProcess->resource);
            FIELD_RUNTIME->processes284[slot] = NULL;
            ownedProcess->update = NULL;
        }
    } else {
        scale = process->resource;
        scale->scale6 -= 0x40;
        scale->scale4 = scale->scale6;
        if (scale->scale6 <= 0x100) {
            scale->scale6 = 0x100;
            scale->scale4 = 0x100;
            flags = (s8*)&scale->flags12;
            *flags &= -0x11;
            process->update = sub_810C2B4;
        }
        sub_807BC90(scale);
    }
}
