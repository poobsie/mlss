#include "global.h"

#define SEC(name) __attribute__((section(".text.callback_forwarders." #name)))

typedef void (*Callback)(void *, void *, void *);

#define DEFINE_CALLBACK_FORWARDER(name)                                 \
    SEC(name) void name(void *argument, void *callbacks)                \
    {                                                                    \
        void *slot = (u8 *)callbacks + 0x1A0;                           \
        Callback callback = *(Callback *)slot;                          \
        callback(argument, callbacks, slot);                            \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_CALLBACK_FORWARDER(sub_813B380)
DEFINE_CALLBACK_FORWARDER(sub_813C484)
DEFINE_CALLBACK_FORWARDER(sub_813C498)
