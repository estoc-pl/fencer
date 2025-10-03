#ifndef FENCER_EXECUTOR_ERRORS_H
#define FENCER_EXECUTOR_ERRORS_H

#include <stdint.h>

#include "../core/errors.h"

FencerError *init_unknown_command_code_error(uint16_t code);

#endif //FENCER_EXECUTOR_ERRORS_H
