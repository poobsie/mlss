#include "field/request_callback_dispatch.h"

#define SEC(symbol) __attribute__((section(".text.field_request_callback_dispatch." #symbol)))
#define FIELD_RUNTIME (*(struct FieldRequestCallbackRuntime**)0x03000FD8)
#define FIELD_DISPATCH (*(struct FieldRequestCallbackDispatch**)0x03000FDC)

struct FieldRequestCallbackOwner {
    u8 unknown00[0x4C];
    void (*callback4C)(struct FieldRequestCallbackOwner* owner);
};

struct FieldRequestCallback {
    u8 unknown00[8];
    struct FieldRequestCallbackOwner owner08;
};

struct FieldRequestCallbackRuntime {
    u8 unknown000[0x7C];
    struct FieldRequestCallback* request7C;
};

struct FieldRequestCallbackDispatch {
    u8 unknown0000[0x8E58];
    void (*callback8E58)(struct FieldRequestCallbackProcess* process);
};

SEC(sub_8107040)
void field_dispatch_request_callback_or_continue(
    struct FieldRequestCallbackProcess* process)
{
    struct FieldRequestCallbackOwner* owner;
    void (*callback)(struct FieldRequestCallbackOwner* owner);

    owner = &FIELD_RUNTIME->request7C->owner08;
    callback = owner->callback4C;
    if (callback != 0) {
        callback(owner);
    } else {
        process->callback = FIELD_DISPATCH->callback8E58;
        process->callback(process);
    }
}
