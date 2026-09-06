#include "global.h"

#define SEC(symbol) __attribute__((section(".text.battle_callback_resource_state." #symbol)))
#define battle_install_variant_callback sub_815071C

void sub_81507A8(void);

SEC(sub_815071C)
void battle_install_variant_callback(void* unused0, void* unused1, void (**slot)(void))
{
    *slot = sub_81507A8;
}
