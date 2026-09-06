#ifndef GUARD_FIELD_DISPLAY_TRANSFER_H
#define GUARD_FIELD_DISPLAY_TRANSFER_H

#include "process/types.h"

struct FieldDisplayTransfer {
    struct Process process;
    u8 phase;
};

#define field_display_transfer_toggle_phase sub_81169C8
void field_display_transfer_toggle_phase(struct FieldDisplayTransfer* transfer);

#endif
