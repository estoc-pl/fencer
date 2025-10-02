#include "int.h"

FENCER_COMMAND(int_push) {
    if (length_left < 8) {
        *error = init_invalid_command_size_error(8, length_left);
        return -1;
    }

    uint64_t result = 0;
    for (int i = 0; i < 8; i++) {
        result = result << 8 | (uint64_t) data[i];
    }

    exec_stack_push_frame(exec_stack, result, destreza->types.int_type, error);

    return 8;
}
