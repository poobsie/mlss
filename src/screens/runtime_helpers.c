#include "audio/music.h"
#include "screens/runtime_helpers.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)
#define SEC(name) __attribute__((section(".text.upper." STRINGIFY(name))))

struct ScreenLayerOwner20 {
    u8 unknown000[0x20];
    void* layer20;
    u8 unknown024[0x45];
    u8 initialized69;
    u8 unknown06A[0xEC];
    u8 initialized156;
};

struct ScreenLayerOwner15C {
    u8 unknown000[0xEF];
    u8 initializedEF;
    u8 unknown0F0[0x6C];
    void* layer15C;
};

void sub_81151E4(
    void* layer, u8 flags, u16 value, u16 size,
    u16 firstMask, u16 secondMask, u32 firstData, u32 secondData);
void* alloc_Zero(s32 size, s32 clear, const char* label, s32 arena);
void sub_8117C9C(
    void* object, s32 priority, const char* label,
    s32 argument, s32 mode, s32 variant);
void sub_8127EF8(
    void* object, s32 priority, const char* label, s32 mode);
void sub_812A9A0(
    void* object, s32 priority, const char* label,
    s32 firstMode, s32 secondMode, s32 state);

SEC(screen_configure_layer20_default_and_mark_156)
void screen_configure_layer20_default_and_mark_156(
    struct ScreenLayerOwner20* owner)
{
    sub_81151E4(owner->layer20, 4, 0, 8, 0xFFFF, 0xFFFF, 0, 0);
    owner->initialized156 = 1;
}

SEC(screen_launch_menu_or_save)
void screen_launch_menu_or_save(s32 menuArgument, s32 useSaveScreen)
{
    if (useSaveScreen == 0) {
        sub_8117C9C(
            alloc_Zero(0x260, 0, (const char*)0x08202F70, 0),
            8, (const char*)0x08202F70, menuArgument, -2, useSaveScreen);
        return;
    }
    sub_8127EF8(
        alloc_Zero(0x128, 0, (const char*)0x08202F78, 0),
        8, (const char*)0x08202F78, -2);
}

SEC(screen_configure_layer15c_and_fade_music)
void screen_configure_layer15c_and_fade_music(
    struct ScreenLayerOwner15C* owner, u16 value)
{
    sub_81151E4(owner->layer15C, 4, value, 0x10, 0xFFFF, 0xFFFF, 0, 0);
    music_set_volume(0, 0, 0x10);
    owner->initializedEF = 1;
}

SEC(screen_configure_layer20_and_mark_69)
void screen_configure_layer20_and_mark_69(
    struct ScreenLayerOwner20* owner, u16 value)
{
    sub_81151E4(owner->layer20, 4, value, 8, 0xFFFF, 0xFFFF, 0, 0);
    owner->initialized69 = 1;
}

SEC(screen_configure_layer20_default)
void screen_configure_layer20_default(struct ScreenLayerOwner20* owner)
{
    sub_81151E4(owner->layer20, 4, 0, 8, 0xFFFF, 0xFFFF, 0, 0);
}

SEC(screen_launch_shop)
void screen_launch_shop(s32 firstMode, s32 secondMode)
{
    sub_812A9A0(
        alloc_Zero(0xC8, 0, (const char*)0x08211B20, 0),
        8, (const char*)0x08211B20, firstMode, secondMode, -2);
}
