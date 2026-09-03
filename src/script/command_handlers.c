#include "global.h"
#include "script/command_context.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))

extern void sub_801B0AC(u16);
extern void sub_803C898(void *, s32);
extern void sub_805C7B4(void *, u8);
extern void sub_805B490(void *, u16);
extern void sub_805B618(void *, u16);
extern void sub_8047E50(void *, u16);
extern void sub_8047364(void *, u8);
extern void sub_80473DC(void *);

SEC(script_command_set_input_mask) s32 script_command_set_input_mask(
    struct ScriptCommandContext* context, void* state, u16* arguments)
{
    sub_801B0AC(*arguments);
    return 1;
}
SEC(script_command_set_input_mask) const u16 script_command_set_input_mask_padding = 0;

SEC(sub_80F0780) s32 sub_80F0780(struct ScriptCommandContext* context, void* state, s32* arguments)
{
    s32 index = *arguments;
    if (index != 5)
        sub_803C898(context->objectRegistry, index);
    return 1;
}

#define DEFINE_OBJECT_COMMAND(name, argument_type, action, result)      \
    SEC(name) s32 name(struct ScriptCommandContext* context, void* state, argument_type* arguments) \
    {                                                                    \
        void* object = context->objectRegistry->objects[SCRIPT_OBJECT_SLOT_183]; \
        action(object, *arguments);                                     \
        return result;                                                   \
    }

DEFINE_OBJECT_COMMAND(sub_80F0BC0, u8, sub_805C7B4, 1)
DEFINE_OBJECT_COMMAND(sub_80F0BD8, u16, sub_805B490, 0)
DEFINE_OBJECT_COMMAND(sub_80F0BF0, u16, sub_805B618, 0)

#define DEFINE_INDEXED_COMMAND(name, argument_type, action)             \
    SEC(name) s32 name(struct ScriptCommandContext* context, void* state, u32* arguments) \
    {                                                                    \
        u32 index = *arguments++;                                       \
        void* object = SCRIPT_OBJECT_AT(context->objectRegistry, index); \
        action(object, *(argument_type *)arguments);                    \
        return 1;                                                        \
    }

DEFINE_INDEXED_COMMAND(script_command_set_object_configuration, u16, sub_8047E50)
DEFINE_INDEXED_COMMAND(script_command_set_object_mode, u8, sub_8047364)

SEC(script_command_advance_object_mode) s32 script_command_advance_object_mode(
    struct ScriptCommandContext* context, void* state, u32* arguments)
{
    u32 index = *arguments;
    void* object = SCRIPT_OBJECT_AT(context->objectRegistry, index);
    sub_80473DC(object);
    return 1;
}
SEC(script_command_advance_object_mode) const u16 script_command_advance_object_mode_padding = 0;
