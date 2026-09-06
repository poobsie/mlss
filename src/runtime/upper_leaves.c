#include "global.h"
#include "runtime/functions.h"

#define SEC(name) __attribute__((section(".text.runtime_upper." #name)))

struct RuntimeNodeValue {
    u8 unknown00[0x18];
    s16 value18;
};

struct RuntimeNodeOwner {
    u8 unknown00[0x310];
    struct RuntimeNodeValue* node310;
};

void sub_801BD50(u8 priority);

SEC(sub_801AFE4)
void runtime_resume_global_services(int unused)
{
    u8* flags = (u8*)0x03000D40;

    if (!(*flags & 1)) {
        sub_801BD50(1);
        runtime_initialize_global_state_fc0();
        runtime_initialize_global_state_fc4();
        *flags |= 1;
    }
}

SEC(sub_810D4C4)
void runtime_set_node_value_241(void)
{
    struct RuntimeNodeOwner* owner = *(struct RuntimeNodeOwner**)0x03000FD8;
    owner->node310->value18 = 0x241;
}
