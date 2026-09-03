#include "runtime/functions.h"

#define SEC(name) __attribute__((section(".text.upper.sub_8123340")))

void free_heap_8018D9C(void* pointer);

SEC(runtime_release_global_state_ff4)
void runtime_release_global_state_ff4(void)
{
    void** state = (void**)0x03000FF4;

    if (*state != 0)
        free_heap_8018D9C(*state);
    *state = 0;
}
