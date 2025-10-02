#include "executor.h"

#include <stdio.h>
#include <stdlib.h>

#include "exec_stack.h"
#include "commands/int.h"
#include "commands/arithmetic.h"

#define IF_CODE(destreza_code) if (destreza_code == code)
#define THEN_COMMAND(command_name) { bytes_read = command_name(destreza, data, length_left, exec_stack, error); }

int64_t execute_command(
    const Destreza *destreza,
    uint16_t code,
    const uint8_t *data,
    uint64_t length_left,
    ExecStack *exec_stack,
    FencerError **error
);

void execute_code_space(CodeSpace *code_space, const Destreza *destreza, FencerError **error) {
    ExecStack *exec_stack = init_stack(error);
    if (*error != NULL) {
        return;
    }

    while (code_space->ip < code_space->size) {
        uint16_t code;
        uint8_t *data = NULL;
        uint64_t length_left;
        code_space_read_next_instruction(code_space, &code, &data, &length_left, error);
        if (*error != NULL) {
            return;
        }

        const int64_t bytes_read = execute_command(destreza, code, data, length_left, exec_stack, error);
        if (*error != NULL) {
            return;
        }

        code_space_shift_ip(code_space, 2 + bytes_read);
    }

    exec_stack_print_dump(exec_stack);
}

int64_t execute_command(
    const Destreza *destreza,
    const uint16_t code,
    const uint8_t *data,
    const uint64_t length_left,
    ExecStack *exec_stack,
    FencerError **error
) {
    int64_t bytes_read = 0;

    IF_CODE(destreza->commands.int_commands.push) THEN_COMMAND(int_push)
    IF_CODE(destreza->commands.arithmetic.add) THEN_COMMAND(arithmetic_add)
    IF_CODE(destreza->commands.arithmetic.subtract) THEN_COMMAND(arithmetic_subtract)
    IF_CODE(destreza->commands.arithmetic.negate) THEN_COMMAND(arithmetic_negate)
    IF_CODE(destreza->commands.arithmetic.multiply) THEN_COMMAND(arithmetic_multiply)
    IF_CODE(destreza->commands.arithmetic.divide) THEN_COMMAND(arithmetic_divide)

    return bytes_read;
}
