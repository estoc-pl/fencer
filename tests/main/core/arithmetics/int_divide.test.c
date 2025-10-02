#include "int_divide.test.h"

#include <stdlib.h>

#include "arithmetics/int.h"

static void test_divide_without_reminder() {
    CU_ASSERT_EQUAL(
        int_divide(0x00000000000007D1ULL /* 2001 */, 0x0000000000000017ULL /* 23 */, NULL),
        0x0000000000000057ULL /* 87 */
    );
}

static void test_divide_and_return_int_part() {
    CU_ASSERT_EQUAL(
        int_divide(0x000000000000E091ULL /* 57489 */, 0x000000000000014BULL /* 331 */, NULL),
        0x00000000000000ADULL /* 173 */
    );
}

static void test_divide_one_by_two() {
    CU_ASSERT_EQUAL(
        int_divide(0x0000000000000001ULL /* 1 */, 0x0000000000000002ULL /* 2 */, NULL),
        0x0000000000000000ULL /* 0 */
    );
}

static void test_divide_max_int_by_zero() {
    FencerError *error = NULL;

    int_divide(MAX_INT /* 9223372036854775807 */, 0x0000000000000000ULL /* 0 */, &error);

    CU_ASSERT_NOT_EQUAL(error, NULL);
}

static void test_divide_zero_by_max_int() {
    CU_ASSERT_EQUAL(
        int_divide(0x0000000000000000ULL /* 0 */, MAX_INT /* 9223372036854775807 */, NULL),
        0x0000000000000000ULL /* 0 */
    );
}

static void test_divide_max_int_by_max_int() {
    CU_ASSERT_EQUAL(
        int_divide(MAX_INT /* 9223372036854775807 */, MAX_INT /* 9223372036854775807 */, NULL),
        0x0000000000000001ULL /* 1 */
    );
}

static void test_divide_min_int_by_min_int() {
    CU_ASSERT_EQUAL(
        int_divide(MIN_INT /* -9223372036854775807 */, MIN_INT /* -9223372036854775807 */, NULL),
        0x0000000000000001ULL /* 1 */
    );
}

static void test_divide_max_int_by_min_int() {
    CU_ASSERT_EQUAL(
        int_divide(MAX_INT /* 9223372036854775807 */, MIN_INT /* -9223372036854775807 */, NULL),
        0xFFFFFFFFFFFFFFFEULL /* -1 */
    );
}

static void test_divide_min_int_by_max_int() {
    CU_ASSERT_EQUAL(
        int_divide(MIN_INT /* -9223372036854775807 */, MAX_INT /* 9223372036854775807 */, NULL),
        0xFFFFFFFFFFFFFFFEULL /* -1 */
    );
}

static void test_divide_max_int_by_one() {
    CU_ASSERT_EQUAL(
        int_divide(MAX_INT /* 9223372036854775807 */, 0x0000000000000001ULL /* 1 */, NULL),
        MAX_INT /* 9223372036854775807 */
    );
}

static void test_divide_min_int_by_one() {
    CU_ASSERT_EQUAL(
        int_divide(MIN_INT /* -9223372036854775807 */, 0x0000000000000001ULL /* 1 */, NULL),
        MIN_INT /* -9223372036854775807 */
    );
}

static void test_divide_one_by_max_int() {
    CU_ASSERT_EQUAL(
        int_divide(0x0000000000000001ULL /* 1 */, MAX_INT /* 9223372036854775807 */, NULL),
        0x0000000000000000ULL /* 0 */
    );
}

static void test_divide_one_by_min_int() {
    CU_ASSERT_EQUAL(
        int_divide(0x0000000000000001ULL /* 1 */, MIN_INT /* -9223372036854775807 */, NULL),
        0x0000000000000000ULL /* 0 */
    );
}

CU_pSuite initialize_arithmetics_int_divide_test_suite() {
    CU_pSuite suite = CU_add_suite("arithmetics | int | divide", NULL, NULL);
    if (suite != NULL) {
        CU_add_test(suite, "should divide without reminder", test_divide_without_reminder);
        CU_add_test(suite, "should return int part of division result", test_divide_and_return_int_part);
        CU_add_test(suite, "should divide 1 by 2", test_divide_one_by_two);
        CU_add_test(suite, "should return error when attempting to divide by 0", test_divide_max_int_by_zero);
        CU_add_test(suite, "should divide 0 by MAX_INT", test_divide_zero_by_max_int);
        CU_add_test(suite, "should divide MAX_INT by MAX_INT", test_divide_max_int_by_max_int);
        CU_add_test(suite, "should divide MIN_INT by MIN_INT", test_divide_min_int_by_min_int);
        CU_add_test(suite, "should divide MAX_INT by MIN_INT", test_divide_max_int_by_min_int);
        CU_add_test(suite, "should divide MIN_INT by MAX_INT", test_divide_min_int_by_max_int);
        CU_add_test(suite, "should divide MAX_INT by 1", test_divide_max_int_by_one);
        CU_add_test(suite, "should divide MIN_INT by 1", test_divide_min_int_by_one);
        CU_add_test(suite, "should divide 1 by MAX_INT", test_divide_one_by_max_int);
        CU_add_test(suite, "should divide 1 by MIN_INT", test_divide_one_by_min_int);
    }
    return suite;
}
