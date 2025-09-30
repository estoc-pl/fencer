#include "int_multiply.test.h"
#include "arithmetics/int.h"

static void test_multiply_positives() {
    CU_ASSERT_EQUAL(
        int_multiply(0x0000000000000010ULL /* 16 */, 0x0000000000000025ULL /* 37 */),
        0x0000000000000250ULL /* 592 */
    );
}

static void test_multiply_positive_and_negative() {
    CU_ASSERT_EQUAL(
        int_multiply(0x0000000000000270ULL /* 624 */, 0xFFFFFFFFFFFFFF84ULL /* -123 */),
        0xFFFFFFFFFFFED42FULL /* -76752 */
    );
}

static void test_multiply_negative_and_positive() {
    CU_ASSERT_EQUAL(
        int_multiply(0xFFFFFFFFFFFFFC7EULL /* -897 */, 0x00000000000008C8ULL /* 2248 */),
        0xFFFFFFFFFFE13B37ULL /* -2016456 */
    );
}

static void test_multiply_negatives() {
    CU_ASSERT_EQUAL(
        int_multiply(0xFFFFFFFFFFFFE225ULL /* -7642 */, 0xFFFFFFFFFFFFD2D3ULL /* -11564 */),
        0x0000000005447378ULL /* 88372088 */
    );
}

static void test_multiply_max_int_and_max_int() {
    CU_ASSERT_EQUAL(
        int_multiply(MAX_INT /* 9223372036854775807 */, MAX_INT /* 9223372036854775807 */),
        0x0000000000000001ULL /* 1 */
    );
}

static void test_multiply_max_int_and_min_int() {
    CU_ASSERT_EQUAL(
        int_multiply(MAX_INT /* 9223372036854775807 */, MIN_INT /* -9223372036854775807 */),
        0xFFFFFFFFFFFFFFFEULL /* -1 */
    );
}

static void test_multiply_min_int_and_max_int() {
    CU_ASSERT_EQUAL(
        int_multiply(MIN_INT /* -9223372036854775807 */, MAX_INT /* 9223372036854775807 */),
        0xFFFFFFFFFFFFFFFEULL /* -1 */
    );
}

static void test_multiply_min_int_and_min_int() {
    CU_ASSERT_EQUAL(
        int_multiply(MIN_INT /* -9223372036854775807 */, MIN_INT /* -9223372036854775807 */),
        0x0000000000000001ULL /* 1 */
    );
}

static void test_multiply_max_int_and_zero() {
    CU_ASSERT_EQUAL(
        int_multiply(MAX_INT /* 9223372036854775807 */, INT_ZERO /* 0 */),
        INT_ZERO /* 0 */
    );
}

static void test_multiply_min_int_and_zero() {
    CU_ASSERT_EQUAL(
        int_multiply(MIN_INT /* -9223372036854775807 */, INT_ZERO /* 0 */),
        INT_ZERO /* 0 */
    );
}

static void test_multiply_max_int_and_one() {
    CU_ASSERT_EQUAL(
        int_multiply(MAX_INT /* 9223372036854775807 */, INT_ONE /* 1 */),
        MAX_INT /* 9223372036854775807 */
    );
}

static void test_multiply_min_int_and_one() {
    CU_ASSERT_EQUAL(
        int_multiply(MIN_INT /* -9223372036854775807 */, INT_ONE /* 1 */),
        MIN_INT /* -9223372036854775807 */
    );
}

CU_pSuite initialize_arithmetics_int_multiply_test_suite() {
    CU_pSuite suite = CU_add_suite("arithmetics | int | multiply", NULL, NULL);
    if (suite != NULL) {
        CU_add_test(suite, "should multiply two positives", test_multiply_positives);
        CU_add_test(suite, "should multiply positive and negative", test_multiply_positive_and_negative);
        CU_add_test(suite, "should multiply negative and positive", test_multiply_negative_and_positive);
        CU_add_test(suite, "should multiply two negatives", test_multiply_negatives);
        CU_add_test(suite, "should multiply MAX_INT and MAX_INT", test_multiply_max_int_and_max_int);
        CU_add_test(suite, "should multiply MAX_INT and MIN_INT", test_multiply_max_int_and_min_int);
        CU_add_test(suite, "should multiply MIN_INT and MAX_INT", test_multiply_min_int_and_max_int);
        CU_add_test(suite, "should multiply MIN_INT and MIN_INT", test_multiply_min_int_and_min_int);
        CU_add_test(suite, "should multiply MAX_INT and 0", test_multiply_max_int_and_zero);
        CU_add_test(suite, "should multiply MIN_INT and 0", test_multiply_min_int_and_zero);
        CU_add_test(suite, "should multiply MAX_INT and 1", test_multiply_max_int_and_one);
        CU_add_test(suite, "should multiply MIN_INT and 1", test_multiply_min_int_and_one);
    }
    return suite;
}
