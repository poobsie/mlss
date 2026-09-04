#include "global.h"
#include "audio/music.h"
#include "audio/sound_effects.h"
#include "battle/functions.h"
#include "battle/object.h"
#include "field/selection_sequence.h"
#include "script/command_handlers.h"
#include "script/command_context.h"
#include "script/execution_state.h"

#define SEC(name) __attribute__((section(".text.script_command_handlers." #name)))
#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define MISC3_SEC(name) \
    __attribute__((section(".text.misc_helpers_03." STRINGIFY(name))))
#define FIELD_RUNTIME (*(struct FieldSelectionRuntime**)0x03000FD8)
#define SCRIPT_GLOBAL_D44 (*(void**)0x03000D44)
#define SCRIPT_GLOBAL_FB8 (*(void**)0x03000FB8)
#define SCRIPT_FIELD_RUNTIME (*(u8**)0x03000FD0)
#define U8AT(pointer, offset) (*(u8*)((u8*)(pointer) + (offset)))

struct ScriptBattleReturnContext {
    u8 unknown00[0x1C];
};

extern void sub_801B0AC(u16);
extern void sub_803C898(void *, s32);
extern void sub_805C7B4(void *, u8);
extern void sub_805B490(void *, u16);
extern void sub_805B618(void *, u16);
extern void sub_8047E50(void *, u16);
extern void sub_8047364(void *, u8);
extern void sub_80473DC(void *);
extern u8 sub_8027378(void* objectRegistry);
extern void sub_805C78C(void* object, u8 value0, u8 value1);
extern void sub_80E9330(void* owner, u16 value);
extern void sub_80E6FB8(void* resource, s32 layer);
extern void sub_80E7118(void* resource, u8 mask);
extern void sub_80E6E68(void* resource);
extern u8 sub_8116B48(s32, s32, s32);
extern u8 sub_811795C(s32, s32, s32);
extern void sub_8029A0C(void*, void*, s32);
extern void sub_803AC8C(void*);
extern void sub_803AAE4(void*);
extern void sub_803AE38(void*);
extern void sub_803ADA8(void*, s32);
extern void sub_802F834(void*);
extern void sub_803C638(void*);
extern void sub_803C424(void*);
extern void sub_80326F4(void*);
extern u8 sub_803C4A0(void*);
extern void sub_80328B4(void*);
extern u8 sub_803C468(void*);

struct ScriptObjectBytePairArguments {
    u8 value0;
    u8 padding01[3];
    u8 value1;
};

struct ScriptResourceEntry {
    u8 unknown00[0x42];
    u8 flags42;
    u8 unknown43[9];
};

struct ScriptResourceOwner {
    u8 unknown00[4];
    struct ScriptResourceEntry* resources04;
};

struct ScriptInputOwner {
    u8 unknown00[4];
    u8* inputState04;
};

struct ScriptSoundVolumeArguments {
    u8 duration;
    u8 padding01[3];
    u8 volume;
};

SEC(sub_80EAD98)
s32 script_command_set_runtime_direction_sign(
    void* context, void* state, const u32* argument)
{
    if (*argument == 0)
        U8AT(SCRIPT_GLOBAL_D44, 0x29) = 1;
    else
        U8AT(SCRIPT_GLOBAL_D44, 0x29) = 0xFF;
    return 1;
}

SEC(sub_80EAEF8)
s32 script_command_control_sound_effect(
    void* context, struct ScriptExecutionState* state,
    const s32* arguments)
{
    s32 operation = *arguments++;

    switch (operation) {
    case 0:
        sound_effect_play(*arguments, SOUND_VOLUME_UNCHANGED);
        break;
    case 1:
        if (*arguments != 0)
            sound_effect_stop(*arguments);
        else
            sound_effects_stop_all();
        break;
    case 2:
        if ((u8)sound_effect_is_playing(*arguments)) {
            state->cursor = state->resumeCursor;
            return 0;
        }
        break;
    }
    return 1;
}

SEC(sub_80EAEE0)
s32 script_command_set_sound_effect_volume(
    void* context, void* state, const u32* arguments)
{
    u32 operation = *arguments++;

    if (operation == 0) {
        const struct ScriptSoundVolumeArguments* parameters =
            (const struct ScriptSoundVolumeArguments*)arguments;
        sound_effects_set_volume(parameters->volume, parameters->duration);
    }
    return 1;
}
SEC(sub_80EAEE0) const u16 sub_80EAEE0_padding = 0;

SEC(sub_80EAF4C)
s32 script_command_control_music(
    void* context, void* state,
    s32* arguments)
{
    s32 operation = *arguments++;

    switch (operation) {
    case 0:
        if (arguments[2] == 2)
            arguments[2] = MUSIC_VOLUME_UNCHANGED;
        music_play(arguments[0], arguments[1], arguments[2]);
        break;
    case 1:
        if (arguments[2] == 2)
            arguments[2] = MUSIC_VOLUME_UNCHANGED;
        music_resume(arguments[0], arguments[2], (u8)arguments[1]);
        break;
    case 2:
        music_set_volume(arguments[0], (u8)arguments[2], (u8)arguments[1]);
        break;
    case 3:
        music_set_tempo(arguments[0], (u8)arguments[2], (u8)arguments[1]);
        break;
    }
    return 1;
}

SEC(sub_80EAE9C)
s32 script_command_branch_if_runtime_byte_30_equals(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments)
{
    if (U8AT(SCRIPT_GLOBAL_FB8, 0x30) == arguments[0])
        state->cursor = arguments[1];
    return 1;
}

SEC(sub_80EB048)
s32 script_command_set_runtime_byte_32(
    void* context, void* state, const u32* argument)
{
    u8* runtime = SCRIPT_GLOBAL_FB8;
    u32 value = *argument;

    U8AT(runtime, 0x32) = value;
    return 1;
}

SEC(sub_80EB05C)
s32 script_command_control_resource_wait(
    void* context, void* owner, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u32 operation = *arguments++;

    switch (operation) {
    case 0:
        sub_80E9330(owner, *(const u16*)arguments);
        break;
    case 1: {
        register struct ScriptResourceEntry* resources asm("r0") =
            ((struct ScriptResourceOwner*)owner)->resources04;
        register u32 index asm("r2") = *arguments;

        // Preserve the original register allocation around the scaled lookup.
        asm("" : "+r"(resources), "+r"(index));
        resources += index;
        asm("" : "+r"(resources));
        if ((s32)((u32)resources->flags42 << 29) >= 0) {
            state->cursor = state->resumeCursor;
            return 0;
        }
        break;
    }
    }
    return 1;
}
SEC(sub_80EB05C) const u16 sub_80EB05C_padding = 0;

SEC(sub_80EB09C)
s32 script_command_configure_graphics_resource(
    void* context, void* resource, void* state, const s32* mode)
{
    if (*mode <= 4) {
        sub_80E6FB8(resource, (u16)*mode);
        sub_80E7118(resource, (u8)(1 << *mode));
    } else {
        sub_80E6E68(resource);
        sub_80E7118(resource, U8AT(*(void**)((u8*)resource + 4), 0x1B3));
    }
    U8AT(SCRIPT_GLOBAL_FB8, 0x31) = 0;
    return 1;
}

SEC(script_cmd_wait_for_user_input)
s32 script_command_wait_for_user_input(
    void* context, struct ScriptInputOwner* owner,
    struct ScriptExecutionState* state, const u32* bit)
{
    if ((owner->inputState04[0x1B4] >> *bit) & 1) {
        state->cursor = state->resumeCursor;
        return 0;
    }
    return 1;
}
SEC(script_cmd_wait_for_user_input)
const u16 script_cmd_wait_for_user_input_padding = 0;
MISC3_SEC(script_command_return_from_battle)
u8 script_command_return_from_battle(
    struct ScriptBattleReturnContext* context,
    struct ScriptExecutionState* state,
    s32* shouldMarkReturn)
{
    struct FieldSelectionRuntime* runtime;
    u8 flags;
    s32 battleReturnMask;

    if (*shouldMarkReturn != 0) {
        runtime = FIELD_RUNTIME;
        flags = runtime->flags2BF;
        battleReturnMask = 2;
        runtime->flags2BF = (u8)(flags | battleReturnMask);
    }
    return script_cmd_return((u8*)context + sizeof(*context), state);
}

SEC(script_command_set_input_mask) s32 script_command_set_input_mask(
    struct ScriptCommandContext* context, void* state, u16* arguments)
{
    sub_801B0AC(*arguments);
    return 1;
}
SEC(script_command_set_input_mask) const u16 script_command_set_input_mask_padding = 0;

SEC(sub_80F0540)
s32 script_command_clear_field_runtime_flag(
    void* context, void* owner, void* state, const u32* arguments)
{
    u32 operation = *arguments++;

    if (operation == 0) {
        /* The owner and meaning of this 16-bit field flag bank remain unknown. */
        u16* flags = (u16*)(SCRIPT_FIELD_RUNTIME + 0x54A);
        *flags &= ~(1 << *arguments);
    }
    return 1;
}

SEC(sub_80F0780) s32 sub_80F0780(struct ScriptCommandContext* context, void* state, s32* arguments)
{
    s32 index = *arguments;
    if (index != 5)
        sub_803C898(context->objectRegistry, index);
    return 1;
}

SEC(sub_80F0794)
s32 script_command_dispatch_field_object_operation(
    struct ScriptCommandContext* context, void* state, const s32* argument)
{
    /* Values 5 through 11 select object-registry operations. Their meanings remain unknown. */
    s32 command = *argument;

    switch (command) {
    case 5:
        sub_803AC8C(context->objectRegistry);
        break;
    case 6:
        sub_803AAE4(context->objectRegistry);
        break;
    case 7:
        sub_803AE38(context->objectRegistry);
        break;
    case 8:
        sub_803ADA8(context->objectRegistry, 1);
        break;
    case 9:
        sub_802F834(context->objectRegistry);
        break;
    case 10:
        sub_803C638(context->objectRegistry);
        break;
    case 11:
        sub_803C424(context->objectRegistry);
        break;
    default:
        sub_8029A0C(context->objectRegistry, (void*)command, 0);
        break;
    }
    return 1;
}

SEC(sub_80F0814)
s32 script_command_dispatch_field_object_control(
    struct ScriptCommandContext* context, struct ScriptExecutionState* state,
    const s32* argument)
{
    /* The packed low-bit/group command encoding is proven; operation names are not. */
    s32 command = *argument;
    s32 group = (command >> 1) & 0xF;
    s32 result;

    switch (group) {
    case 0:
        switch (command & 1) {
        case 0:
            sub_80326F4(context->objectRegistry);
            break;
        case 1:
            result = sub_803C4A0(context->objectRegistry);
            if ((result << 24) != 0) {
                state->cursor = state->resumeCursor;
                return 0;
            }
            break;
        }
        break;
    case 1:
        switch (group & command) {
        case 0:
            sub_80328B4(context->objectRegistry);
            break;
        case 1:
            result = sub_803C468(context->objectRegistry);
            if ((result << 24) != 0) {
                state->cursor = state->resumeCursor;
                return 0;
            }
            break;
        }
        break;
    }
    return 1;
}
SEC(sub_80F0814) const u16 sub_80F0814_padding = 0;

SEC(sub_80F087C)
s32 script_wait_for_battle_flag_208_10(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state)
{
    s32 result;

    if (((u8*)context->objectRegistry)[0x208] & 0x10) {
        result = 1;
    } else {
        state->cursor = state->resumeCursor;
        result = 0;
    }
    return result;
}

SEC(sub_80F08C0)
s32 script_command_branch_on_field_queries(
    void* context, struct ScriptExecutionState* state,
    const u32* arguments)
{
    u8 result = sub_8116B48(0, 3, 0);

    if (result == 0) {
        result = sub_811795C(0, 0, 1);
        if (result == 0)
            result = sub_811795C(1, 0, 1);
    }

    if ((result == 0) == *arguments++)
        state->cursor = *arguments;
    return 1;
}
SEC(sub_80F08C0) const u16 sub_80F08C0_padding = 0;

SEC(sub_80F0914)
s32 script_command_set_battle_flag_12d(
    struct ScriptCommandContext* context, void* state,
    const u32* operation)
{
    switch (*operation) {
    case 0:
        battle_set_flag_12d_10(
            (struct BattleControlObject*)context->objectRegistry);
        break;
    case 1:
        battle_set_flag_12d_20(
            (struct BattleControlObject*)context->objectRegistry);
        break;
    }
    return 1;
}
SEC(sub_80F0914) const u16 sub_80F0914_padding = 0;

SEC(sub_80F0938)
s32 script_command_set_battle_flags_12c(
    struct ScriptCommandContext* context, void* state,
    const s32* mode)
{
    if (*mode != -32)
        battle_set_flags_12c_mode(
            (struct BattleControlObject*)context->objectRegistry, *mode);
    else
        battle_set_flag_12c_01(
            (struct BattleControlObject*)context->objectRegistry);
    return 0;
}
SEC(sub_80F0938) const u16 sub_80F0938_padding = 0;

SEC(sub_80F0984)
s32 script_wait_for_battle_control_ready(
    struct ScriptCommandContext* context,
    struct ScriptExecutionState* state)
{
    u8 result = sub_8027378(context->objectRegistry);
    if (result == 1) {
        state->cursor = state->resumeCursor;
        return 0;
    }
    return 1;
}
SEC(sub_80F0984) const u16 sub_80F0984_padding = 0;

SEC(sub_80F0BA4)
s32 script_command_configure_object_slot_183(
    struct ScriptCommandContext* context, void* state,
    const struct ScriptObjectBytePairArguments* arguments)
{
    sub_805C78C(
        context->objectRegistry->objects[SCRIPT_OBJECT_SLOT_183],
        arguments->value0, arguments->value1);
    return 1;
}
SEC(sub_80F0BA4) const u16 sub_80F0BA4_padding = 0;

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
