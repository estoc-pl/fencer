#include "int.h"

const uint64_t MAX_INT = 0x7FFFFFFFFFFFFFFFLU;
const uint64_t MIN_INT = 0x8000000000000000LU;
const uint64_t ZERO = 0x0000000000000000LU;
const uint64_t ONE = 0x0000000000000001LU;

const uint64_t MINUS_ZERO = 0xFFFFFFFFFFFFFFFFLU;

uint64_t add(const uint64_t term1, const uint64_t term2) {
    const uint64_t sign1 = term1 >> 63;
    const uint64_t sign2 = term2 >> 63;

    const uint64_t term1_temp = term1 & MAX_INT;
    const uint64_t term2_temp = term2 & MAX_INT;

    uint64_t result = term1_temp + term2_temp;
    const uint64_t result_sign = result >> 63;

    if (sign1 ^ sign2) {
        // invert result sign
        result = ~result ^ MAX_INT;
    }

    if (sign1 & sign2 || result_sign & (sign1 || sign2)) {
        result = result + ONE;
    }

    if (result == MINUS_ZERO) {
        return ZERO;
    }

    return result;
}
