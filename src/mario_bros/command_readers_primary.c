#include "global.h"
#include "mario_bros/command_context.h"

void mb_read_value_24(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte24 = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2C(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2C = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2D(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2D = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2E(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2E = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_2F(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2F = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_1E(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte1E = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_1F(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte1F = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_26(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte26 = *ctx->cursor;
    ctx->cursor++;
}

void mb_read_value_27(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte27 = *ctx->cursor;
    ctx->cursor++;
}

void mb_command_noop(void) {
}
