#include "global.h"
#include "field/metadata.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

#define FIELD_OBJECT_SET_DIRECTORIES ((struct FieldObjectSetDirectory**)0x083D6C58)
#define FIELD_PRIMARY_METADATA_TABLE ((void**)0x083D7458)
#define FIELD_SECONDARY_METADATA_TABLE ((void**)0x0851FA00)

SEC(sub_80FAEEC) u8 field_get_scene_state_value_9a1(struct FieldSceneOwner* owner)
{
    return owner->sceneState[0x9A1];
}

SEC(get_field_object_count) u8 get_field_object_count(u16 index, u8* countOut)
{
    struct FieldObjectSetDirectory* directory = FIELD_OBJECT_SET_DIRECTORIES[index];
    *countOut = directory->packedObjectCount >> 3;
    return *countOut;
}

SEC(sub_80FB7BC) void* field_get_object_resource_list(u16 index, u8* countOut)
{
    struct FieldObjectSetDirectory* directory = FIELD_OBJECT_SET_DIRECTORIES[index];

    *countOut = directory->packedResourceCount & 0x3F;
    return (u8*)directory
        - ((directory->resourceListBackOffsetHi << 8)
            | directory->resourceListBackOffsetLo);
}

SEC(sub_80FB7E0) void* field_get_metadata_table_a_entry(u16 index)
{
    return FIELD_PRIMARY_METADATA_TABLE[index];
}

SEC(sub_80FB7F0) void* field_get_metadata_table_b_entry(u16 index)
{
    return FIELD_SECONDARY_METADATA_TABLE[index];
}
