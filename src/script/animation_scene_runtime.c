#include "script/animation_runtime.h"
#include "common.h"
#include "process/process.h"

#define SEC(name) __attribute__((section(".text.animation_scene_runtime." #name)))
#define ZERO_PAD(name) \
    SEC(name) const u16 name##_padding __attribute__((aligned(1))) = 0

typedef void (*AnimationMemoryFill)(u32 value, void* destination, u32 size);

#define ANIMATION_FIELD_RUNTIME \
    (*(struct AnimationFieldRuntime**)0x03000FD8)
#define ANIMATION_MEMORY_FILL \
    (*(AnimationMemoryFill*)0x03001034)

extern u8 sub_8116620(void* state);
extern void sub_81151E4(void* layer, u8 flags, u16 value, u16 size,
                        u16 firstMask, u16 secondMask,
                        u32 firstData, u32 secondData);
extern s32 sub_8082B00(void);

SEC(sub_80E2EDC)
void animation_scene_remove_process(struct AnimationSceneProcess* process, u32 flags)
{
    process->process.definition = (struct ProcessDefinition*)0x08CDC2E8;
    if (process->completion != 0)
        *process->completion = 0;
    process_remove(&process->process, flags);
}

SEC(sub_80E3CF4)
bool32 animation_scene_layer_is_active(void)
{
    u8 result = sub_8116620(ANIMATION_FIELD_RUNTIME->layer248);

    if (result != 0)
        return TRUE;
    return FALSE;
}
ZERO_PAD(sub_80E3CF4);

SEC(sub_80E3D1C)
void animation_scene_configure_layer(void)
{
    struct AnimationFieldRuntime* runtime = ANIMATION_FIELD_RUNTIME;
    void* optional = runtime->optional2D8;
    u16 value = 0;

    if (optional != 0)
        value = *(u16*)((u8*)optional + 0x0A);
    sub_81151E4(runtime->layer248, 0, value, 0x10,
                 0xFFFF, 0xFFFF, 0, 0);
    gGameState.field_884 = -1;
}

SEC(sub_80E3D70)
void animation_scene_clear_vram_regions(void)
{
    ANIMATION_MEMORY_FILL(0, (void*)0x06004000, 0x9000);
    ANIMATION_MEMORY_FILL(0, (void*)0x0600F000, 0x1000);
}

SEC(sub_80E3DA4)
bool32 animation_scene_poll_runtime_ready(void)
{
    u8 result = sub_8082B00();

    if (result != 0)
        return TRUE;
    gGameState.field_884 = result;
    return FALSE;
}
ZERO_PAD(sub_80E3DA4);

SEC(sub_80E3DD0)
void animation_scene_initialize_transfer_buffer(void)
{
    void* optional = ANIMATION_FIELD_RUNTIME->optional2D8;
    u32 value = 0;
    AnimationMemoryFill* fillSlot;
    void* buffer;

    if (optional != 0)
        value = *(u16*)((u8*)optional + 0x0A);
    fillSlot = (AnimationMemoryFill*)0x03001034;
    buffer = (void*)0x02000080;
    (*fillSlot)(value, buffer, 0x200);
    value |= value << 16;
    (*fillSlot)(value, buffer, 0x400);
    gGameState.field_2 = 0xFFFF;
    gGameState.field_0 = 0xFFFF;
    gGameState.field_884 = -1;
}

SEC(sub_80E4F98)
void animation_transfer_mark_references(struct AnimationTransferNode* root,
                                        struct AnimationTransferNode* target)
{
    struct AnimationTransferNode* node = root;

    while (node != 0) {
        if (target == node->key)
            animation_transfer_mark_references(root, node);
        else if (target == node)
            node->state = -1;
        node = node->next;
    }
}
