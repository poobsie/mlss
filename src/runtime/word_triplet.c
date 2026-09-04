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

void word_triplet_add(struct WordTriplet* destination,
                      const struct WordTriplet* source)
    __attribute__((section(".text.sub_8163F6C")));
void word_triplet_add(struct WordTriplet* destination,
                      const struct WordTriplet* source) {
    destination->first += source->first;
    destination->second += source->second;
    destination->third += source->third;
}
__attribute__((section(".text.sub_8163F6C")))
const u16 word_triplet_add_padding = 0;

void word_triplet_set(struct WordTriplet* destination, u32 first,
                      u32 second, u32 third)
    __attribute__((section(".text.sub_8163FB8")));
void word_triplet_set(struct WordTriplet* destination, u32 first,
                      u32 second, u32 third) {
    destination->first = first;
    destination->second = second;
    destination->third = third;
}
