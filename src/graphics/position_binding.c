#include "graphics/position_binding.h"

#define STRINGIFY_INNER(value) #value
#define STRINGIFY(value) STRINGIFY_INNER(value)

#define DEFINE_UPDATE_CALLBACK(name)                                      \
    void name(struct PositionBinding* binding,                            \
              const struct FixedPosition* origin)                         \
        __attribute__((section(".text.text_late_helpers." STRINGIFY(name)))); \
    void name(struct PositionBinding* binding,                            \
              const struct FixedPosition* origin) {                       \
        position_binding_update_relative(binding, origin);                \
    }                                                                     \
    __attribute__((section(".text.text_late_helpers." STRINGIFY(name))))  \
    const u16 name##_padding = 0;

DEFINE_UPDATE_CALLBACK(position_binding_update_callback_a)
DEFINE_UPDATE_CALLBACK(position_binding_update_callback_b)
DEFINE_UPDATE_CALLBACK(position_binding_update_callback_c)
DEFINE_UPDATE_CALLBACK(position_binding_update_callback_d)
