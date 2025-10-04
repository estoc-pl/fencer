#include "io.h"

#include <stdio.h>
#include <stdlib.h>

FENCER_COMMAND(io_print) {
    uint64_t value;
    uint8_t value_type;
    exec_stack_pop_frame(exec_stack, &value, &value_type, error);
    if (*error != NULL) {
        return -1;
    }

    if (value_type != destreza->types.int_type) {
        *error = init_unsupported_operand_type_error(value_type);
        return -1;
    }

    printf("%llu", value);

    return 0;
}
