#include "global.h"
#include "mario_bros/command_context.h"

void mb2_read_byte24(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte24 = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte2C(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2C = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte2D(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2D = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte2E(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2E = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte2F(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte2F = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte1E(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte1E = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte1F(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte1F = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte26(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte26 = *ctx->cursor;
    ctx->cursor++;
}

void mb2_read_byte27(void* unused, struct MarioBrosCommandContext* ctx) {
    ctx->byte27 = *ctx->cursor;
    ctx->cursor++;
}

void mb2_command_noop(void) {
}
