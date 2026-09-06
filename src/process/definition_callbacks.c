#include "common.h"
#include "process/process.h"
#include "ui/functions.h"
#include "audio/sound_effects.h"

#define SEC(name) __attribute__((section(".text.process_definition_callbacks." #name)))

struct UiValueTracker {
    u8 gap00[0x18];
    s32 value18;
    u8 gap1C[0x34];
    s32 peakValue50;
};

struct UiCountdown {
    u8 gap00[0x18];
    s32 remaining18;
    s32 subcounter1C;
};

struct UiDelayedCountdown {
    u8 gap00[0x6C];
    s32 remaining6C;
    s32 subcounter70;
};

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

SEC(sub_816D814)
void sub_816D814(struct UiValueTracker* tracker)
{
    tracker->value18 = 0;
    tracker->peakValue50 = 0;
}

SEC(sub_816D898)
void sub_816D898(struct UiCountdown* countdown)
{
    countdown->remaining18 = 60;
    countdown->subcounter1C = 0;
}
SEC(sub_816D898) const u16 sub_816D898_padding = 0;

SEC(sub_8171DF0)
void sub_8171DF0(struct DefinitionD278Process* process)
{
    if (process->sound97ActiveEA == 0) {
        process->sound97ActiveEA++;
        sound_effect_play(0x97, SOUND_VOLUME_UNCHANGED);
    }
}
SEC(sub_8171DF0) const u16 sub_8171DF0_padding = 0;

SEC(sub_8171F44)
void sub_8171F44(struct UiDelayedCountdown* countdown)
{
    countdown->remaining6C = 180;
    countdown->subcounter70 = 0;
}
SEC(sub_8171F44) const u16 sub_8171F44_padding = 0;
