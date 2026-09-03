#include "global.h"
#include "runtime/callback_table.h"
#include "runtime/callback_packet.h"

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

__attribute__((section(".text.early_code_helpers.sub_801DC38")))
void sub_801DC38(struct RuntimeCallbackPacket* packet)
{
    packet->callback(packet->first, packet->second);
}
__attribute__((section(".text.early_code_helpers.sub_801DC38")))
const u16 sub_801DC38_padding = 0;

void runtime_invoke_pair_callback(struct RuntimeCallbackPacket* packet)
    __attribute__((alias("sub_801DC38")));
