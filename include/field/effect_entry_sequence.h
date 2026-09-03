#ifndef GUARD_FIELD_EFFECT_ENTRY_SEQUENCE_H
#define GUARD_FIELD_EFFECT_ENTRY_SEQUENCE_H

#include "global.h"

struct FieldEffectEntryMetadata {
    u8 unknown00[0x14];
    u16 dispatchValue;
};

struct FieldEffectEntry {
    u8 unknown00[0x10];
    struct FieldEffectEntryMetadata* metadata;
};

struct FieldEffectRuntime {
    u8 unknown000[0x248];
    void* dispatchGate;
};

struct FieldEffectProcess {
    u8 unknown00[4];
    void (*update)(struct FieldEffectProcess* process);
    u8 unknown08[4];
    s32 entryId;
    s16 timer;
};

void field_wait_then_dispatch_effect_entry(struct FieldEffectProcess* process);

#endif
