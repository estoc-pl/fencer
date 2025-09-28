#ifndef FENCER_INT_H
#define FENCER_INT_H

#include <stdint.h>

extern const uint64_t MAX_INT;
extern const uint64_t MIN_INT;
extern const uint64_t ZERO;
extern const uint64_t ONE;

uint64_t add(uint64_t term1, uint64_t term2);

uint64_t subtract(uint64_t term1, uint64_t term2);

uint64_t negate(uint64_t term);

#endif //FENCER_INT_H
