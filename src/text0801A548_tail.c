#include "global.h"
#include "common.h"
#include "process/process.h"

struct UnknownScreenProcess {
    struct Process process;
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    u16 pad24;
    u16 originX;
    u16 originY;
    struct Sprite* spriteTop;
    struct Sprite* spriteRight;
    struct Sprite* spriteBottom;
    struct Sprite* spriteLeft;
    s16* volatile scroll;
    struct Process* field40;
    void* field44;
    void* field48;
};

void sub_8057C9C(void*, int, int);
void sub_8057B58(void*, int);
void sub_81166AC(void*, int);

void sub_8051A00(struct UnknownScreenProcess* self) {
    self->scroll[0] = self->originX - self->x;
    self->scroll[1] = self->originY - self->y;

    if (self->y == 0)
        sprite_hide_8021F20(self->spriteTop);
    else
        sprite_show_8020CBC(self->spriteTop);

    if (self->x == self->width - 0xF0)
        sprite_hide_8021F20(self->spriteRight);
    else
        sprite_show_8020CBC(self->spriteRight);

    if (self->y == self->height - 0xA0)
        sprite_hide_8021F20(self->spriteBottom);
    else
        sprite_show_8020CBC(self->spriteBottom);

    if (self->x == 0)
        sprite_hide_8021F20(self->spriteLeft);
    else
        sprite_show_8020CBC(self->spriteLeft);
}

void sub_8051A80(void) {
    u32 value = gGameState.field_880;

    sub_8020A78();
    dword_3000D48(stru_203FFB8.field_3C, stru_203FFB8.field_3C + 0xA14);
    value = dword_3000D4C(stru_203FFB8.field_3C, value);
    gGameState.field_880 = value;
}

void sub_8051ACC(struct UnknownScreenProcess* self) {
    if (self->x < 0)
        self->x = 0;
    else if (self->x > self->width - 0xF0)
        self->x = self->width - 0xF0;

    if (self->y < 0)
        self->y = 0;
    else if (self->y > self->height - 0xA0)
        self->y = self->height - 0xA0;

    sub_8057C9C(self->field44, self->x, self->y);
}

void sub_8051B18(struct UnknownScreenProcess* self, u32 flags) {
    self->process.definition = (struct ProcessDefinition*)0x08CDC1A8;
    sub_8021FD4();
    if (self->field44 != 0)
        sub_8057B58(self->field44, 3);
    if (self->field40 != 0) {
        self->field40->definition = (struct ProcessDefinition*)0x08CDC1B8;
        process_remove(self->field40, 3);
    }
    if (self->field48 != 0)
        sub_81166AC(self->field48, 3);
    process_remove(&self->process, flags);
}

void sub_8051B68(struct UnknownScreenProcess* self, u32 flags) {
    self->process.definition = (struct ProcessDefinition*)0x08CDC1B8;
    process_remove(&self->process, flags);
}

struct UnknownScreenProcess* sub_8051B7C(struct UnknownScreenProcess* self, u8 priority,
                                         char* label) {
    process_add(&self->process, priority, label);
    self->process.definition = (struct ProcessDefinition*)0x08CDC1B8;
    return self;
}
