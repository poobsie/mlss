#ifndef GUARD_MARIO_BROS_CALLBACK_H
#define GUARD_MARIO_BROS_CALLBACK_H

/* Register trampolines retained under their link symbols in assembly. */
#define mario_bros_call_callback sub_8F6F35C
#define mario_bros_call_callback_with_object sub_8F6F360
#define mario_bros_call_callback_with_two_args sub_8F6F364
#define mario_bros_call_secondary_callback_with_object sub_8F95EC0

void mario_bros_call_callback(void* callback);
void mario_bros_call_callback_with_object(void* object, void* callback);
void mario_bros_call_callback_with_two_args(void* arg0, void* arg1, void* callback);
void mario_bros_call_secondary_callback_with_object(void* object, void* callback);

extern void* gMarioBrosObjectCallbackA;
extern void* gMarioBrosObjectCallbackB;
extern void* gMarioBrosTwoArgumentCallback;
extern void* gMarioBrosSecondaryObjectCallbackA;
extern void* gMarioBrosSecondaryObjectCallbackB;

#endif
