#include "field/position_forwarder.h"

#define SEC(symbol) __attribute__((section(".text.field_position_forwarder." #symbol)))

void sub_810D3B8(void* context, s32 x, s32 y, s32 flag);

SEC(sub_8106BEC)
void field_forward_node_position_and_flag(struct FieldPositionNode* node)
{
    sub_810D3B8(
        node->context0C, node->x12, node->y14, ((s16)node->flags10 >> 12) & 1);
}

SEC(sub_8106BEC)
const u16 sub_8106BEC_padding = 0;
