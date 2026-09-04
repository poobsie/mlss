#ifndef GUARD_OBJECT_ACTION_FACTORY_H
#define GUARD_OBJECT_ACTION_FACTORY_H

#include "global.h"

typedef void (*ObjectActionUpdate)(void);

void sub_80DEEA8(
    u32 coordinate0, u32 coordinate1, u32 coordinate2, u32 eventId,
    ObjectActionUpdate update, u32 visualId, u32 visualVariant,
    u32 pathMode, u32 pointCount, u32 objectOrientation,
    u32 visualOrientation, const void* pointData, u32 trailingPointCount);

#define object_create_scripted_action sub_80DEEA8
#define object_create_action_8175768 sub_8176894
#define object_create_action_81744FC sub_8176AA0
#define object_create_action_817399C sub_8176CB8
#define object_create_action_8173104 sub_8176DAC
#define object_create_action_81729C4 sub_8176ED8
#define object_create_action_81723C0 sub_8176FCC
#define object_create_action_81881E0 sub_818B6C4
#define object_create_action_81873FC sub_818B930
#define object_create_action_8185B40 sub_818BC7C
#define object_create_action_8185054 sub_818BDF0
#define object_create_action_8184654 sub_818BFD4
#define object_create_action_81829EC sub_818C31C
#define object_create_action_8180BE4 sub_818C628
#define object_create_action_817E608 sub_818CB18
#define object_create_action_817C8BC sub_818CEA8
#define object_create_action_817B980 sub_818D180
#define object_create_action_817A84C sub_818D3A8
#define object_create_action_817A00C sub_818D498
#define object_create_action_81798C8 sub_818D590
#define object_create_action_8178038 sub_818D820
#define object_create_action_81773F8 sub_818D94C

void object_create_action_8175768(u32, u32, u32, u32);
void object_create_action_81744FC(u32, u32, u32, u32);
void object_create_action_817399C(u32, u32, u32, u32);
void object_create_action_8173104(u32, u32, u32, u32);
void object_create_action_81729C4(u32, u32, u32, u32);
void object_create_action_81723C0(u32, u32, u32, u32);
void object_create_action_81881E0(u32, u32, u32, u32);
void object_create_action_81873FC(u32, u32, u32, u32);
void object_create_action_8185B40(u32, u32, u32, u32);
void object_create_action_8185054(u32, u32, u32, u32);
void object_create_action_8184654(u32, u32, u32, u32);
void object_create_action_81829EC(u32, u32, u32, u32);
void object_create_action_8180BE4(u32, u32, u32, u32);
void object_create_action_817E608(u32, u32, u32, u32);
void object_create_action_817C8BC(u32, u32, u32, u32);
void object_create_action_817B980(u32, u32, u32, u32);
void object_create_action_817A84C(u32, u32, u32, u32);
void object_create_action_817A00C(u32, u32, u32, u32);
void object_create_action_81798C8(u32, u32, u32, u32);
void object_create_action_8178038(u32, u32, u32, u32);
void object_create_action_81773F8(u32, u32, u32, u32);

#endif
