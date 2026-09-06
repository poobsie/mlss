#include "field/effect_entry_sequence.h"
#include "field/value_transfer.h"

#define SEC(name) __attribute__((section(".text.field_effect_entry_sequence." #name)))
#define FIELD_RUNTIME (*(struct FieldEffectRuntime**)0x03000FD8)

void sub_810CAD0(void);
struct FieldEffectEntry* sub_8087650(s32 entryId);
void sub_807F708(s32 kind, s32 value, s32 duration, s32 flags, s32 dispatchValue);
void sub_8107360(struct FieldEffectProcess* process);

SEC(sub_81071F0) void sub_81071F0(struct FieldEffectProcess* process)
{
    s32 entryId;
    struct FieldEffectEntry* entry;

    if (field_value_transfer_status(FIELD_RUNTIME->valueTransfer) != 1) {
        entryId = process->entryId;
        sub_810CAD0();
        entry = sub_8087650(entryId);
        if (entry != NULL) {
            sub_807F708(4, 0, 0x20, 0, (s32)entry->metadata->dispatchValue);
        }
        process->timer = 0xC;
        process->update = sub_8107360;
    }
}

void field_wait_then_dispatch_effect_entry(struct FieldEffectProcess* process)
    __attribute__((alias("sub_81071F0")));
