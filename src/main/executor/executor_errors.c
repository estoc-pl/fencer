#include "executor_errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNKNOWN_COMMAND_CODE_ERROR "Unknown command code: %d"

FencerError *init_unknown_command_code_error(const uint16_t code) {
    char *message = calloc(strlen(UNKNOWN_COMMAND_CODE_ERROR) - 1 * 2 + 1 * 5 + 1, sizeof(char));
    if (!message) {
        return NULL;
    }

    sprintf(message, UNKNOWN_COMMAND_CODE_ERROR, code);

    return init_fencer_error(message, true);
}
