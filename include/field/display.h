#ifndef GUARD_FIELD_DISPLAY_H
#define GUARD_FIELD_DISPLAY_H

#include "global.h"

struct FieldDisplayProcess {
    u8 unknown00[4];
    void (*update)(struct FieldDisplayProcess* process);
    void* resource;
};

struct FieldDisplayRuntime {
    u8 unknown000[0x250];
    void* displayManager;
    u8 unknown254[0x30];
    struct FieldDisplayProcess* process284;
    struct FieldDisplayProcess* process288;
    struct FieldDisplayProcess* process28C;
    struct FieldDisplayProcess* process290;
};

void field_release_display_processes_284_288(void);
void field_release_display_process_28c_and_layers_2_3(void);
void field_finish_display_process_290_and_layers_4_5(void);
void field_disable_display_layers_0_1(void);
void field_configure_display_layer(s32 value);

#endif
