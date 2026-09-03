#include "global.h"
#include "process/process.h"

#define SEC(name) __attribute__((section(".text.process_callback_owner." #name)))

typedef u32 (*ProcessOwnerCallback)(s32 value);

struct ProcessCallbackOwner {
    u8 unknown00[0x18];
    const void* descriptor;
    s32 resourceId;
    ProcessOwnerCallback callback;
    s32 callbackValue;
};

void sub_80E4FC8();
void heap_free_block();

SEC(sub_807A658) void sub_807A658(struct ProcessCallbackOwner* owner, s32 flags)
{
    ProcessOwnerCallback callback;

    owner->descriptor = (void*)0x08CDC2D8;
    if (owner->resourceId != -1) {
        sub_80E4FC8();
        if (owner->resourceId != 0) {
            heap_free_block();
        }
        callback = owner->callback;
        if (callback != NULL) {
            callback(owner->callbackValue);
        }
    }
    process_remove((struct Process*)owner, flags);
}

void process_destroy_callback_owner(struct ProcessCallbackOwner* owner, s32 flags)
    __attribute__((alias("sub_807A658")));
