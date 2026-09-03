#include "field/display_nodes.h"

extern u32 sub_810D5F4;
extern u32 sub_810D624;

struct FieldDisplayNode* sub_807D2D0(u32* definition, s32 value, s32 argument);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_810CCC8) void field_create_linked_display_nodes(void)
{
    struct FieldDisplayNode* first;

    first = sub_807D2D0(&sub_810D624, 0, 0);
    first->value14 = 0;
    sub_807D2D0(&sub_810D5F4, 0x18, 0)->linkedNode08 = first;
}
