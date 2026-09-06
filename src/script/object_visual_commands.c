#include "global.h"
#include "script/command_context.h"
#include "script/command_handlers.h"

#define SEC(name) __attribute__((section(".text.script_object_commands." #name)))

typedef void (*ScriptObjectCallback)(void* component, u8 value);

struct ScriptObjectCallbackEntry {
    s16 objectOffset;
    u16 unknown02;
    ScriptObjectCallback callback;
};

struct ScriptObjectCallbackTable {
    u8 unknown00[0x90];
    struct ScriptObjectCallbackEntry primary;
    struct ScriptObjectCallbackEntry secondary;
};

struct ScriptObjectRuntime {
    u8 unknown000[0x58];
    u8 transform58[0x23C];
    void* visual294;
    u8 unknown298[0xA0];
    struct ScriptObjectCallbackTable* callbacks338;
};

struct ScriptIndexedObjectCallbackArguments {
    s32 objectIndex;
    s32 animationValue;
    s32 interactionValue;
    s32 configuration;
    s32 callbackSelector;
};

struct ScriptActiveObjectCallbackArguments {
    s32 callbackValue;
    s32 animationValue;
    s32 interactionValue;
    s32 configuration;
};

extern void sub_8047364(void* object, u8 mode);
extern void sub_8047258(void* object, s32 configuration);
extern void sub_8047154(void* object, s32 value0, s32 value1);
extern s32 sub_80EA60C(
    void* commandRuntime, void* target, void* visual, s32 mode, s32 value);

#define INVOKE_OBJECT_CALLBACK(object, entry, value) do {      \
    struct ScriptObjectCallbackEntry* callbackEntry = (entry); \
    callbackEntry->callback(                                   \
        (u8*)(object) + callbackEntry->objectOffset, (value));  \
} while (0)

SEC(sub_80F1738)
s32 script_command_configure_indexed_object_callback(
    struct ScriptCommandContext* context, void* state,
    const struct ScriptIndexedObjectCallbackArguments* arguments)
{
    struct ScriptObjectRuntime* object =
        SCRIPT_OBJECT_AT(context->objectRegistry, arguments->objectIndex);

    sub_8047364(object, 1);
    sub_8047258(object, 0);
    if (arguments->callbackSelector) {
        INVOKE_OBJECT_CALLBACK(object, &object->callbacks338->secondary,
                               (u8)arguments->animationValue);
    } else {
        INVOKE_OBJECT_CALLBACK(object, &object->callbacks338->primary,
                               (u8)arguments->animationValue);
    }
    sub_8047154(object, arguments->interactionValue, 0);
    return (u8)sub_80EA60C(
        (u8*)context + 0x1C, object->transform58, object->visual294,
        (u8)arguments->callbackSelector, (u8)arguments->configuration);
}
SEC(sub_80F1738) const u16 sub_80F1738_padding = 0;

SEC(sub_80F1998)
s32 script_command_configure_object_callback(
    struct ScriptCommandContext* context, struct ScriptObjectRuntime* object,
    void* target, const struct ScriptActiveObjectCallbackArguments* arguments)
{
    sub_8047364(object, 1);
    sub_8047258(object, arguments->configuration);
    if (arguments->configuration) {
        INVOKE_OBJECT_CALLBACK(object, &object->callbacks338->secondary,
                               (u8)arguments->callbackValue);
    } else {
        INVOKE_OBJECT_CALLBACK(object, &object->callbacks338->primary,
                               (u8)arguments->callbackValue);
    }
    sub_8047154(object, arguments->animationValue, 0);
    return (u8)sub_80EA60C(
        (u8*)context + 0x1C, target, object->visual294,
        (u8)arguments->configuration, (u8)arguments->interactionValue);
}
SEC(sub_80F1998) const u16 sub_80F1998_padding = 0;
