#include "arithmetic.h"

#include <stdlib.h>

#include "../core/arithmetics/int.h"

bool load_int_operand(const Destreza *destreza, ExecStack *exec_stack, uint64_t *operand, FencerError **error);

FENCER_COMMAND(arithmetic_add) {
    uint64_t operand1, operand2;

    if (!load_int_operand(destreza, exec_stack, &operand1, error) ||
        !load_int_operand(destreza, exec_stack, &operand2, error)) {
        return -1;
    }

    exec_stack_push_frame(exec_stack, int_add(operand1, operand2), destreza->types.int_type, error);

    return 0;
}

FENCER_COMMAND(arithmetic_subtract) {
    uint64_t operand1, operand2;

    if (!load_int_operand(destreza, exec_stack, &operand1, error) ||
        !load_int_operand(destreza, exec_stack, &operand2, error)) {
        return -1;
    }

    exec_stack_push_frame(exec_stack, int_subtract(operand1, operand2), destreza->types.int_type, error);

    return 0;
}

FENCER_COMMAND(arithmetic_negate) {
    uint64_t operand;

    if (!load_int_operand(destreza, exec_stack, &operand, error)) {
        return -1;
    }

    exec_stack_push_frame(exec_stack, int_negate(operand), destreza->types.int_type, error);

    return 0;
}

FENCER_COMMAND(arithmetic_multiply) {
    uint64_t operand1, operand2;

    if (!load_int_operand(destreza, exec_stack, &operand1, error) ||
        !load_int_operand(destreza, exec_stack, &operand2, error)) {
        return -1;
    }

    exec_stack_push_frame(exec_stack, int_multiply(operand1, operand2), destreza->types.int_type, error);

    return 0;
}

FENCER_COMMAND(arithmetic_divide) {
    uint64_t operand1, operand2;

    if (!load_int_operand(destreza, exec_stack, &operand1, error) ||
        !load_int_operand(destreza, exec_stack, &operand2, error)) {
        return -1;
    }

    const uint64_t result = int_divide(operand1, operand2, error);
    if (*error != NULL) {
        return -1;
    }

    exec_stack_push_frame(exec_stack, result, destreza->types.int_type, error);

    return 0;
}

bool load_int_operand(const Destreza *destreza, ExecStack *exec_stack, uint64_t *operand, FencerError **error) {
    uint8_t operand_type;
    exec_stack_pop_frame(exec_stack, operand, &operand_type, error);
    if (*error != NULL) {
        return false;
    }

    if (operand_type != destreza->types.int_type) {
        *error = init_unsupported_operand_type_error(operand_type);
        return false;
    }

    return true;
}
