#include "field/runtime_dispatch.h"
#include "object/runtime_object.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(symbol) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(symbol))))

struct FieldActiveObjectOwner {
    u8 unknown000[8];
    u8 object08[0x11A];
    u8 flags122;
};

static inline struct RuntimeObject* field_active_runtime_object(
    struct FieldActiveObjectOwner* owner)
{
    return (struct RuntimeObject*)owner->object08;
}

struct FieldDispatchRuntime {
    u8 unknown00[0x0C];
    u8 flags0C;
    u8 unknown0D[0x6F];
    struct FieldActiveObjectOwner* activeObjectOwner;
};

struct FieldDispatchProcess {
    u8 unknown00[4];
    void (*update)(struct FieldDispatchProcess* process);
};

struct FieldCallbackStore {
    u8 unknown0000[0x8E58];
    void (*savedCallback)(struct FieldDispatchProcess* process);
};

#define FIELD_RUNTIME (*(struct FieldDispatchRuntime**)0x03000FD8)
#define FIELD_CALLBACK_STORE (*(struct FieldCallbackStore**)0x03000FDC)

void sub_80970B8(struct RuntimeObject* object);
void sub_8097F30(struct RuntimeObject* object);

SEC(field_prepare_active_object_for_flag_80)
void field_prepare_active_object_for_flag_80(void)
{
    struct FieldDispatchRuntime* runtime;

    runtime = FIELD_RUNTIME;
    if (runtime->flags0C & 0x80) {
        sub_8097F30(field_active_runtime_object(runtime->activeObjectOwner));
        return;
    }
    sub_80970B8(field_active_runtime_object(runtime->activeObjectOwner));
}

SEC(field_restore_saved_callback_when_active_flag_clear)
void field_restore_saved_callback_when_active_flag_clear(
    struct FieldDispatchProcess* process)
{
    void (*callback)(struct FieldDispatchProcess* process);

    if (!(FIELD_RUNTIME->activeObjectOwner->flags122 & 0x20)) {
        callback = FIELD_CALLBACK_STORE->savedCallback;
        process->update = callback;
        callback(process);
    }
}
