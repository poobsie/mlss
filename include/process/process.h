#ifndef GUARD_PROCESS_PROCESS_H
#define GUARD_PROCESS_PROCESS_H

#include "process/types.h"

#define PROCESS_REMOVE_FLAGS_NOTHING 0
#define PROCESS_REMOVE_FLAGS_FREE    1
#define PROCESS_REMOVE_FLAGS_UNKNOWN 2

/* Class identity is unknown; the installed definition address is proven. */
#define process_destroy_definition_bd98 sub_801B85C
#define process_timed_update sub_801B820
#define process_destroy_owned_buffer sub_801BC98
#define process_remove_global_owned_buffer sub_801BD30
#define process_initialize_tld tld_init_8127A94
#define process_initialize_definition_c4a0 sub_81367C0
#define process_destroy_definition_c4a0 sub_81367AC
#define process_destroy_definition_d140 sub_8168294
#define process_prepare_graphics_definition_d140 sub_8167D00
#define process_destroy_definition_d1b0 sub_816B3C4
#define process_prepare_graphics_definition_d1b0 sub_816AF94
#define process_destroy_definition_d220 sub_816D96C
#define process_prepare_graphics_definition_d220 sub_816D538
#define process_destroy_definition_d290 sub_8171FC0
#define process_prepare_graphics_definition_d290 sub_8171AFC
#define process_definition_d140_advance_to_state4_on_start sub_8167DF8
#define process_definition_d140_reset_ui_objects sub_8167E30
#define process_definition_d278_advance_to_state4_on_start sub_8171B44
#define process_definition_d278_hide_sprite_pairs sub_8171BF0
#define process_definition_d278_start_sound_97_once sub_8171DF0

struct Process* process_add(struct Process* process, u8 priority, char* label);
void process_execute_all(void);
bool32 process_exists(struct Process* process);
void process_enable_all(void);
void process_disable_all(void);
void process_enable(struct Process* process);
void process_disable(struct Process* process);
void process_remove(struct Process* process, u32 flags);
void process_destroy_definition_bd98(struct Process* process, u32 flags);
void process_destroy_definition_d1b0(struct Process* process, u32 flags);
void process_prepare_graphics_definition_d140(struct Process* process);
void process_prepare_graphics_definition_d1b0(struct Process* process);
void process_prepare_graphics_definition_d220(struct Process* process);
void process_prepare_graphics_definition_d290(struct Process* process);
void process_definition_d140_advance_to_state4_on_start(
    struct DefinitionD140Process* process);
void process_definition_d140_reset_ui_objects(
    struct DefinitionD140Process* process, void* value20, void* value24);
void process_definition_d278_advance_to_state4_on_start(
    struct DefinitionD278Process* process);
void process_definition_d278_hide_sprite_pairs(
    struct DefinitionD278Process* process);
void process_definition_d278_start_sound_97_once(
    struct DefinitionD278Process* process);
void process_timed_update(struct TimedProcess* process);
void process_destroy_owned_buffer(struct OwnedBufferProcess* process, u32 flags);
void process_remove_global_owned_buffer(void);
struct Process* process_initialize_tld(
    struct Process* process, u8 priority, char* label);
struct Process* process_initialize_definition_c4a0(
    struct Process* process, u8 priority, char* label);

#endif
