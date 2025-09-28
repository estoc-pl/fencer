#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "core/arithmetics/int.test.h"

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    initialize_arithmetics_int_test_suite();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    const unsigned int failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    return failures == 0 ? 0 : 1;
}
