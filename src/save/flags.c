#include "save/flags.h"

u8 sub_80E99E0(u16 id);
void sub_80E9A6C(u16 id, u8 value);

u8 save_local_flag_read(u32 id)
    __attribute__((section(".text.text_late_helpers.sub_8150A00")));
u8 save_local_flag_read(u32 id) {
    return sub_80E99E0(id + SAVE_LOCAL_FLAG_BASE);
}

void save_local_flag_write(u32 id, u8 value)
    __attribute__((section(".text.text_late_helpers.sub_8150A1C")));
void save_local_flag_write(u32 id, u8 value) {
    sub_80E9A6C(id + SAVE_LOCAL_FLAG_BASE, value);
}
