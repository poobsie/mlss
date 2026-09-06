#include "common.h"
#include "process/process.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define UPPER_SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))
#define SEC(name) __attribute__((section(".text.process_definition_initializers." #name)))

UPPER_SEC(process_initialize_tld)
struct Process* process_initialize_tld(
    struct Process* process, u8 priority, char* label)
{
    process_add(process, priority, label);
    process->definition = (struct ProcessDefinition*)0x08CDC3C8;
    return process;
}

UPPER_SEC(process_initialize_definition_c4a0)
struct Process* process_initialize_definition_c4a0(
    struct Process* process, u8 priority, char* label)
{
    process_add(process, priority, label);
    process->definition = (struct ProcessDefinition*)0x08CDC4A0;
    return process;
}

void sub_8167B44(struct Process* process);

#define PREPARE_GRAPHICS_STATE()                                             \
    do {                                                                     \
        sub_8020A78();                                                       \
        dword_3000D48(                                                       \
            stru_203FFB8.field_3C, stru_203FFB8.field_3C + 0xA14);           \
        gGameState.field_880 =                                               \
            dword_3000D4C(stru_203FFB8.field_3C, gGameState.field_880);      \
    } while (0)

SEC(sub_8167D00) void sub_8167D00(struct Process* process)
{
    struct Process* parent = process->parentProcess;

    PREPARE_GRAPHICS_STATE();
    sub_8167B44(parent);
}

#define DEFINE_GRAPHICS_PREPARER(name)              \
    SEC(name) void name(struct Process* process)     \
    {                                                 \
        PREPARE_GRAPHICS_STATE();                    \
    }

DEFINE_GRAPHICS_PREPARER(sub_816AF94)
DEFINE_GRAPHICS_PREPARER(sub_816D538)
DEFINE_GRAPHICS_PREPARER(sub_8171AFC)
