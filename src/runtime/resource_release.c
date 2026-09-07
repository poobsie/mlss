#include "common.h"
#include "runtime/functions.h"

void runtime_release_global_resource_callback(void* unused)
    __attribute__((section(".text.text_late_helpers.sub_8150A38")));
void runtime_release_global_resource_callback(void* unused) {
    sub_8021FD4();
}

__attribute__((section(".text.text_late_helpers.sub_8150A38")))
const u16 runtime_release_global_resource_callback_padding = 0;

void sub_80208F4(void);

void sub_8021FD4(void)
    __attribute__((section(".text.sub_8021FD4")));
void sub_8021FD4(void) {
    void* allocation = (void*)stru_203FFB8.field_3C;
    if (allocation != 0)
        free_heap_8018D9C(allocation);
    sub_80208F4();
    /* The ownership meaning of this cleared global word is not yet known. */
    *(u32*)0x03000D74 = 0;
}
