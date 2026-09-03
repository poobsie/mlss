#include "global.h"
#include "field/fixed_command_set.h"

void sub_8082AAC(u32 command);

#define SEC(symbol) __attribute__((section(".text.small_functions_01." #symbol)))

SEC(sub_8081E74) void field_spawn_fixed_command_set(void)
{
    sub_8082AAC(0x2027);
    sub_8082AAC(0x2046);
    sub_8082AAC(0x2056);
    sub_8082AAC(0x2075);
    sub_8082AAC(0x2089);
}
