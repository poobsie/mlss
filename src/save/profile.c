#include "save/profile.h"

struct TitleSaveSummary* save_get_title_summary(void)
    __attribute__((section(".text.text_upper_singletons.sub_81251DC")));
struct TitleSaveSummary* save_get_title_summary(void) {
    return (struct TitleSaveSummary*)((u8*)gSaveState + 0x1FF8);
}
