#include "runtime/definition_slot.h"
void free_heap_8018DA8(void* object);

void definition_slot_destroy(struct DefinitionSlot* slot, u32 flags)
    __attribute__((section(".text.sub_816166C")));
void definition_slot_destroy(struct DefinitionSlot* slot, u32 flags) {
    slot->definition = (const void*)0x08CDD0B8;
    if (flags & 1)
        free_heap_8018DA8(slot);
}
void definition_slot_initialize(struct DefinitionSlot* slot)
    __attribute__((section(".text.sub_816168C")));
void definition_slot_initialize(struct DefinitionSlot* slot) {
    slot->definition = (const void*)0x08CDD0B8;
}
