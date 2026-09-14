#include "process/process.h"
#include "memory/heap.h"

#define GLOBAL_OWNED_BUFFER_PROCESS (*(struct OwnedBufferProcess**)0x03000D44)
#define OWNED_BUFFER_PROCESS_LABEL ((char*)0x081E23C8)

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
    struct OwnedBufferProcess* process = GLOBAL_OWNED_BUFFER_PROCESS;
    if (process != 0) {
        process_destroy_owned_buffer(process, 3);
        GLOBAL_OWNED_BUFFER_PROCESS = 0;
    }
}

__attribute__((section(".text.sub_801BD50")))
void process_ensure_global_owned_buffer(u32 priority) {
    if (GLOBAL_OWNED_BUFFER_PROCESS == 0) {
        GLOBAL_OWNED_BUFFER_PROCESS = time_init(
            alloc_Zero(0x2C, 0, OWNED_BUFFER_PROCESS_LABEL, 0),
            priority, OWNED_BUFFER_PROCESS_LABEL);
        process_disable(&GLOBAL_OWNED_BUFFER_PROCESS->process);
    }
}
