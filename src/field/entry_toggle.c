#include "field/entry_toggle.h"

u8 sub_8120E90(void* source, u8 entry);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_80FAEC4)
void field_toggle_target_flag_a0_02_if_entry_matches(
    struct FieldEntryMatchOwner* owner,
    struct FieldEntryToggleTarget* target,
    u8 entry)
{
    if (sub_8120E90(owner->matchSource14, entry) == 1)
        target->flagsA0 ^= 2;
}
