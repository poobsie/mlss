#ifndef GUARD_FIELD_DISPLAY_H
#define GUARD_FIELD_DISPLAY_H

#include "global.h"

struct RuntimeObject;

struct FieldDisplayProcess {
    u8 unknown00[4];
    void (*update)(struct FieldDisplayProcess* process);
    void* resource;
};

struct FieldDisplayRegisterOwner {
    u8 unknown00[4];
    s32 active;
};

struct FieldDisplayRegisterProcess {
    u8 unknown00[4];
    void (*update)(struct FieldDisplayRegisterProcess* process);
    struct FieldDisplayRegisterOwner* owner;
};

struct FieldDisplayRuntime {
    u8 unknown000[0x250];
    void* displayManager;
    u8 unknown254[0x24];
    struct RuntimeObject* object278;
    struct FieldDisplayProcess* process27C;
    struct FieldDisplayProcess* process280;
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
#define field_finish_display_processes_27c_280 sub_810CAD0
#define field_update_register_pair_when_owner_active sub_810CBDC
#define field_release_display_object_278 sub_810D170
#define field_update_register_pair_and_stop_when_owner_inactive sub_810D5F4

void field_finish_display_processes_27c_280(void);
void field_update_register_pair_when_owner_active(
    struct FieldDisplayRegisterProcess* process);
void field_release_display_object_278(void);
void field_update_register_pair_and_stop_when_owner_inactive(
    struct FieldDisplayRegisterProcess* process);

#endif
