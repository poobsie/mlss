#ifndef GUARD_RUNTIME_DEFINITION_SLOT_H
#define GUARD_RUNTIME_DEFINITION_SLOT_H
#include "global.h"
struct DefinitionSlot { const void* definition; };
#define definition_slot_destroy sub_816166C
#define definition_slot_initialize sub_816168C
void definition_slot_destroy(struct DefinitionSlot* slot, u32 flags);
void definition_slot_initialize(struct DefinitionSlot* slot);
#endif
