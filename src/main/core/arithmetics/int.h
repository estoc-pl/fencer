#ifndef FENCER_INT_H
#define FENCER_INT_H

#include <stdint.h>

#include "../errors.h"

#define DIVISION_BY_ZERO_ERROR "Division by zero detected"

extern const uint64_t MAX_INT;
extern const uint64_t MIN_INT;
extern const uint64_t INT_ZERO;
extern const uint64_t INT_ONE;

uint64_t int_add(uint64_t term1, uint64_t term2);

uint64_t int_subtract(uint64_t term1, uint64_t term2);

uint64_t int_negate(uint64_t term);

uint64_t int_abs(uint64_t term);

uint64_t int_multiply(uint64_t term1, uint64_t term2);

uint64_t int_divide(uint64_t term1, uint64_t term2, FencerError **error);

#endif //FENCER_INT_H
