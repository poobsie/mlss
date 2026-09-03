#include "process/process.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))

SEC(process_initialize_tld)
struct Process* process_initialize_tld(
    struct Process* process, u8 priority, char* label)
{
    process_add(process, priority, label);
    process->definition = (struct ProcessDefinition*)0x08CDC3C8;
    return process;
}

SEC(process_initialize_definition_c4a0)
struct Process* process_initialize_definition_c4a0(
    struct Process* process, u8 priority, char* label)
{
    process_add(process, priority, label);
    process->definition = (struct ProcessDefinition*)0x08CDC4A0;
    return process;
}
