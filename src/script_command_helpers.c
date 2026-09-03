#include "global.h"

#define FIELD(object, type, offset) (*(type *)((u8 *)(object) + (offset)))
#define SEC(name) __attribute__((section(".text.script_command_helpers." #name)))

extern void sub_801B0AC(u16);
extern void sub_803C898(void *, s32);
extern void sub_805C7B4(void *, u8);
extern void sub_805B490(void *, u16);
extern void sub_805B618(void *, u16);
extern void sub_8047E50(void *, u16);
extern void sub_8047364(void *, u8);
extern void sub_80473DC(void *);

SEC(sub_80EA9A8) s32 sub_80EA9A8(void *context, void *state, u16 *arguments)
{
    sub_801B0AC(*arguments);
    return 1;
}
SEC(sub_80EA9A8) const u16 sub_80EA9A8_padding = 0;

SEC(sub_80F0780) s32 sub_80F0780(void *context, void *state, s32 *arguments)
{
    s32 index = *arguments;
    if (index != 5)
        sub_803C898(FIELD(context, void *, 0x14), index);
    return 1;
}

#define DEFINE_OBJECT_COMMAND(name, argument_type, action, result)      \
    SEC(name) s32 name(void *context, void *state, argument_type *arguments) \
    {                                                                    \
        void *objects = FIELD(context, void *, 0x14);                   \
        void *object = *(void **)((u8 *)objects + 0x304);               \
        action(object, *arguments);                                     \
        return result;                                                   \
    }

DEFINE_OBJECT_COMMAND(sub_80F0BC0, u8, sub_805C7B4, 1)
DEFINE_OBJECT_COMMAND(sub_80F0BD8, u16, sub_805B490, 0)
DEFINE_OBJECT_COMMAND(sub_80F0BF0, u16, sub_805B618, 0)

#define DEFINE_INDEXED_COMMAND(name, argument_type, action)             \
    SEC(name) s32 name(void *context, void *state, u32 *arguments)      \
    {                                                                    \
        u32 index = *arguments++;                                       \
        void *objects = FIELD(context, void *, 0x14);                   \
        void *object = FIELD((u8 *)objects + index * 4, void *, 0x28);  \
        action(object, *(argument_type *)arguments);                    \
        return 1;                                                        \
    }

DEFINE_INDEXED_COMMAND(sub_80F1478, u16, sub_8047E50)
DEFINE_INDEXED_COMMAND(script_cmd_80F17C4, u8, sub_8047364)

SEC(sub_80F17DC) s32 sub_80F17DC(void *context, void *state, u32 *arguments)
{
    u32 index = *arguments;
    void *objects = FIELD(context, void *, 0x14);
    void *object = FIELD((u8 *)objects + index * 4, void *, 0x28);
    sub_80473DC(object);
    return 1;
}
SEC(sub_80F17DC) const u16 sub_80F17DC_padding = 0;
