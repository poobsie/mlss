#include "global.h"
#define FIELD_AT(p, t, o) (*(t)((u8*)(p) + (o)))
#define SEC(name)         __attribute__((section(".text.upper_gate." #name)))
SEC(sub_8163CD4) void sub_8163CD4(void* arg0, void* arg1) {
    void* temp_r0;
    void* var_r0 = FIELD_AT(arg0, void**, 0);
    if (var_r0 != NULL) {
    loop_1:
        if (var_r0 != arg1) {
            var_r0 = FIELD_AT(var_r0, void**, 8);
            if (var_r0 == NULL)
                goto block_3;
            goto loop_1;
        }
    } else {
    block_3:
        temp_r0 = FIELD_AT(arg0, void**, 0);
        if (temp_r0 == NULL) {
            FIELD_AT(arg1, void**, 8) = temp_r0;
            FIELD_AT(arg1, void**, 4) = temp_r0;
            FIELD_AT(arg0, void**, 4) = arg1;
            FIELD_AT(arg0, void**, 0) = arg1;
        } else {
            FIELD_AT(FIELD_AT(arg0, void**, 4), void**, 8) = arg1;
            FIELD_AT(arg1, void**, 4) = FIELD_AT(arg0, void**, 4);
            FIELD_AT(arg1, void**, 8) = NULL;
            FIELD_AT(arg0, void**, 4) = arg1;
        }
        FIELD_AT(arg0, s32*, 8)++;
    }
}
