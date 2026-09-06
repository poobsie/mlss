#include "field/display_transfer.h"
#define SEC(symbol) __attribute__((section(".text.field_display_transfer." #symbol)))

SEC(sub_81169C8)
void field_display_transfer_toggle_phase(struct FieldDisplayTransfer* transfer)
{
    transfer->phase ^= 1;
}

SEC(sub_81169C8)
const u16 sub_81169C8_padding = 0;
