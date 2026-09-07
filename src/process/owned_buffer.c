#include "process/process.h"
#include "memory/heap.h"


void process_destroy_owned_buffer(struct OwnedBufferProcess* process, u32 flags)
    __attribute__((section(".text.early_code_helpers_3.sub_801BC98")));
void process_destroy_owned_buffer(struct OwnedBufferProcess* process, u32 flags) {
    process->process.definition = (struct ProcessDefinition*)0x08CDBDA8;
    if (process->buffer != 0) {
        free_heap_8018D9C(process->buffer);
    }
    process_remove(&process->process, flags);
}

void process_remove_global_owned_buffer(void)
    __attribute__((section(".text.early_code_helpers_3.sub_801BD30")));
void process_remove_global_owned_buffer(void) {
    struct OwnedBufferProcess** slot = (struct OwnedBufferProcess**)0x03000D44;
    struct OwnedBufferProcess* process = *slot;
    if (process != 0) {
        process_destroy_owned_buffer(process, 3);
        *slot = 0;
    }
}

__attribute__((section(".text.sub_801BD50")))
void sub_801BD50(u32 priority) {
    struct OwnedBufferProcess** slot = (struct OwnedBufferProcess**)0x03000D44;
    if (*slot == 0) {
        *slot = time_init(alloc_Zero(0x2C, 0, (char*)0x081E23C8, 0), priority, (char*)0x081E23C8);
        process_disable(&(*slot)->process);
    }
}
