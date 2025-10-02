#ifndef FENCER_EXEC_STACK_H
#define FENCER_EXEC_STACK_H

#include <stdint.h>

#include "core/errors.h"

#define UNKNOWN_EXEC_STACK_INIT_ERROR "An unexpected error occurred while initializing execution stack"
#define UNKNOWN_EXEC_STACK_INIT_BLOCK_ERROR "An unexpected error occurred while loading execution stack block"
#define EXEC_STACK_EMPTY_ERROR "Internal error: Attempted pop on empty execution stack"

#define WORD uint64_t
#define WORD_TYPE uint8_t
#define BLOCK_SIZE 908

typedef struct StackBlock {
    WORD frames[BLOCK_SIZE];
    WORD_TYPE types[BLOCK_SIZE];
    uint32_t sp;
    struct StackBlock *prev_block;
} StackBlock;

typedef struct {
    StackBlock *active_block;
} ExecStack;

ExecStack *init_stack(FencerError **error);

void exec_stack_push_frame(ExecStack *stack, WORD frame, WORD_TYPE type, FencerError **error);

void exec_stack_pop_frame(ExecStack *stack, WORD *target_frame, WORD_TYPE *target_type, FencerError **error);

void exec_stack_print_dump(const ExecStack *stack);

void free_stack(ExecStack *stack);

#endif //FENCER_EXEC_STACK_H
