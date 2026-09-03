#include "global.h"

#define SECTION(name) __attribute__((section(".text.mariobros_global_dispatch." #name)))

extern u8 gMarioGlobal_03000F50[];
extern void *gMarioData_08F9F054[];
extern void *gMarioData_08F9F11C[];
extern void *gMarioData_08F9FA64[];
extern void sub_8F6F35C(void *);

#define DEFINE_GLOBAL_TABLE_CALL(name, table) \
    SECTION(name) void name(void) \
    { \
        sub_8F6F35C(table[gMarioGlobal_03000F50[0xC5A]]); \
    }

DEFINE_GLOBAL_TABLE_CALL(sub_8F55174, gMarioData_08F9F054)
DEFINE_GLOBAL_TABLE_CALL(sub_8F55C90, gMarioData_08F9F11C)
DEFINE_GLOBAL_TABLE_CALL(sub_8F5CBA4, gMarioData_08F9FA64)
