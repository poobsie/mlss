#include "global.h"

#define UPPER_SECTION(name) __attribute__((section(".text.text_upper_structural." #name)))

extern u32 sub_813B5B4(void*);
extern u32 sub_813B650(void*);
extern void sub_813E974(void);
extern void sub_814706C(void);
extern void sub_815F8F4();
extern void sub_815F97C(void*, s32);
extern void sub_815FB14(void*, void*);
extern void sub_8021308(void*);
extern void sub_8139AA0(void*);
extern void* sub_815FA3C(void*);
extern void sub_815FA70(void*, s32);
extern void sub_815FAFC(void*);
extern void sub_8020A78(void);
extern void sub_8082E1C(void*, s32, s32, s32);
extern u32 sub_8199F30(void);

#define DEFINE_UPPER_LINKED_CHILD_DESTRUCTOR(name, descriptor) \
UPPER_SECTION(name) void name(u8* object, void* argument) { \
    u8* child; \
    u8* definition; \
    *(void**)(object + 0x30) = (void*)(descriptor); \
    child = *(u8**)(object + 0x34); \
    if (child != 0) { \
        definition = *(u8**)(child + 0x30); \
        (*(void (**)(void*, s32))(definition + 0x0C))(child + *(s16*)(definition + 8), 3); \
    } \
    sub_815FB14(object, argument); \
}

DEFINE_UPPER_LINKED_CHILD_DESTRUCTOR(sub_8158954, 0x08CDC9B0)
DEFINE_UPPER_LINKED_CHILD_DESTRUCTOR(sub_815F19C, 0x08CDCED0)

struct UpperLink {
    u8 pad_00[8];
    void* link;
    u8 first;
    u8 second;
    u8 pad_0E[4];
    u8 flags;
};

UPPER_SECTION(sub_8199D5C) void* sub_8199D5C(struct UpperLink* obj, u8 first, u8 second, void* link) {
    void* previous = obj->link;
    u32 flags;
    u32 clear;
    obj->first = first;
    obj->second = second;
    obj->link = link;
    flags = obj->flags;
    clear = 0x21;
    clear = -clear;
    clear &= flags;
    obj->flags = clear;
    return previous;
}

struct UpperMotion {
    u8 pad_00[4];
    s32 x;
    s32 y;
    s32 previous_x;
    s32 previous_y;
    s16 delta_x;
    u8 pad_16[2];
    s16 delta_y;
};

UPPER_SECTION(sub_815FAE4) void sub_815FAE4(struct UpperMotion* object, s32 y_offset) {
    s32 delta;
    s32 y;
    object->x += object->delta_x;
    delta = object->delta_y;
    y = object->y;
    y += delta;
    y += y_offset;
    object->y = y;
}

struct UpperCoordinates {
    u8 pad_00[0x0C];
    s16* output;
    u8 pad_10[4];
    s32 x;
    s32 y;
};

struct UpperReset {
    u16 values[4];
    u32 words[5];
};

struct UpperEntry {
    u8 pad_00[0x40];
    u32 field_40;
    void* field_44;
    u16 field_48;
};

UPPER_SECTION(sub_8142CF0) void sub_8142CF0(void* unused, void* argument, void (**output)(void)) {
    if ((u8)sub_813B5B4(argument) == 0)
        *output = sub_813E974;
}

UPPER_SECTION(sub_814704C) void sub_814704C(void* unused, void* argument, void (**output)(void)) {
    if ((u8)sub_813B650(argument) == 0)
        *output = sub_814706C;
}

#define DEFINE_INITIALIZER_ZERO(name, descriptor) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    *(u16*)((u8*)object + 0x36) = 0; \
    *(u16*)((u8*)object + 0x38) = 0; \
    *(u16*)((u8*)object + 0x34) = value; \
    sub_815F97C(object, 0); \
    return object; \
}

#define DEFINE_INITIALIZER(name, descriptor) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    *(u16*)((u8*)object + 0x34) = value; \
    sub_815F97C(object, 0); \
    return object; \
}

#define DEFINE_INITIALIZER_COPY_POSITION(name, descriptor) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    u32 x; \
    u32 y; \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    *(u16*)((u8*)object + 0x34) = value; \
    x = *(u32*)((u8*)object + 4); \
    y = *(u32*)((u8*)object + 8); \
    *(u32*)((u8*)object + 0x38) = x; \
    *(u32*)((u8*)object + 0x3C) = y; \
    sub_815F97C(object, 0); \
    return object; \
}

#define DEFINE_INITIALIZER_IDLE(name, descriptor) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    *(u16*)((u8*)object + 0x34) = value; \
    *(u8*)((u8*)object + 0x24) = 0; \
    return object; \
}

#define DEFINE_RESET_WRAPPER(name, descriptor, offset) \
UPPER_SECTION(name) void name(void* object, void* argument) { \
    void* child; \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    child = *(void**)((u8*)object + (offset)); \
    if (child != 0) { \
        sub_8021308(child); \
        *(void**)((u8*)object + (offset)) = 0; \
    } \
    sub_815FB14(object, argument); \
}

DEFINE_INITIALIZER(sub_815852C, 0x08CDC5F0)
DEFINE_INITIALIZER(sub_815ED84, 0x08CDCB10)
DEFINE_INITIALIZER_COPY_POSITION(sub_81585EC, 0x08CDC630)
DEFINE_INITIALIZER_COPY_POSITION(sub_815EE44, 0x08CDCB50)
DEFINE_RESET_WRAPPER(sub_8158C98, 0x08CDC8F0, 0x40)
DEFINE_RESET_WRAPPER(sub_815EFAC, 0x08CDCC50, 0x34)

#define DEFINE_MARIO_PAIR_SELECT(name, address) \
UPPER_SECTION(name) void name(u8* object) { \
    struct UpperMarioPair { u32 first; u32 second; } choices; \
    u32 offset = object[8]; \
    choices = *(struct UpperMarioPair*)(address); \
    offset &= 4; \
    *(u32*)(object + 0x18) = *(u32*)((u8*)&choices + offset); \
}

#define DEFINE_ZERO_STATE_INITIALIZER(name, descriptor, state) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    *(u16*)((u8*)object + 0x34) = value; \
    *(u16*)((u8*)object + 0x36) = 0; \
    *(u16*)((u8*)object + 0x38) = 0; \
    *(u8*)((u8*)object + 0x24) = (state); \
    sub_815F97C(object, 0); \
    return object; \
}

#define DEFINE_IDLE_INITIALIZER_WITH_SETUP(name, descriptor) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    *(u16*)((u8*)object + 0x34) = value; \
    *(u8*)((u8*)object + 0x24) = 0; \
    sub_815F97C(object, 0); \
    return object; \
}

#define DEFINE_UPPER_CALLBACK_SETUP(name, delta, next) \
UPPER_SECTION(name) void name(void* unused, u8* context, void** output) { \
    u8* base = *(u8**)(context + 0x1B0); \
    if ((u8)sub_813B650(context) == 0) { \
        u32 index = *(u16*)(context + 0x1D0); \
        u32 selected = base[index + (delta)]; \
        *(u16*)(context + 0x1D2) = selected; \
        output[0] = (void*)0x0813B1E9; \
        output[3] = (void*)0x0813B361; \
        output[1] = (void*)(next); \
    } \
}

DEFINE_UPPER_CALLBACK_SETUP(sub_814260C, 0x58, 0x08141D55)
DEFINE_UPPER_CALLBACK_SETUP(sub_8142760, 0x4E, 0x08141509)
DEFINE_UPPER_CALLBACK_SETUP(sub_8142BCC, 0x6C, 0x0813E619)

#define DEFINE_UPPER_ENABLE_CALLBACKS(name, next) \
UPPER_SECTION(name) void name(void* unused, u8* context) { \
    context[0x33E] |= 0x10; \
    sub_8139AA0(context); \
    *(void**)(context + 0x198) = (void*)0x0813B381; \
    *(void**)(context + 0x1A0) = (void*)(next); \
}

DEFINE_UPPER_ENABLE_CALLBACKS(sub_81427E0, 0x08141509)
DEFINE_UPPER_ENABLE_CALLBACKS(sub_8147010, 0x08146FAD)

#define DEFINE_UPPER_PREPARE_STATE(name, state) \
UPPER_SECTION(name) void name(u8* object) { \
    void* child = sub_815FA3C(object); \
    if (child != 0) { \
        sub_815FA70(object, 1); \
        *(u16*)((u8*)sub_815FA3C(object) + 0x0C) = 0; \
    } \
    *(u16*)(object + 0x36) = 0x1E; \
    object[0x24] = (state); \
}

DEFINE_UPPER_PREPARE_STATE(sub_8158A20, 4)
DEFINE_UPPER_PREPARE_STATE(sub_8158ABC, 2)

#define DEFINE_UPPER_CHILD_WRAPPER(name, descriptor) \
UPPER_SECTION(name) void name(u8* object, void* argument) { \
    u8* child; \
    u8* definition; \
    *(void**)(object + 0x30) = (void*)(descriptor); \
    if (*(u8**)(object + 0x3C) != 0) { \
        sub_815FAFC(*(u8**)(object + 0x3C)); \
        child = *(u8**)(object + 0x3C); \
        if (child != 0) { \
            definition = *(u8**)(child + 0x30); \
            (*(void (**)(void*, s32))(definition + 0x0C))( \
                child + *(s16*)(definition + 8), 3); \
        } \
    } \
    sub_815FB14(object, argument); \
}

DEFINE_UPPER_CHILD_WRAPPER(sub_8158EEC, 0x08CDC9F0)
DEFINE_UPPER_CHILD_WRAPPER(sub_815F58C, 0x08CDCF10)

#define DEFINE_UPPER_COMPLEX_INITIALIZER(name, descriptor) \
UPPER_SECTION(name) void* name(void* object, s32 mode, u16 value) { \
    u8* cursor; \
    u32 zero; \
    sub_815F8F4(); \
    *(void**)((u8*)object + 0x30) = (void*)(descriptor); \
    cursor = (u8*)object + 0x24; \
    zero = 0; \
    *cursor = zero; \
    *(u16*)((u8*)object + 0x34) = zero; \
    *(u16*)((u8*)object + 0x36) = value; \
    cursor += 0x1C; \
    *(u16*)cursor = zero; \
    *(u32*)((u8*)object + 0x3C) = zero; \
    *(u32*)((u8*)object + 0x44) = zero; \
    sub_815F97C(object, 0); \
    return object; \
}

#define DEFINE_UPPER_COUNTED_MOTION(name) \
UPPER_SECTION(name) u32 name(u8* object) { \
    if (*(u16*)(object + 0x2DE) == 0) \
        return 0; \
    *(s32*)(object + 0x0C) += *(s16*)(object + 0x242); \
    *(s32*)(object + 0x10) += *(s16*)(object + 0x244); \
    --*(u16*)(object + 0x2DE); \
    return *(u16*)(object + 0x2DE) != 0; \
}

#define DEFINE_UPPER_RUNTIME_UPDATE(name) \
UPPER_SECTION(name) void name(void) { \
    struct UpperRuntimeState { u8 pad[0x880]; u32 slot; }; \
    u8* base; \
    u8* holder; \
    struct UpperRuntimeState* state; \
    void (**first)(void*, void*); \
    u32 (**second)(void*, u32); \
    sub_8020A78(); \
    first = (void (**)(void*, void*))0x03000D48; \
    holder = (u8*)0x0203FFB8; \
    base = *(u8**)(holder + 0x3C); \
    (*first)(base, base + 0xA14); \
    second = (u32 (**)(void*, u32))0x03000D4C; \
    base = *(u8**)(holder + 0x3C); \
    state = (struct UpperRuntimeState*)0x0300034C; \
    state->slot = (*second)(base, state->slot); \
}

#define DEFINE_UPPER_ENABLE_RESET_CALLBACKS(name, next) \
UPPER_SECTION(name) void name(void* unused, u8* context) { \
    context[0x33E] |= 0x10; \
    sub_8139AA0(context); \
    *(u16*)(context + 0x1D4) = 0; \
    *(void**)(context + 0x198) = (void*)0x0813B381; \
    *(void**)(context + 0x1A0) = (void*)(next); \
}

DEFINE_UPPER_ENABLE_RESET_CALLBACKS(sub_8142B04, 0x0813FDF5)
DEFINE_UPPER_ENABLE_RESET_CALLBACKS(sub_8145920, 0x08144CD5)
DEFINE_UPPER_ENABLE_RESET_CALLBACKS(sub_814BCC0, 0x08148E99)

#define DEFINE_UPPER_CONSUME_FLAG(name, mask, half_offset, adjustment) \
UPPER_SECTION(name) void name(u8* object) { \
    u16* flags = (u16*)(object + 0x11E); \
    u16 bits = *flags; \
    if (bits & (mask)) { \
        u32 cleared = (u16)~(mask); \
        cleared &= bits; \
        *flags = cleared; \
        cleared = (half_offset); \
        *(u16*)(object + (cleared << 1)) = cleared - (adjustment); \
    } \
}

#define DEFINE_UPPER_ANIMATION_TRANSITION(name, next) \
UPPER_SECTION(name) void name(u8* object) { \
    u8* owner = *(u8**)(object + 0x2C); \
    u8* state = *(u8**)(owner + 0x28); \
    s32 animation = 6; \
    u8* sprite; \
    if (*(s16*)(state + 0xEC) == -1) \
        animation = 2; \
    sub_8082E1C(object, animation, 0, 0); \
    sprite = *(u8**)(object + 8); \
    sprite[0x12] = (sprite[0x12] & -7) | 2; \
    *(void**)(object + 0x4C) = (void*)(next); \
}
