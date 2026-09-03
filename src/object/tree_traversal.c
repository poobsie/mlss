#include "global.h"

struct ObjectTreeNode {
    u32 unknown00;
    struct ObjectTreeNode* firstChild;
    struct ObjectTreeNode* secondChild;
};

void object_traverse_child_tree_noop(struct ObjectTreeNode* object)
    __asm__("sub_8135F20")
    __attribute__((section(".text.child_actions.sub_8135F20")));
void object_traverse_child_tree_noop(struct ObjectTreeNode* object)
{
    struct ObjectTreeNode* child = object->firstChild;
    if (child != 0)
        object_traverse_child_tree_noop(child);
    child = object->secondChild;
    if (child != 0)
        object_traverse_child_tree_noop(child);
}
__attribute__((section(".text.child_actions.sub_8135F20")))
const u16 sub_8135F20_padding = 0;
