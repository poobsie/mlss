#ifndef GUARD_PROCESS_TYPES_H
#define GUARD_PROCESS_TYPES_H

#include "global.h"

struct ProcessDefinition {
    u32 field_0;
    void (*field_4)(void*);
    s16 offset;
    u16 field_A;
    void (*update)(void*);
};

struct Process {
    u8 state;
    u8 priority;
    s16 enabled : 1;
    s16 yielded : 1;
    s16 executionRate : 4;
    u16 executionCounter : 4;
    u16 initialListPosition : 6;
    u32 frames;
    char label[4];
    struct Process* previous;
    struct Process* next;
    struct Process* parentProcess;
    struct ProcessDefinition* definition;
};

extern struct ProcessDefinition gBaseProcessDefinition __asm__("stru_8CDBD68");

#endif
