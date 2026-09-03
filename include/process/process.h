#ifndef GUARD_PROCESS_PROCESS_H
#define GUARD_PROCESS_PROCESS_H

#include "process/types.h"

#define PROCESS_REMOVE_FLAGS_NOTHING 0
#define PROCESS_REMOVE_FLAGS_FREE    1
#define PROCESS_REMOVE_FLAGS_UNKNOWN 2

/* Class identity is unknown; the installed definition address is proven. */
#define process_destroy_definition_bd98 sub_801B85C

struct Process* process_add(struct Process* process, u8 priority, char* label);
void process_execute_all(void);
bool32 process_exists(struct Process* process);
void process_enable_all(void);
void process_disable_all(void);
void process_enable(struct Process* process);
void process_disable(struct Process* process);
void process_remove(struct Process* process, u32 flags);
void process_destroy_definition_bd98(struct Process* process, u32 flags);

#endif
