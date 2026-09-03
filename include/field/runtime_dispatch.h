#ifndef GUARD_FIELD_RUNTIME_DISPATCH_H
#define GUARD_FIELD_RUNTIME_DISPATCH_H

#include "global.h"

struct FieldDispatchProcess;

#define field_prepare_active_object_for_flag_80 sub_8087360
#define field_restore_saved_callback_when_active_flag_clear sub_810707C

void field_prepare_active_object_for_flag_80(void);
void field_restore_saved_callback_when_active_flag_clear(
    struct FieldDispatchProcess* process);

#endif
