#include "graphics/workspace_owner.h"

void free_heap_8018DA8(void* allocation);
void heap_free_block(void* allocation);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

#define GRAPHICS_WORKSPACE_OUTPUT (*(s16*)0x02000000)
#define GRAPHICS_WORKSPACE_VALUE (*(s32*)0x03000F70)

SEC(sub_80854F8)
void graphics_destroy_workspace_288(struct GraphicsWorkspaceOwner* owner,
                                    u32 flags)
{
    GRAPHICS_WORKSPACE_OUTPUT = (s16)GRAPHICS_WORKSPACE_VALUE;
    heap_free_block(owner->workspace288);
    if (flags & 1)
        free_heap_8018DA8(owner);
}
