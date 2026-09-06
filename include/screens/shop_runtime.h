#ifndef GUARD_SCREENS_SHOP_RUNTIME_H
#define GUARD_SCREENS_SHOP_RUNTIME_H

#include "global.h"

#define shop_screen_destroy sub_812AA78

struct ShopScreenRuntime;

void shop_screen_destroy(struct ShopScreenRuntime* screen, u32 flags);

#endif
