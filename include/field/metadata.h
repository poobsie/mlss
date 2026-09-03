#ifndef GUARD_FIELD_METADATA_H
#define GUARD_FIELD_METADATA_H

#include "global.h"

/* Directory embedded inside each field-object definition blob. */
struct FieldObjectSetDirectory {
    u8 packedResourceCount;
    u8 packedObjectCount;
    u8 resourceListBackOffsetLo;
    u8 resourceListBackOffsetHi;
    u8 unknownListBackOffsetLo;
    u8 unknownListBackOffsetHi;
    u8 objectListBackOffsetLo;
    u8 objectListBackOffsetHi;
};

struct FieldSceneOwner {
    u8 unknown00[0x24];
    u8* sceneState;
};

#define field_get_scene_state_value_9a1 sub_80FAEEC
#define field_get_object_resource_list sub_80FB7BC
#define field_get_metadata_table_a_entry sub_80FB7E0
#define field_get_metadata_table_b_entry sub_80FB7F0

u8 get_field_object_count(u16 index, u8* countOut);

#endif
