#include "global.h"
#include "battle/object.h"

void free_heap_8018DA8(void* pointer);

#define DEFINE_BATTLE_SPRITE_OWNER_DESTRUCTOR(name)                           \
    void name(struct BattleSpriteOwner* object, int flags)                    \
        __attribute__((section(".text." #name)));                             \
    void name(struct BattleSpriteOwner* object, int flags) {                  \
        struct BattleSpriteOwner* current = object;                            \
        current->vtable = (void*)0x08CDCF50;                                   \
        if (flags & 1) {                                                       \
            free_heap_8018DA8(current);                                        \
        }                                                                      \
    }

DEFINE_BATTLE_SPRITE_OWNER_DESTRUCTOR(sub_815F7FC)
DEFINE_BATTLE_SPRITE_OWNER_DESTRUCTOR(sub_815F838)
DEFINE_BATTLE_SPRITE_OWNER_DESTRUCTOR(sub_815F85C)
DEFINE_BATTLE_SPRITE_OWNER_DESTRUCTOR(sub_815F898)
DEFINE_BATTLE_SPRITE_OWNER_DESTRUCTOR(sub_815F8BC)
