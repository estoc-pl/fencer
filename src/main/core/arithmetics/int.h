#ifndef FENCER_INT_H
#define FENCER_INT_H

#include <stdint.h>

#include "../errors.h"

#define DIVISION_BY_ZERO_ERROR "Division by zero detected"

#define MAX_INT 0x7FFFFFFFFFFFFFFFULL
#define MIN_INT 0x8000000000000000ULL
#define INT_ZERO 0x0000000000000000ULL
#define INT_ONE 0x0000000000000001ULL

uint64_t int_add(uint64_t term1, uint64_t term2);

uint64_t int_subtract(uint64_t term1, uint64_t term2);

uint64_t int_negate(uint64_t term);

uint64_t int_abs(uint64_t term);

uint64_t int_multiply(uint64_t term1, uint64_t term2);

uint64_t int_divide(uint64_t term1, uint64_t term2, FencerError **error);

#endif //FENCER_INT_H
