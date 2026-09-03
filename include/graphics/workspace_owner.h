#ifndef GUARD_GRAPHICS_WORKSPACE_OWNER_H
#define GUARD_GRAPHICS_WORKSPACE_OWNER_H

#include "global.h"

struct GraphicsWorkspaceOwner {
    u8 unknown000[0x288];
    void* workspace288;
};

#define graphics_destroy_workspace_288 sub_80854F8

void graphics_destroy_workspace_288(struct GraphicsWorkspaceOwner* owner,
                                    u32 flags);

#endif
