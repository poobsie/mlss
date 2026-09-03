#include "runtime/pointer_access.h"

#define SEC(symbol) __attribute__((section(".text.middle." #symbol)))

SEC(sub_80E92A8) void* runtime_dereference_pointer(void** pointer)
{
    return *pointer;
}
