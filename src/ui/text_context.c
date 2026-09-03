#include "ui/text_context.h"

#define SEC(name) __attribute__((section(".text.text_upper_structural." #name)))

SEC(sub_8199D5C)
const u8* sub_8199D5C(
    struct TextContext* context, u8 column, u8 row, const u8* cursor)
{
    const u8* previous = context->cursor;
    u32 flags;
    u32 clear;
    context->column = column;
    context->row = row;
    context->cursor = cursor;
    flags = context->flags;
    clear = 0x21;
    clear = -clear;
    clear &= flags;
    context->flags = clear;
    return previous;
}

const u8* text_context_set_cursor(
    struct TextContext*, u8, u8, const u8*)
    __attribute__((alias("sub_8199D5C")));
