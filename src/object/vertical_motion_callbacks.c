#include "object/vertical_motion_callbacks.h"

#define SEC(symbol) __attribute__((section(".text.object_vertical_motion." #symbol)))

u8 sub_808CAC4(struct RuntimeObject* object);
void sub_8082E1C(
    struct RuntimeObject* object, s32 animation, s32 command, s32 value);

void sub_808E09C(struct RuntimeObject* object);
void sub_808E0C8(struct RuntimeObject* object);
void sub_808EFFC(struct RuntimeObject* object);
void sub_808FFF8(struct RuntimeObject* object);
void sub_8090608(struct RuntimeObject* object);
void sub_8090974(struct RuntimeObject* object);
void sub_8090D70(struct RuntimeObject* object);
void sub_8091EE0(struct RuntimeObject* object);
void sub_8091F48(struct RuntimeObject* object);
void sub_8091FB0(struct RuntimeObject* object);
void sub_8093070(struct RuntimeObject* object);
void sub_80930D8(struct RuntimeObject* object);
void sub_8093140(struct RuntimeObject* object);
void sub_80941FC(struct RuntimeObject* object);
void sub_8094264(struct RuntimeObject* object);
void sub_80942CC(struct RuntimeObject* object);
void sub_8094654(struct RuntimeObject* object);
void sub_80946BC(struct RuntimeObject* object);
void sub_8094724(struct RuntimeObject* object);
void sub_8094AAC(struct RuntimeObject* object);
void sub_8094B14(struct RuntimeObject* object);
void sub_8094B7C(struct RuntimeObject* object);
void sub_8094F04(struct RuntimeObject* object);
void sub_8094F6C(struct RuntimeObject* object);
void sub_8094FD4(struct RuntimeObject* object);

#define DEFINE_VERTICAL_MOTION_CALLBACK(symbol, name, command, next) \
    SEC(symbol)                                                       \
    void name(struct RuntimeObject* object)                           \
    {                                                                \
        s8* flags;                                                   \
                                                                     \
        object->verticalVelocity += object->verticalAcceleration;    \
        object->verticalPosition =                                   \
            object->positionZBase + object->verticalVelocity;        \
        if (object->verticalVelocity <= 0) {                          \
            object->update = next;                                   \
            if (sub_808CAC4(object) == 0) {                           \
                sub_8082E1C(object, 6, command, 0);                   \
                flags = (s8*)&object->visual->flags;                 \
                *flags = (*flags & -7) | 2;                          \
                flags = (s8*)&object->flags77;                       \
                *flags = (*flags & -8) | 1;                          \
            }                                                        \
        }                                                            \
    }

#define DEFINE_FLOOR_LANDING_CALLBACK(symbol, name, next)               \
    SEC(symbol)                                                         \
    void name(struct RuntimeObject* object)                             \
    {                                                                  \
        s8* flags;                                                     \
                                                                       \
        object->verticalVelocity += object->verticalAcceleration;      \
        object->verticalPosition =                                     \
            object->positionZBase + object->verticalVelocity;          \
        if (object->verticalPosition <= object->state->floorHeight) {   \
            flags = (s8*)&object->flags77;                             \
            *flags &= -8;                                              \
            object->verticalPosition = object->state->floorHeight;     \
            sub_8082E1C(object, 8, 0x204D, 0);                          \
            flags = (s8*)&object->visual->flags;                       \
            *flags = (*flags & -7) | 2;                                \
            object->update = next;                                     \
        }                                                              \
    }

#define DEFINE_ALTERNATE_FLOOR_LANDING_CALLBACK(symbol, name, next)     \
    SEC(symbol)                                                         \
    void name(struct RuntimeObject* object)                             \
    {                                                                  \
        s8* flags;                                                     \
                                                                       \
        object->verticalVelocity += object->verticalAcceleration;      \
        object->verticalPosition =                                     \
            object->positionZBase + object->verticalVelocity;          \
        if (object->verticalPosition <= object->state->floorHeight) {   \
            flags = (s8*)&object->flags77;                             \
            *flags &= -8;                                              \
            object->verticalPosition = object->state->floorHeight;     \
            sub_8082E1C(object, 8, 0x2000, 0);                          \
            flags = (s8*)&object->visual->flags;                       \
            *flags = (*flags & -7) | 2;                                \
            object->update = next;                                     \
        }                                                              \
    }

DEFINE_VERTICAL_MOTION_CALLBACK(sub_808DEEC, object_advance_vertical_motion_to_animation_6_initial_path, 0x204D, object_land_on_state_floor_with_animation_8_initial_path)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_808DF5C, object_advance_vertical_motion_to_alternate_animation_6_initial_path, 0x2000, object_land_on_state_floor_with_alternate_animation_8_initial_path)
DEFINE_FLOOR_LANDING_CALLBACK(sub_808DFCC, object_land_on_state_floor_with_animation_8_initial_path, sub_808E09C)
DEFINE_ALTERNATE_FLOOR_LANDING_CALLBACK(sub_808E034, object_land_on_state_floor_with_alternate_animation_8_initial_path, sub_808E0C8)

DEFINE_VERTICAL_MOTION_CALLBACK(sub_808EF1C, object_advance_vertical_motion_to_animation_6_path_a, 0x204D, sub_808EFFC)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_808FF18, object_advance_vertical_motion_to_animation_6_path_b, 0x204D, sub_808FFF8)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8090528, object_advance_vertical_motion_to_animation_6_path_c, 0x204D, sub_8090608)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8090894, object_advance_vertical_motion_to_animation_6_path_d, 0x204D, sub_8090974)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8090C90, object_advance_vertical_motion_to_animation_6_path_e, 0x204D, sub_8090D70)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8091E00, object_advance_vertical_motion_to_animation_6_path_f, 0x204D, sub_8091EE0)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8092F90, object_advance_vertical_motion_to_animation_6_path_g, 0x204D, sub_8093070)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_809411C, object_advance_vertical_motion_to_animation_6_path_h, 0x204D, sub_80941FC)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8094574, object_advance_vertical_motion_to_animation_6_path_i, 0x204D, sub_8094654)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_80949CC, object_advance_vertical_motion_to_animation_6_path_j, 0x204D, sub_8094AAC)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8094E24, object_advance_vertical_motion_to_animation_6_path_k, 0x204D, sub_8094F04)

DEFINE_VERTICAL_MOTION_CALLBACK(sub_8091E70, object_advance_vertical_motion_to_alternate_animation_6_path_a, 0x2000, sub_8091F48)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8093000, object_advance_vertical_motion_to_alternate_animation_6_path_b, 0x2000, sub_80930D8)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_809418C, object_advance_vertical_motion_to_alternate_animation_6_path_c, 0x2000, sub_8094264)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_80945E4, object_advance_vertical_motion_to_alternate_animation_6_path_d, 0x2000, sub_80946BC)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8094A3C, object_advance_vertical_motion_to_alternate_animation_6_path_e, 0x2000, sub_8094B14)
DEFINE_VERTICAL_MOTION_CALLBACK(sub_8094E94, object_advance_vertical_motion_to_alternate_animation_6_path_f, 0x2000, sub_8094F6C)

DEFINE_FLOOR_LANDING_CALLBACK(sub_8091EE0, object_land_on_state_floor_with_animation_8_path_a, sub_8091FB0)
DEFINE_FLOOR_LANDING_CALLBACK(sub_8093070, object_land_on_state_floor_with_animation_8_path_b, sub_8093140)
DEFINE_FLOOR_LANDING_CALLBACK(sub_80941FC, object_land_on_state_floor_with_animation_8_path_c, sub_80942CC)
DEFINE_FLOOR_LANDING_CALLBACK(sub_8094654, object_land_on_state_floor_with_animation_8_path_d, sub_8094724)
DEFINE_FLOOR_LANDING_CALLBACK(sub_8094AAC, object_land_on_state_floor_with_animation_8_path_e, sub_8094B7C)
DEFINE_FLOOR_LANDING_CALLBACK(sub_8094F04, object_land_on_state_floor_with_animation_8_path_f, sub_8094FD4)
