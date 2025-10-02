#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_COMMAND_SIZE_ERROR "Invalid command data size: expected %llu, but received %llu"
#define UNSUPPORTED_OPERAND_TYPE_ERROR "Unsupported operand type code: %d"

FencerError *init_invalid_command_size_error(const uint64_t expected, const uint64_t actual) {
    char *message = calloc(strlen(INVALID_COMMAND_SIZE_ERROR) - 2 * 2 + 2 * 20 + 1, sizeof(char));
    if (!message) {
        return NULL;
    }

    sprintf(message, INVALID_COMMAND_SIZE_ERROR, expected, actual);

    return init_fencer_error(message, true);
}

FencerError *init_unsupported_operand_type_error(const uint8_t type) {
    char *message = calloc(strlen(UNSUPPORTED_OPERAND_TYPE_ERROR) - 1 * 2 + 1 * 3 + 1, sizeof(char));
    if (!message) {
        return NULL;
    }

    sprintf(message, UNSUPPORTED_OPERAND_TYPE_ERROR, type);

    return init_fencer_error(message, true);
}
