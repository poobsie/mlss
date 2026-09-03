#include "global.h"
#include "process/process.h"

#define SEC(name) __attribute__((section(".text.process_destructors." #name)))

#define DEFINE_PROCESS_DESTRUCTOR(name, descriptor)                    \
    SEC(name) void name(struct Process *process, u32 flags)             \
    {                                                                    \
        process->definition = (struct ProcessDefinition *)(descriptor); \
        process_remove(process, flags);                                 \
    }

DEFINE_PROCESS_DESTRUCTOR(sub_81367AC, 0x08CDC4A0)
DEFINE_PROCESS_DESTRUCTOR(sub_8168294, 0x08CDD140)
DEFINE_PROCESS_DESTRUCTOR(sub_816D96C, 0x08CDD220)
DEFINE_PROCESS_DESTRUCTOR(sub_8171FC0, 0x08CDD290)

void process_destroy_definition_bd98(struct Process* process, u32 flags)
    __attribute__((section(".text.early_system_helpers.sub_801B85C")));
void process_destroy_definition_bd98(struct Process* process, u32 flags)
{
    process->definition = (struct ProcessDefinition*)0x08CDBD98;
    process_remove(process, flags);
}
