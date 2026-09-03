#include "global.h"
#include "battle/object.h"

void sub_815FB14(struct BattleDefinitionObject* object, void* argument,
                 const struct BattleObjectDefinition* definition);

#define OBJECT_WRAPPER_SECTION(name) __attribute__((section(name)))
#define OBJECT_WRAPPER_BODY(address)                                      \
    const struct BattleObjectDefinition* definition =                     \
        (const struct BattleObjectDefinition*)(address);                  \
    object->definition = definition;                                      \
    sub_815FB14(object, argument, definition)

void sub_8158450(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158450");
void sub_8158450(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC5B0);
}

void sub_8158518(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158518");
void sub_8158518(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC5F0);
}

void sub_815859C(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_815859C");
void sub_815859C(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC670);
}

void sub_81585D8(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81585D8");
void sub_81585D8(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC630);
}

void sub_8158654(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158654");
void sub_8158654(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC6B0);
}

void sub_81586FC(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81586FC");
void sub_81586FC(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC6F0);
}

void sub_8158808(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158808");
void sub_8158808(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC770);
}

void sub_81588C8(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81588C8");
void sub_81588C8(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC930);
}

void sub_8158920(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158920");
void sub_8158920(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC970);
}

void sub_8158994(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158994");
void sub_8158994(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC7B0);
}

void sub_81589DC(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_81589DC");
void sub_81589DC(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC7F0);
}

void sub_8158A50(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158A50");
void sub_8158A50(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC830);
}

void sub_8158AEC(struct BattleDefinitionObject* object, void* argument)
    OBJECT_WRAPPER_SECTION(".text.sub_8158AEC");
void sub_8158AEC(struct BattleDefinitionObject* object, void* argument) {
    OBJECT_WRAPPER_BODY(0x08CDC870);
}
