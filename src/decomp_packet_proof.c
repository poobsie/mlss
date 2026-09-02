#include "global.h"

struct PacketProofObject {
    u8 pad_00[0x14];
    u16 value;
};

void sub_8158E10(struct PacketProofObject* object)
    __attribute__((section(".text.sub_8158E10")));
void sub_8158E10(struct PacketProofObject* object) {
    object->value = 0;
}

__attribute__((section(".text.sub_8158E10")))
const u16 sub_8158E10_padding = 0;
