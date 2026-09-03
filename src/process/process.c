#include "global.h"
#include "common.h"
#include "process/process.h"

#define PROCESS_DISABLED 0
#define PROCESS_ENABLED  1

struct Process* process_add(struct Process* process, u8 priority, char* label) {
    u32 initialListPosition;
    struct Process* latestProcess;
    char* destLabel;

    process->definition = &gBaseProcessDefinition;
    initialListPosition = 0;
    latestProcess = gGameState.processListHead;

    if (latestProcess == NULL) {
        gGameState.processListHead = process;
        process->previous = NULL;
        process->next = NULL;
        destLabel = process->label;
    } else {
        if (latestProcess == NULL) {
        out:
            latestProcess->next = process;
            process->previous = latestProcess;
            process->next = NULL;
            initialListPosition++;
        } else {
            destLabel = process->label;

            while (latestProcess->priority <= priority) {
                if (latestProcess->next == NULL) {
                    //! Possible fake match.
                    goto out;
                }

                latestProcess = latestProcess->next;
                initialListPosition++;
            }

            if (latestProcess->previous == NULL) {
                gGameState.processListHead = process;
                process->previous = NULL;
                process->next = latestProcess;
                latestProcess->previous = process;
            } else {
                latestProcess->previous->next = process;
                process->previous = latestProcess->previous;
                process->next = latestProcess;
                latestProcess->previous = process;
            }
        }
    }

    process->parentProcess = gGameState.currentProcess;
    process->initialListPosition = initialListPosition;
    process->state = 0;
    process->priority = priority;
    process->enabled = PROCESS_ENABLED;
    process->yielded = TRUE;
    process->executionRate = 1;
    process->executionCounter = 0;
    process->frames = 0;
    COPY_LABEL(destLabel, label);
    gGameState.activeProcessCount++;

    return process;
}

void process_execute_all(void) {
    struct Process* exeProcess;
    struct Process* process;
    bool32 stopExecuting;

    if (gGameState.processListHead != 0) {
        do {
            stopExecuting = TRUE;

            exeProcess = gGameState.processListHead;
            while (exeProcess != NULL) {
                gGameState.nextProcessToExecute = exeProcess->next;
                gGameState.currentProcess = exeProcess;

                if (exeProcess->enabled & PROCESS_ENABLED && !exeProcess->yielded) {
                    s8 executionRate = exeProcess->executionRate;

                    if (executionRate & 8) {
                        if (++exeProcess->executionCounter >= -executionRate) {
                            exeProcess->definition->update((u8*)exeProcess
                                                           + exeProcess->definition->offset);
                            exeProcess->executionCounter = 0;
                        }

                        if (gGameState.currentProcess != NULL) {
                            exeProcess->frames++;
                            exeProcess->yielded = TRUE;
                        }
                    } else {
                        exeProcess->definition->update((u8*)exeProcess
                                                       + exeProcess->definition->offset);

                        if (gGameState.currentProcess != NULL) {
                            exeProcess->frames++;

                            if (++exeProcess->executionCounter >= exeProcess->executionRate) {
                                exeProcess->yielded = TRUE;
                            } else {
                                stopExecuting = FALSE;
                            }
                        }
                    }
                }

                exeProcess = gGameState.nextProcessToExecute;
            }
        } while (stopExecuting == FALSE);
    }

    process = gGameState.processListHead;
    while (process != NULL) {
        process->yielded = FALSE;

        if (!(process->executionRate & 8)) {
            process->executionCounter = 0;
        }

        process = process->next;
    }
}

bool32 process_exists(struct Process* process) {
    struct Process* curProcess = gGameState.processListHead;

    while (curProcess != NULL) {
        if (curProcess == process) {
            return TRUE;
        }

        curProcess = curProcess->next;
    }

    return FALSE;
}

void process_enable_all(void) {
    struct Process* process = gGameState.processListHead;

    while (process != NULL) {
        process->enabled = PROCESS_ENABLED;
        process->yielded = TRUE;
        process = process->next;
    }
}

void process_disable_all(void) {
    struct Process* process = gGameState.processListHead;

    while (process != NULL) {
        if (process->priority != 0 && process->priority != 255) {
            process->enabled = PROCESS_DISABLED;
            process->yielded = TRUE;
        }
        process = process->next;
    }
}

void process_enable(struct Process* process) {
    process->enabled = PROCESS_ENABLED;
    process->yielded = TRUE;
}

void process_disable(struct Process* process) {
    process->enabled = PROCESS_DISABLED;
    process->yielded = TRUE;
}

void process_remove(struct Process* process, u32 flags) {
    process->definition = &gBaseProcessDefinition;

    if (process->next != NULL) {
        process->next->previous = process->previous;
    }

    if (process->previous == NULL) {
        gGameState.processListHead = process->next;
    } else {
        process->previous->next = process->next;
    }

    gGameState.activeProcessCount--;

    if (gGameState.currentProcess == process) {
        gGameState.currentProcess = NULL;
    }

    if (gGameState.nextProcessToExecute == process) {
        gGameState.nextProcessToExecute = process->next;
    }

    if (flags & PROCESS_REMOVE_FLAGS_FREE) {
        free_heap_8018DA8(process);
    }
}
