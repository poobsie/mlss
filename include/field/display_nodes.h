#ifndef GUARD_FIELD_DISPLAY_NODES_H
#define GUARD_FIELD_DISPLAY_NODES_H

#include "global.h"

struct FieldDisplayNode {
    u8 unknown00[8];
    struct FieldDisplayNode* linkedNode08;
    u8 unknown0C[8];
    s16 value14;
};

#define field_create_linked_display_nodes sub_810CCC8
#define field_create_display_node_86 sub_810CCB0
#define field_ensure_primary_pair_display_nodes sub_810CBC8

void field_create_linked_display_nodes(void);
void field_create_display_node_86(void);
void field_ensure_primary_pair_display_nodes(void);

#endif
