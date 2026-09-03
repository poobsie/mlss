#include "process/process.h"

void free_heap_8018D9C(void* pointer);

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
