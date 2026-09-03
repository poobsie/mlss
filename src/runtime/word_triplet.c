#include "runtime/word_triplet.h"

void word_triplet_copy(struct WordTriplet* destination,
                       const struct WordTriplet* source)
    __attribute__((section(".text.sub_8163FA8")));
void word_triplet_copy(struct WordTriplet* destination,
                       const struct WordTriplet* source) {
    destination->first = source->first;
    destination->second = source->second;
    destination->third = source->third;
}

__attribute__((section(".text.sub_8163FA8")))
const u16 word_triplet_copy_padding = 0;
