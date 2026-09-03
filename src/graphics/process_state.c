#include "graphics/process_state.h"
#include "process/process.h"

#define SEC(name) __attribute__((section(".text.graphics_process_state." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(name) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(name))))
#define MISC2_SEC(name) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(name))))
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))

void free_heap_8018D9C();
void sub_8029888(s32 channel, s32 value);
void sub_80184F4(void* address);
void sub_8058278(struct GraphicsStagingSource* source);
void sub_80582DC(struct GraphicsStagingSource* source);
void sub_80584F8(struct GraphicsStagingSource* source);
void sub_80587BC(struct GraphicsStagingSource* source, s32 mode);

MISC2_SEC(graphics_apply_staging_source)
void graphics_apply_staging_source(struct GraphicsStagingSource* source)
{
    graphics_copy_staging_values(source);
    sub_80582DC(source);
    sub_80587BC(source, 0);
    sub_8058278(source);
    sub_80584F8(source);
}

MISC3_SEC(graphics_copy_compact_staging_values)
void graphics_copy_compact_staging_values(
    struct GraphicsCompactStagingSource* source)
{
    *(s16*)0x02000010 = source->maskedValue0 & 0x1FF;
    *(s16*)0x02000014 = source->maskedValue1 & 0x1FF;
    *(s16*)0x02000012 = source->component0 & 0xFF;
    *(s16*)0x02000016 = source->component1 & 0xFF;
}

SEC(sub_8059F24) void sub_8059F24(struct GraphicsStagingSource* source)
{
    *(s16*)0x02000014 = source->maskedValue0 & 0x1FF;
    *(s16*)0x02000018 = source->maskedValue1 & 0x1FF;
    *(s16*)0x0200001C = source->maskedValue2 & 0x1FF;
    *(s16*)0x02000016 = source->component0;
    *(s16*)0x0200001A = source->component1;
    *(s16*)0x0200001E = source->component2;
}

SEC(sub_805C73C) void sub_805C73C(struct GraphicsProcessState* process, s32 flags)
{
    process->descriptor = (void*)0x08CDC2B8;
    *(s16*)0x040000BA = 0;
    sub_8029888(0, 0);
    process->active = 0;
    if (*(s32*)0x03000E04 != 0) {
        free_heap_8018D9C();
    }
    if (*(s32*)0x03000E00 != 0) {
        free_heap_8018D9C();
    }
    process_remove((struct Process*)process, flags);
}

SEC(sub_805DA1C) void sub_805DA1C(struct GraphicsProcessState* process, s32 flags)
{
    process->descriptor = (void*)0x08CDC2C8;
    sub_80184F4((void*)0x06000000);
    if (process->bufferA4 != 0) {
        free_heap_8018D9C();
    }
    if (process->bufferA8 != 0) {
        free_heap_8018D9C();
    }
    if (process->buffer98 != 0) {
        free_heap_8018D9C();
    }
    if (process->buffer94 != 0) {
        free_heap_8018D9C();
    }
    process_remove((struct Process*)process, flags);
}

void graphics_copy_staging_values(struct GraphicsStagingSource* source)
    __attribute__((alias("sub_8059F24")));
void graphics_destroy_transfer_process(struct GraphicsProcessState* process, s32 flags)
    __attribute__((alias("sub_805C73C")));
void graphics_destroy_vram_process(struct GraphicsProcessState* process, s32 flags)
    __attribute__((alias("sub_805DA1C")));

MISC_SEC(graphics_terminate_process_label_at_2)
void graphics_terminate_process_label_at_2(struct Process* process)
{
    process->label[2] = 0;
}
MISC_SEC(graphics_terminate_process_label_at_2)
const u16 graphics_terminate_process_label_at_2_padding = 0;
