#include "int.h"

const uint64_t MAX_INT = 0x7FFFFFFFFFFFFFFFULL;
const uint64_t MIN_INT = 0x8000000000000000ULL;
const uint64_t INT_ZERO = 0x0000000000000000ULL;
const uint64_t INT_ONE = 0x0000000000000001ULL;

const uint64_t MINUS_ZERO = 0xFFFFFFFFFFFFFFFFULL;

uint64_t int_add(const uint64_t term1, const uint64_t term2) {
    const uint64_t term1_temp = term1 & MAX_INT;
    const uint64_t term2_temp = term2 & MAX_INT;
    uint64_t result = term1_temp + term2_temp;

    const uint64_t sign1 = term1 & MIN_INT;
    const uint64_t sign2 = term2 & MIN_INT;
    const uint64_t should_invert_sign = sign1 ^ sign2;

    if (sign1 & sign2 || result & should_invert_sign) {
        result += INT_ONE;
    }

    if (should_invert_sign) {
        result = ~result ^ MAX_INT;
    }

    if (result == MINUS_ZERO) {
        return INT_ZERO;
    }

    return result;
}

uint64_t int_subtract(const uint64_t term1, const uint64_t term2) {
    return int_add(term1, int_negate(term2));
}

uint64_t int_negate(const uint64_t term) {
    if (term == INT_ZERO) {
        return term;
    }
    return ~term;
}

uint64_t int_abs(const uint64_t term) {
    if (term & MIN_INT) {
        return int_negate(term);
    }
    return term;
}

uint64_t int_multiply(const uint64_t term1, const uint64_t term2) {
    const uint64_t term1_temp = int_abs(term1);
    const uint64_t term2_temp = int_abs(term2);
    uint64_t low_result = INT_ZERO;
    uint64_t high_result = INT_ZERO;

    for (uint64_t mask = INT_ONE; mask != 0; mask <<= 1) {
        if (term2_temp & mask) {
            high_result += term1_temp;
        }

        low_result >>= 1;
        low_result |= high_result << 63;
        high_result >>= 1;
    }

    if ((term1 ^ term2) & MIN_INT) {
        return int_negate(low_result);
    }

    return low_result;
}

uint64_t int_divide(const uint64_t term1, const uint64_t term2, FencerError **error) {
    if (term2 == INT_ZERO) {
        *error = init_fencer_error(DIVISION_BY_ZERO_ERROR, false);
        return INT_ZERO;
    }

    uint64_t rest = ~int_abs(term1) & MAX_INT;
    uint64_t divisor = int_abs(term2);

    uint8_t shifted_bits = 0;
    while (!(divisor & 0x4000000000000000ULL)) {
        divisor <<= 1;
        shifted_bits++;
    }

    uint64_t result = INT_ZERO;
    for (uint64_t result_mask = MIN_INT >> (63 - shifted_bits); result_mask != 0; result_mask >>= 1) {
        const uint64_t new_rest = rest + divisor;

        if (!(new_rest & MIN_INT)) {
            result |= result_mask;
            rest = new_rest;
        }

        divisor >>= 1;
    }

    if ((term1 ^ term2) & MIN_INT) {
        return int_negate(result);
    }

    return result;
}
