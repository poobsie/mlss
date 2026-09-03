#include "global.h"
#include "mario_bros/callback.h"
#include "mario_bros/functions.h"

#define MB_LATE_SECTION(name) __attribute__((section(".text.mariobros_late." #name)))

extern void sub_8F6D170(void);

MB_LATE_SECTION(sub_8F6DE98) void sub_8F6DE98(void) {
    sub_8F6D170();
}
MB_LATE_SECTION(sub_8F6DE98) const u16 sub_8F6DE98_padding = 0;

MB_LATE_SECTION(sub_8F6E1F8) void mario_bros_call_object_callback_a(void* object) {
    mario_bros_call_callback_with_object(object, gMarioBrosObjectCallbackA);
}

MB_LATE_SECTION(sub_8F6E20C) void mario_bros_call_object_callback_b(void* object) {
    mario_bros_call_callback_with_object(object, gMarioBrosObjectCallbackB);
}

MB_LATE_SECTION(sub_8F6F210) void mario_bros_call_two_argument_callback(void* arg0, void* arg1) {
    mario_bros_call_callback_with_two_args(arg0, arg1, gMarioBrosTwoArgumentCallback);
}

MB_LATE_SECTION(sub_8F94D78) void mario_bros_call_secondary_object_callback_a(void* object) {
    mario_bros_call_secondary_callback_with_object(object, gMarioBrosSecondaryObjectCallbackA);
}

MB_LATE_SECTION(sub_8F94D8C) void mario_bros_call_secondary_object_callback_b(void* object) {
    mario_bros_call_secondary_callback_with_object(object, gMarioBrosSecondaryObjectCallbackB);
}
