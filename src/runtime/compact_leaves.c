#include "global.h"

#define SEC(name) __attribute__((section(".text.runtime_compact." #name)))

struct RuntimeLargeOwner {
    u8 unknown00[0x804];
    u32 value804;
    u8 unknown808[4];
    u32 value80C;
};

SEC(sub_8160EC4)
struct RuntimeLargeOwner* sub_8160EC4(struct RuntimeLargeOwner* owner) {
    owner->value804 = 0;
    owner->value80C = 0;
    return owner;
}

SEC(sub_8150EFC)
void* sub_8150EFC(void* owner) {
    return (u8*)owner + 0x0C;
}
