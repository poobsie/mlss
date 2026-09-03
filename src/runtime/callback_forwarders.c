#include "global.h"
#include "runtime/callback_table.h"

#define SEC(name) __attribute__((section(".text.callback_forwarders." #name)))

#define DEFINE_CALLBACK_FORWARDER(name)                                 \
    SEC(name) void name(void* argument, struct RuntimeCallbackTable* table) \
    {                                                                    \
        RuntimeForwardedCallback* slot = &table->callback;               \
        RuntimeForwardedCallback callback = *slot;                       \
        callback(argument, table, slot);                                 \
    }                                                                    \
    SEC(name) const u16 name##_padding = 0;

DEFINE_CALLBACK_FORWARDER(sub_813B380)
DEFINE_CALLBACK_FORWARDER(sub_813C484)
DEFINE_CALLBACK_FORWARDER(sub_813C498)
