#ifndef GUARD_FIELD_POSITION_FORWARDER_H
#define GUARD_FIELD_POSITION_FORWARDER_H

#include "global.h"

struct FieldPositionNode {
    u8 unknown00[0x0C];
    void* context0C;
    u16 flags10;
    s16 x12;
    s16 y14;
};

#define field_forward_node_position_and_flag sub_8106BEC
void field_forward_node_position_and_flag(struct FieldPositionNode* node);

#endif
