#ifndef GUARD_FIELD_REQUEST_CALLBACK_DISPATCH_H
#define GUARD_FIELD_REQUEST_CALLBACK_DISPATCH_H

#include "global.h"

struct FieldRequestCallbackProcess {
    u8 unknown00[4];
    void (*callback)(struct FieldRequestCallbackProcess* process);
};

#define field_dispatch_request_callback_or_continue sub_8107040

void field_dispatch_request_callback_or_continue(
    struct FieldRequestCallbackProcess* process);

#endif
