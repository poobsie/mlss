#include "runtime/input_sound_mask.h"

#define SEC(symbol) __attribute__((section(".text.runtime_input_sound." #symbol)))

SEC(sub_801B0AC)
void runtime_set_input_sound_mask(u16 mask)
{
    *(u16*)0x03000D3C = mask;
}
