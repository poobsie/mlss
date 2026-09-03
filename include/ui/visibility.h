#ifndef GUARD_UI_VISIBILITY_H
#define GUARD_UI_VISIBILITY_H

#include "global.h"

struct UiSingleSpriteOwner {
    u8 unknown00[0x30];
    void* sprite;
};

#define ui_hide_owned_sprite sub_81218C8
#define ui_show_owned_sprite sub_81218D4
#define ui_visibility_callback_false sub_81218E0

void ui_hide_owned_sprite(struct UiSingleSpriteOwner* owner);
void ui_show_owned_sprite(struct UiSingleSpriteOwner* owner);
int ui_visibility_callback_false(void);

#endif
