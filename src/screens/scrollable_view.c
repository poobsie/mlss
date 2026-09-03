#include "screens/scrollable_view.h"

void sub_8057C9C(void*, int, int);
void sub_81166AC(void*, int);

void scrollable_view_update_hardware_and_arrows(struct ScrollableViewProcess* self) {
    self->hardwareScroll[0] = self->originX - self->scrollX;
    self->hardwareScroll[1] = self->originY - self->scrollY;

    if (self->scrollY == 0)
        sprite_hide_8021F20(self->topArrow);
    else
        sprite_show_8020CBC(self->topArrow);

    if (self->scrollX == self->contentWidth - 0xF0)
        sprite_hide_8021F20(self->rightArrow);
    else
        sprite_show_8020CBC(self->rightArrow);

    if (self->scrollY == self->contentHeight - 0xA0)
        sprite_hide_8021F20(self->bottomArrow);
    else
        sprite_show_8020CBC(self->bottomArrow);

    if (self->scrollX == 0)
        sprite_hide_8021F20(self->leftArrow);
    else
        sprite_show_8020CBC(self->leftArrow);
}

void scrollable_view_update_persistent_value(void) {
    u32 value = gGameState.field_880;

    sub_8020A78();
    dword_3000D48(stru_203FFB8.field_3C, stru_203FFB8.field_3C + 0xA14);
    value = dword_3000D4C(stru_203FFB8.field_3C, value);
    gGameState.field_880 = value;
}

void scrollable_view_clamp_position(struct ScrollableViewProcess* self) {
    if (self->scrollX < 0)
        self->scrollX = 0;
    else if (self->scrollX > self->contentWidth - 0xF0)
        self->scrollX = self->contentWidth - 0xF0;

    if (self->scrollY < 0)
        self->scrollY = 0;
    else if (self->scrollY > self->contentHeight - 0xA0)
        self->scrollY = self->contentHeight - 0xA0;

    sub_8057C9C(self->content, self->scrollX, self->scrollY);
}

void scrollable_view_destroy(struct ScrollableViewProcess* self, u32 flags) {
    self->process.definition = (struct ProcessDefinition*)0x08CDC1A8;
    sub_8021FD4();
    if (self->content != 0)
        scrollable_view_content_destroy(self->content, 3);
    if (self->childProcess != 0) {
        self->childProcess->definition = (struct ProcessDefinition*)0x08CDC1B8;
        process_remove(self->childProcess, 3);
    }
    if (self->auxiliary != 0)
        sub_81166AC(self->auxiliary, 3);
    process_remove(&self->process, flags);
}

void scrollable_view_destroy_process_only(struct ScrollableViewProcess* self, u32 flags) {
    self->process.definition = (struct ProcessDefinition*)0x08CDC1B8;
    process_remove(&self->process, flags);
}

struct ScrollableViewProcess* scrollable_view_initialize_process(
    struct ScrollableViewProcess* self, u8 priority, char* label) {
    process_add(&self->process, priority, label);
    self->process.definition = (struct ProcessDefinition*)0x08CDC1B8;
    return self;
}
