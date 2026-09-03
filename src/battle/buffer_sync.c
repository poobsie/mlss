#include "global.h"

void sub_80FC1F8(void);

__attribute__((section(".text.early_code_helpers.sub_801AF50")))
void sub_801AF50(void)
{
    sub_80FC1F8();
}
__attribute__((section(".text.early_code_helpers.sub_801AF50")))
const u16 sub_801AF50_padding = 0;

void battle_sync_process_buffers(void)
    __attribute__((alias("sub_801AF50")));
