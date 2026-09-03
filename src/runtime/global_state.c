#include "runtime/functions.h"

#define SEC(name) __attribute__((section(".text.upper.sub_8123340")))

void free_heap_8018D9C(void* pointer);
void heap_free_block(void* pointer);

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))

SEC(runtime_release_global_state_ff4)
void runtime_release_global_state_ff4(void)
{
    void** state = (void**)0x03000FF4;

    if (*state != 0)
        free_heap_8018D9C(*state);
    *state = 0;
}

MISC_SEC(runtime_release_global_state_fb4)
void runtime_release_global_state_fb4(void)
{
    heap_free_block(*(void**)0x03000FB4);
}

MISC_SEC(runtime_release_global_state_fc4)
void runtime_release_global_state_fc4(void)
{
    heap_free_block(*(void**)0x03000FC4);
}

MISC_SEC(runtime_release_and_clear_global_state_fc0)
void runtime_release_and_clear_global_state_fc0(void)
{
    void** state = (void**)0x03000FC0;
    heap_free_block(*state);
    *state = 0;
}
