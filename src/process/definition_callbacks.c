#include "common.h"
#include "process/process.h"
#include "ui/functions.h"

#define SEC(name) __attribute__((section(".text.process_definition_callbacks." #name)))

SEC(sub_8167DF8)
void sub_8167DF8(struct DefinitionD140Process* process)
{
    if (gGameState.field_2A & START_BUTTON)
        process->state54 = 4;
}

SEC(sub_8167E30)
void sub_8167E30(
    struct DefinitionD140Process* process, void* value20, void* value24)
{
    ui_object_reset(process->object20, value20);
    ui_object_reset(process->object24, value24);
}
SEC(sub_8167E30) const u16 sub_8167E30_padding = 0;

SEC(sub_8171B44)
void sub_8171B44(struct DefinitionD278Process* process)
{
    if (gGameState.field_2A & START_BUTTON)
        process->state44 = 4;
}

SEC(sub_8171BF0)
void sub_8171BF0(struct DefinitionD278Process* process)
{
    ui_sprite_pair_hide(process->spritePair6C);
    ui_sprite_pair_hide(process->spritePair70);
}
SEC(sub_8171BF0) const u16 sub_8171BF0_padding = 0;
