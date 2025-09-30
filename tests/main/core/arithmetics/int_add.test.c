#include "int_add.test.h"
#include "arithmetics/int.h"

static void test_add_positives() {
    CU_ASSERT_EQUAL(
        int_add(0x0000000000000011ULL /* 17 */, 0x0000000000000019ULL /* 25 */),
        0x000000000000002AULL /* 42 */
    );
}

static void test_add_positives_overflow() {
    CU_ASSERT_EQUAL(
        int_add(0x6000000000000000ULL /* 6917529027641081856 */, 0x5000000000000000ULL /* 5764607523034234880 */),
        0xB000000000000000ULL /* -5764607523034234879 */
    );
}

static void test_add_positive_to_negative() {
    CU_ASSERT_EQUAL(
        int_add(0xFFFFFFFFFFFFFEFEULL /* -257 */, 0x0000000000000058ULL /* 88 */),
        0xFFFFFFFFFFFFFF56ULL /* -169 */
    );
}

static void test_add_positive_to_negative_sign_change() {
    CU_ASSERT_EQUAL(
        int_add(0xFFFFFFFFFFFFFF90ULL /* -111 */, 0x0000000000000237ULL /* 567 */),
        0x00000000000001C8ULL /* 456 */
    );
}

static void test_add_negative_to_positive() {
    CU_ASSERT_EQUAL(
        int_add(0x00000000000003E6ULL /* 998 */, 0xFFFFFFFFFFFFFFB5ULL /* -74 */),
        0x000000000000039CULL /* 924 */
    );
}

static void test_add_negative_to_positive_sign_change() {
    CU_ASSERT_EQUAL(
        int_add(0x00000000000008C8ULL /* 2248 */, 0xFFFFFFFFFFFFE9F1ULL /* -5646 */),
        0xFFFFFFFFFFFFF2B9ULL /* -3398 */
    );
}

static void test_add_negatives() {
    CU_ASSERT_EQUAL(
        int_add(0xFFFFFFFFFFFFFFF0ULL /* -15 */, 0xFFFFFFFFFFFFFFE9ULL /* -22 */),
        0xFFFFFFFFFFFFFFDAULL /* -37 */
    );
}

static void test_add_negatives_overflow() {
    CU_ASSERT_EQUAL(
        int_add(0x9FFFFFFFFFFFFFFFULL /* -6917529027641081856 */, 0xAFFFFFFFFFFFFFFFULL /* -5764607523034234880 */),
        0x4FFFFFFFFFFFFFFFULL /* 5764607523034234879 */
    );
}

static void test_add_max_int_to_max_int() {
    CU_ASSERT_EQUAL(
        int_add(MAX_INT /* 9223372036854775807 */, MAX_INT /* 9223372036854775807 */),
        0xFFFFFFFFFFFFFFFEULL /* -1 */
    );
}

static void test_add_minus_max_int_to_max_int() {
    CU_ASSERT_EQUAL(
        int_add(MAX_INT /* 9223372036854775807 */, MIN_INT /* -9223372036854775807 */),
        0x0000000000000000ULL /* 0 */
    );
}

static void test_add_max_int_to_minus_max_int() {
    CU_ASSERT_EQUAL(
        int_add(MIN_INT /* -9223372036854775807 */, MAX_INT /* 9223372036854775807 */),
        0x0000000000000000ULL /* 0 */
    );
}

static void test_add_minus_max_int_to_minus_max_int() {
    CU_ASSERT_EQUAL(
        int_add(MIN_INT /* -9223372036854775807 */, MIN_INT /* -9223372036854775807 */),
        0x0000000000000001ULL /* 1 */
    );
}

CU_pSuite initialize_arithmetics_int_add_test_suite() {
    CU_pSuite suite = CU_add_suite("arithmetics | int | add", NULL, NULL);
    if (suite != NULL) {
        CU_add_test(suite, "should add two small positives", test_add_positives);
        CU_add_test(suite, "should add two positives with overflow", test_add_positives_overflow);
        CU_add_test(suite, "should add positive to negative", test_add_positive_to_negative);
        CU_add_test(
            suite,
            "should add positive to negative with sign change",
            test_add_positive_to_negative_sign_change
        );
        CU_add_test(suite, "should add negative to positive", test_add_negative_to_positive);
        CU_add_test(
            suite,
            "should add negative to positive with sign change",
            test_add_negative_to_positive_sign_change
        );
        CU_add_test(suite, "should add two small negatives", test_add_negatives);
        CU_add_test(suite, "should add two negatives with overflow", test_add_negatives_overflow);
        CU_add_test(suite, "should add MAX_INT to MAX_INT", test_add_max_int_to_max_int);
        CU_add_test(suite, "should add -MAX_INT to MAX_INT", test_add_minus_max_int_to_max_int);
        CU_add_test(suite, "should add MAX_INT to -MAX_INT", test_add_max_int_to_minus_max_int);
        CU_add_test(suite, "should add -MAX_INT to -MAX_INT", test_add_minus_max_int_to_minus_max_int);
    }

    return suite;
}
