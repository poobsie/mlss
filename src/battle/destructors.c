#include "global.h"
#include "battle/functions.h"
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

#define DEFINE_BATTLE_VTABLE_DESTRUCTOR(name, sectionName)                     \
    void name(struct BattleVtableObject* object, int flags)                    \
        __attribute__((section(sectionName)));                                 \
    void name(struct BattleVtableObject* object, int flags)                    \
    {                                                                          \
        object->vtable = (void*)0x08CDCA30;                                     \
        if (flags & 1)                                                         \
            free_heap_8018DA8(object);                                         \
    }

DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_a,
                                ".text.freeing_destructors.sub_8159378")
DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_b,
                                ".text.freeing_destructors.sub_81593B8")
DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_c,
                                ".text.freeing_destructors.sub_81593DC")
DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_d,
                                ".text.freeing_destructors.sub_8159400")
DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_e,
                                ".text.freeing_destructors.sub_8159440")
DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_f,
                                ".text.freeing_destructors.sub_8159464")
DEFINE_BATTLE_VTABLE_DESTRUCTOR(battle_destroy_definition_ca30_base,
                                ".text.freeing_destructors.sub_81DD648")
