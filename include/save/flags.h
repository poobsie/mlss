#ifndef GUARD_SAVE_FLAGS_H
#define GUARD_SAVE_FLAGS_H

#include "global.h"

enum {
    SAVE_LOCAL_FLAG_BASE = 0x1B90,
};

#define save_local_flag_read sub_8150A00
#define save_local_flag_write sub_8150A1C

u8 save_local_flag_read(u32 id);
void save_local_flag_write(u32 id, u8 value);

#endif
