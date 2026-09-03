#ifndef GUARD_RUNTIME_WORD_TRIPLET_H
#define GUARD_RUNTIME_WORD_TRIPLET_H

#include "global.h"

struct WordTriplet {
    u32 first;
    u32 second;
    u32 third;
};

#define word_triplet_copy sub_8163FA8

void word_triplet_copy(struct WordTriplet* destination,
                       const struct WordTriplet* source);

#endif
