#include "battle/functions.h"
#include "battle/object.h"

#define BATTLE_SECTION(name) __attribute__((section(name)))

void battle_set_flag_f8_40(struct BattleControlObject* object)
    BATTLE_SECTION(".text.sub_8028EE8");
void battle_set_flag_f8_40(struct BattleControlObject* object) {
    ((u8*)object)[0xF8] |= 0x40;
}

void battle_set_flag_12d_20(struct BattleControlObject* object)
    BATTLE_SECTION(".text.sub_8028F2C");
void battle_set_flag_12d_20(struct BattleControlObject* object) {
    ((u8*)object)[0x12D] |= 0x20;
}

void battle_set_flag_12d_10(struct BattleControlObject* object)
    BATTLE_SECTION(".text.sub_8028F40");
void battle_set_flag_12d_10(struct BattleControlObject* object) {
    ((u8*)object)[0x12D] |= 0x10;
}

void battle_set_value_12b(struct BattleControlObject* object, u8 value)
    BATTLE_SECTION(".text.sub_8029024");
void battle_set_value_12b(struct BattleControlObject* object, u8 value) {
    object->value12B = value;
}

void battle_set_flag_12c_02(struct BattleControlObject* object)
    BATTLE_SECTION(".text.sub_8029060");
void battle_set_flag_12c_02(struct BattleControlObject* object) {
    ((u8*)object)[0x12C] |= 2;
}

void battle_set_flag_12c_01(struct BattleControlObject* object)
    BATTLE_SECTION(".text.sub_8029070");
void battle_set_flag_12c_01(struct BattleControlObject* object) {
    ((u8*)object)[0x12C] |= 1;
}

void battle_set_flags_12c_mode(struct BattleControlObject* object, s32 value)
    BATTLE_SECTION(".text.early_bitfield_updates.sub_80290CC");
void battle_set_flags_12c_mode(struct BattleControlObject* object, s32 value) {
    u8* flags = (u8*)object + 0x12C;
    s32 current;
    s32 bits;
    value <<= 2;
    current = *flags;
    bits = 3;
    bits &= current;
    bits |= value;
    *flags = bits;
}
