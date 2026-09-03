#include "global.h"
#include "field/actor.h"

#define SEC(name) __attribute__((section(".text.field_actor_pair_flags." #name)))
/* Direct members make agbcc reuse the actor register and break the match. */
#define FIELD_AT(pointer, type, offset) (*(type)((u8*)(pointer) + (offset)))

struct FieldActorFlagProcess {
    u8 unknown00[4];
    void (*update)(struct FieldActorFlagProcess* process);
};

void sub_8086F0C(struct FieldActorFlagProcess* process);

SEC(sub_8087AE0) void sub_8087AE0(struct FieldActorFlagProcess* process)
{
    struct FieldRuntime* runtime;
    void* actorA;
    void* actorB;

    runtime = gFieldRuntime;
    actorA = runtime->actorA;
    actorB = runtime->actorB;
    if ((6 & FIELD_AT(actorA, u8*, 0x7E)) == 2) {
        FIELD_AT(actorA, u8*, 0x81) =
            (u8)(FIELD_AT(actorA, u8*, 0x81) | 4);
    }
    if ((6 & FIELD_AT(actorB, u8*, 0x7E)) == 2) {
        FIELD_AT(actorB, u8*, 0x81) =
            (u8)(FIELD_AT(actorB, u8*, 0x81) | 4);
    }
    process->update = sub_8086F0C;
}

void field_mark_primary_actor_pair_when_state_is_two(struct FieldActorFlagProcess* process)
    __attribute__((alias("sub_8087AE0")));
