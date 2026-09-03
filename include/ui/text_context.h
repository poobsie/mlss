#ifndef GUARD_UI_TEXT_CONTEXT_H
#define GUARD_UI_TEXT_CONTEXT_H

#include "global.h"

struct TextContext {
    u8 unknown00[8];
    const u8* cursor;
    u8 column;
    u8 row;
    u8 unknown0E[4];
    u8 flags;
};

const u8* text_context_set_cursor(
    struct TextContext* context, u8 column, u8 row, const u8* cursor);

#endif
