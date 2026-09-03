#include "common.h"
#include "runtime/functions.h"

void runtime_release_global_resource_callback(void* unused)
    __attribute__((section(".text.text_late_helpers.sub_8150A38")));
void runtime_release_global_resource_callback(void* unused) {
    sub_8021FD4();
}

__attribute__((section(".text.text_late_helpers.sub_8150A38")))
const u16 runtime_release_global_resource_callback_padding = 0;
