#ifndef GUARD_RUNTIME_WORD_TRIPLET_H
#define GUARD_RUNTIME_WORD_TRIPLET_H

#include "global.h"

struct WordTriplet {
    u32 first;
    u32 second;
    u32 third;
};

#define word_triplet_copy sub_8163FA8
#define word_triplet_add sub_8163F6C
#define word_triplet_set sub_8163FB8

void word_triplet_copy(struct WordTriplet* destination,
                       const struct WordTriplet* source);
void word_triplet_add(struct WordTriplet* destination,
                      const struct WordTriplet* source);
void word_triplet_set(struct WordTriplet* destination, u32 first,
                      u32 second, u32 third);

#endif
