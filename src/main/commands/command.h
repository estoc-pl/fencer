#ifndef FENCER_COMMAND_H
#define FENCER_COMMAND_H

#include <stdint.h>

#include "../core/errors.h"
#include "../exec_stack.h"
#include "../destreza/destreza.h"

#define FENCER_COMMAND(name) int64_t name( \
    const Destreza *destreza,              \
    const uint8_t *data,                   \
    uint64_t length_left,                  \
    ExecStack *exec_stack,                 \
    FencerError **error                    \
)

FencerError *init_invalid_command_size_error(uint64_t expected, uint64_t actual);

FencerError *init_unsupported_operand_type_error(uint8_t type);

#endif //FENCER_COMMAND_H
