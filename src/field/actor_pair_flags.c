#include "global.h"
#include "field/actor.h"

#define SEC(name) __attribute__((section(".text.field_actor_pair_flags." #name)))
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
typedef u32 UnknownWord;

struct FieldActorFlagProcess {
    u8 unknown00[4];
    void (*update)(struct FieldActorFlagProcess* process);
};

void sub_8086F0C(struct FieldActorFlagProcess* process);

SEC(sub_8087AE0) void sub_8087AE0(void* arg0)
{
    void* temp_r0;
    void* temp_r2;
    void* temp_r3;

    temp_r0 = *(void**)0x03000FD8;
    temp_r2 = FIELD_AT(temp_r0, void**, 0x70);
    temp_r3 = FIELD_AT(temp_r0, void**, 0x74);
    if ((6 & FIELD_AT(temp_r2, u8*, 0x7E)) == 2) {
        FIELD_AT(temp_r2, u8*, 0x81) = (u8)(FIELD_AT(temp_r2, u8*, 0x81) | 4);
    }
    if ((6 & FIELD_AT(temp_r3, u8*, 0x7E)) == 2) {
        FIELD_AT(temp_r3, u8*, 0x81) = (u8)(FIELD_AT(temp_r3, u8*, 0x81) | 4);
    }
    FIELD_AT(arg0, UnknownWord**, 4) = (UnknownWord*)&sub_8086F0C;
}

void field_mark_primary_actor_pair_when_state_is_two(struct FieldActorFlagProcess* process)
    __attribute__((alias("sub_8087AE0")));
