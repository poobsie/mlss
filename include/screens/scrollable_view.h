#ifndef GUARD_SCREENS_SCROLLABLE_VIEW_H
#define GUARD_SCREENS_SCROLLABLE_VIEW_H

#include "common.h"
#include "process/process.h"

struct ScrollableViewContent;

struct ScrollableViewProcess {
    struct Process process;
    s16 scrollX;
    s16 scrollY;
    u16 contentWidth;
    u16 contentHeight;
    u16 unknown24;
    u16 originX;
    u16 originY;
    struct Sprite* topArrow;
    struct Sprite* rightArrow;
    struct Sprite* bottomArrow;
    struct Sprite* leftArrow;
    s16* volatile hardwareScroll;
    struct Process* childProcess;
    struct ScrollableViewContent* content;
    void* auxiliary;
};

struct ScrollableViewContent {
    struct Process process;
    u8 unknown01C[0x78];
    void* buffer094;
    void* buffer098;
    void* buffer09C;
    void* buffer0A0;
    void* buffer0A4;
    void* buffer0A8;
    u8 unknown0AC[0x4D8];
    u8 cleanupActive584;
};

#define scrollable_view_update_hardware_and_arrows sub_8051A00
#define scrollable_view_update_persistent_value sub_8051A80
#define scrollable_view_clamp_position sub_8051ACC
#define scrollable_view_destroy sub_8051B18
#define scrollable_view_destroy_process_only sub_8051B68
#define scrollable_view_initialize_process sub_8051B7C
#define scrollable_view_content_destroy sub_8057B58

void scrollable_view_update_hardware_and_arrows(struct ScrollableViewProcess* self);
void scrollable_view_update_persistent_value(void);
void scrollable_view_clamp_position(struct ScrollableViewProcess* self);
void scrollable_view_destroy(struct ScrollableViewProcess* self, u32 flags);
void scrollable_view_destroy_process_only(struct ScrollableViewProcess* self, u32 flags);
struct ScrollableViewProcess* scrollable_view_initialize_process(
    struct ScrollableViewProcess* self, u8 priority, char* label);
void scrollable_view_content_destroy(struct ScrollableViewContent* content,
                                     u32 flags);

#endif
