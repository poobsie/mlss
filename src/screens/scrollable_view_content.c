#include "screens/scrollable_view.h"

void free_heap_8018D9C(void* allocation);
void sub_80184F4(void* vramBase);
void sub_805C6B8(struct ScrollableViewContent* content);

#define SEC(symbol) __attribute__((section(".text.small_functions_12." #symbol)))

SEC(sub_8057B58)
void scrollable_view_content_destroy(struct ScrollableViewContent* content,
                                     u32 flags)
{
    content->process.definition = (struct ProcessDefinition*)0x08CDC288;
    if (content->cleanupActive584 != 0)
        sub_805C6B8(content);
    sub_80184F4((void*)0x06000000);
    if (content->buffer0A4 != 0)
        free_heap_8018D9C(content->buffer0A4);
    if (content->buffer0A0 != 0)
        free_heap_8018D9C(content->buffer0A0);
    if (content->buffer09C != 0)
        free_heap_8018D9C(content->buffer09C);
    if (content->buffer0A8 != 0)
        free_heap_8018D9C(content->buffer0A8);
    if (content->buffer098 != 0)
        free_heap_8018D9C(content->buffer098);
    if (content->buffer094 != 0)
        free_heap_8018D9C(content->buffer094);
    process_remove(&content->process, flags);
}
