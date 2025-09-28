#include "int.test.h"
#include "arithmetics/int.h"

static void test_add_positives() {
    CU_ASSERT_EQUAL(
        add(0x0000000000000011LU /* 17 */, 0x0000000000000019LU /* 25 */),
        0x000000000000002ALU /* 42 */
    );
}

static void test_add_positives_overflow() {
    CU_ASSERT_EQUAL(
        add(0x6000000000000000LU /* 6917529027641081856 */, 0x5000000000000000LU /* 5764607523034234880 */),
        0xB000000000000000LU /* -5764607523034234879 */
    );
}

static void test_add_positive_to_negative() {
    CU_ASSERT_EQUAL(
        add(0xFFFFFFFFFFFFFEFELU /* -257 */, 0x0000000000000058LU /* 88 */),
        0xFFFFFFFFFFFFFF56LU /* -169 */
    );
}

static void test_add_positive_to_negative_sign_change() {
    CU_ASSERT_EQUAL(
        add(0xFFFFFFFFFFFFFF90LU /* -111 */, 0x0000000000000237LU /* 567 */),
        0x00000000000001C8LU /* 456 */
    );
}

static void test_add_negative_to_positive() {
    CU_ASSERT_EQUAL(
        add(0x00000000000003E6LU /* 998 */, 0xFFFFFFFFFFFFFFB5LU /* -74 */),
        0x000000000000039CLU /* 924 */
    );
}

static void test_add_negative_to_positive_sign_change() {
    CU_ASSERT_EQUAL(
        add(0x00000000000008C8LU /* 2248 */, 0xFFFFFFFFFFFFE9F1LU /* -5646 */),
        0xFFFFFFFFFFFFF2B9LU /* -3398 */
    );
}

static void test_add_negatives() {
    CU_ASSERT_EQUAL(
        add(0xFFFFFFFFFFFFFFF0LU /* -15 */, 0xFFFFFFFFFFFFFFE9LU /* -22 */),
        0xFFFFFFFFFFFFFFDALU /* -37 */
    );
}

static void test_add_negatives_overflow() {
    CU_ASSERT_EQUAL(
        add(0x9FFFFFFFFFFFFFFFLU /* -6917529027641081856 */, 0xAFFFFFFFFFFFFFFFLU /* -5764607523034234880 */),
        0x4FFFFFFFFFFFFFFFLU /* 5764607523034234879 */
    );
}

static void test_add_max_int_to_max_int() {
    CU_ASSERT_EQUAL(
        add(MAX_INT /* 9223372036854775807 */, MAX_INT /* 9223372036854775807 */),
        0xFFFFFFFFFFFFFFFELU /* -1 */
    );
}

static void test_add_minus_max_int_to_max_int() {
    CU_ASSERT_EQUAL(
        add(MAX_INT /* 9223372036854775807 */, MIN_INT /* -9223372036854775807 */),
        0x0000000000000000LU /* 0 */
    );
}

static void test_add_max_int_to_minus_max_int() {
    CU_ASSERT_EQUAL(
        add(MIN_INT /* -9223372036854775807 */, MAX_INT /* 9223372036854775807 */),
        0x0000000000000000LU /* 0 */
    );
}

static void test_add_minus_max_int_to_minus_max_int() {
    CU_ASSERT_EQUAL(
        add(MIN_INT /* -9223372036854775807 */, MIN_INT /* -9223372036854775807 */),
        0x0000000000000001LU /* 1 */
    );
}

CU_pSuite initialize_arithmetics_int_test_suite() {
    CU_pSuite suite = CU_add_suite("Arithmetics int", NULL, NULL);
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
