#include "process/process.h"

void sub_801B7B0(struct TimedProcess* process, u8 step, u16 current,
                 u16 limit);

void process_timed_update(struct TimedProcess* process)
    __attribute__((section(".text.early_code_helpers_3.sub_801B820")));
void process_timed_update(struct TimedProcess* process) {
    process->current++;
    sub_801B7B0(process, process->step, process->current, process->limit);
    if ((u32)process->current >= (u32)process->limit && process != NULL) {
        process->process.definition = (struct ProcessDefinition*)0x08CDBD98;
        process_remove(&process->process, 3);
    }
}
