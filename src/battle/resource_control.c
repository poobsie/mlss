#include "battle/functions.h"
#include "battle/object.h"

void sub_805C6B8(void* resource);
void sub_805BFF0(void* resource);

void battle_activate_resource_flags_0780(struct BattleResourceControlObject* object)
    __attribute__((section(".text.early_code_helpers_3.sub_8029788")));
void battle_activate_resource_flags_0780(struct BattleResourceControlObject* object) {
    u8* bytes = (u8*)object;

    if (((s32)(*(u16*)(bytes + 0xFC) << 0x15) >> 0x1C) == 0) {
        sub_805C6B8(*(void**)(bytes + 0x304));
    }
    *(u16*)(bytes + 0xFC) = (u16)(*(u16*)(bytes + 0xFC) | 0x780);
}

void battle_prepare_resource_if_inactive(struct BattleResourceControlObject* object)
    __attribute__((section(".text.text_early_helpers_04.sub_80297B8")));
void battle_prepare_resource_if_inactive(struct BattleResourceControlObject* object) {
    u8* bytes = (u8*)object;

    if (((s32)(*(u16*)(bytes + 0xFC) << 0x15) >> 0x1C) == 0)
        sub_805BFF0(*(void**)(bytes + 0x304));
}
