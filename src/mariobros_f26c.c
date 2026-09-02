#include "global.h"

struct MbCommandContext {
    u8 pad_00[0x1E];
    u8 value_1E;
    u8 value_1F;
    u8 pad_20[4];
    u8 value_24;
    u8 pad_25;
    u8 value_26;
    u8 value_27;
    u8 pad_28[4];
    u8 value_2C;
    u8 value_2D;
    u8 value_2E;
    u8 value_2F;
    u8 pad_30[0x10];
    u8* cursor;
};

void mb_read_value_24(void* unused, struct MbCommandContext* ctx) {
    ctx->value_24 = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2C(void* unused, struct MbCommandContext* ctx) {
    ctx->value_2C = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2D(void* unused, struct MbCommandContext* ctx) {
    ctx->value_2D = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2E(void* unused, struct MbCommandContext* ctx) {
    ctx->value_2E = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2F(void* unused, struct MbCommandContext* ctx) {
    ctx->value_2F = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_1E(void* unused, struct MbCommandContext* ctx) {
    ctx->value_1E = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_1F(void* unused, struct MbCommandContext* ctx) {
    ctx->value_1F = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_26(void* unused, struct MbCommandContext* ctx) {
    ctx->value_26 = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_27(void* unused, struct MbCommandContext* ctx) {
    ctx->value_27 = *ctx->cursor;
    ctx->cursor++;
}

void mb_command_noop(void) {
}
