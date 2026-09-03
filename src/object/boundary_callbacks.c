#include "object/functions.h"
#include "object/runtime_object.h"

void sub_8088020(struct RuntimeObject* object);
void sub_807C298(struct RuntimeObject* object);

#define DEFINE_BOUNDARY_CALLBACK(name, sectionName)                            \
    void name(struct RuntimeObject* object)                                    \
        __attribute__((section(sectionName)));                                 \
    void name(struct RuntimeObject* object)                                    \
    {                                                                          \
        sub_8088020(object);                                                    \
        if (object->visual->coordinate0 + object->boundaryOffset45 <= 0)       \
            sub_807C298(object);                                                \
    }                                                                          \
    __attribute__((section(sectionName))) const u16 name##_padding = 0;

DEFINE_BOUNDARY_CALLBACK(object_update_then_trigger_at_boundary_a,
                         ".text.vertical_boundary_callbacks.sub_809C13C")
DEFINE_BOUNDARY_CALLBACK(object_update_then_trigger_at_boundary_b,
                         ".text.vertical_boundary_callbacks.sub_809C1E8")
DEFINE_BOUNDARY_CALLBACK(object_update_then_trigger_at_boundary_c,
                         ".text.vertical_boundary_callbacks.sub_809C570")
