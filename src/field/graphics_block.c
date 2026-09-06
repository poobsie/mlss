#include "field/graphics_block.h"

#define SEC(symbol) __attribute__((section(".text.field_graphics_block." #symbol)))

struct FieldGraphicsStateOverlay {
    u8 unknown00[0x8C0];
    u8 resourceIndex8C0;
};

extern struct FieldGraphicsStateOverlay gFieldGraphicsState __asm__("gGameState");

void* sub_8127ECC(u32 index, u32* size);
s32 sub_8127E50(void* source, void* destination, s32 useHeapBuffer);

SEC(sub_81229F0)
void field_load_indexed_graphics_block(struct FieldGraphicsWorkspace* workspace)
{
    void* resource = sub_8127ECC(gFieldGraphicsState.resourceIndex8C0 + 7, NULL);

    sub_8127E50(resource, workspace->graphicsData840, FALSE);
}
