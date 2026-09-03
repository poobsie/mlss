#include "field/display_nodes.h"

extern u32 sub_810D5F4;
extern u32 sub_810D624;
extern u32 sub_810B680;

struct FieldDisplayNode* sub_807D2D0(u32* definition, s32 value, s32 argument);
void sub_810B908(s32 index);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_01." STRINGIFY(symbol))))
#define MISC2_SEC(symbol) \
    __attribute__((section(".text.misc_helpers_02." STRINGIFY(symbol))))

MISC2_SEC(field_ensure_primary_pair_display_nodes)
void field_ensure_primary_pair_display_nodes(void)
{
    sub_810B908(0);
    sub_810B908(1);
}
MISC2_SEC(field_ensure_primary_pair_display_nodes)
const u16 field_ensure_primary_pair_display_nodes_padding = 0;

SEC(sub_810CCC8) void field_create_linked_display_nodes(void)
{
    struct FieldDisplayNode* first;

    first = sub_807D2D0(&sub_810D624, 0, 0);
    first->value14 = 0;
    sub_807D2D0(&sub_810D5F4, 0x18, 0)->linkedNode08 = first;
}

MISC_SEC(field_create_display_node_86)
void field_create_display_node_86(void)
{
    sub_807D2D0(&sub_810B680, 0x86, 0)->value14 = 0;
}
