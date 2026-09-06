#include "runtime/functions.h"

#include "memory/heap.h"
#include "gba/syscall.h"

#define SEC(name) __attribute__((section(".text.upper.sub_8123340")))

void free_heap_8018D9C(void* pointer);

typedef void (*RuntimeMemoryFill)(u32 value, void* destination, u32 size);

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))
#define MISC2_SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))

MISC2_SEC(runtime_release_global_state_fbc)
void runtime_release_global_state_fbc(void)
{
    void** state = (void**)0x03000FBC;

    if (*state != 0) {
        heap_free_block(*state);
        *state = 0;
    }
}

MISC2_SEC(runtime_initialize_global_state_fbc)
void runtime_initialize_global_state_fbc(void)
{
    void** stateSlot = (void**)0x03000FBC;
    void* state = heap_alloc_block(TRUE, 0x34, (const char*)0x08200180);
    RuntimeMemoryFill fill;

    *stateSlot = state;
    fill = *(RuntimeMemoryFill*)0x03001034;
    fill(0, state, 0x34);
}

MISC2_SEC(runtime_release_global_state_fb4_fb8_fbc)
void runtime_release_global_state_fb4_fb8_fbc(void)
{
    void** state;

    runtime_release_global_state_fb4();
    state = (void**)0x03000FB8;
    if (*state != 0) {
        heap_free_block(*state);
        *state = 0;
    }
    runtime_release_global_state_fbc();
}

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

MISC_SEC(runtime_initialize_global_state_fc4)
void runtime_initialize_global_state_fc4(void)
{
    register void** stateSlot asm("r6") = (void**)0x03000FC4;
    register const u8* copyEnd asm("r4") = (const u8*)0x08001010;
    register const u8* copyStart asm("r5") = (const u8*)0x08000F9C;
    u32 size;
    void* state;

    asm("" : "+r"(stateSlot), "+r"(copyEnd), "+r"(copyStart));
    size = copyEnd - copyStart;
    state = heap_alloc_block(FALSE, size, (const char*)0x08200198);

    *stateSlot = state;
    CpuSet(copyStart, state, (size << 10) >> 11);
}

MISC_SEC(runtime_release_and_clear_global_state_fc0)
void runtime_release_and_clear_global_state_fc0(void)
{
    void** state = (void**)0x03000FC0;
    heap_free_block(*state);
    *state = 0;
}

MISC_SEC(runtime_initialize_global_state_fc0)
void runtime_initialize_global_state_fc0(void)
{
    void** stateSlot = (void**)0x03000FC0;
    u32 size = 0x570;
    void* state = heap_alloc_block(TRUE, size, (const char*)0x08200190);
    RuntimeMemoryFill fill;

    *stateSlot = state;
    fill = *(RuntimeMemoryFill*)0x03001034;
    fill(0, state, size);
}
