#include "field/map_graphics.h"
#include "memory/heap.h"

#define MAP_GRAPHICS_SEC(symbol) \
    __attribute__((section(".text.field.map_graphics." #symbol)))

void sub_80184F4(void* address);

MAP_GRAPHICS_SEC(sub_805A99C)
void field_map_graphics_destroy(
    struct FieldMapGraphicsProcess* process, u32 flags)
{
    process->process.definition = (struct ProcessDefinition*)0x08CDC2A8;
    sub_80184F4((void*)0x06000000);
    if (process->graphicsWorkspace != NULL)
        free_heap_8018D9C(process->graphicsWorkspace);
    if (process->metatileDefinitions != NULL)
        free_heap_8018D9C(process->metatileDefinitions);
    if (process->cellIndices != NULL)
        free_heap_8018D9C(process->cellIndices);
    if (process->expandedTilemaps != NULL)
        free_heap_8018D9C(process->expandedTilemaps);
    process_remove(&process->process, flags);
}
