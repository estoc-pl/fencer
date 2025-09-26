#ifndef FENCER_EXEC_STACK_H
#define FENCER_EXEC_STACK_H

#include <stdbool.h>
#include <stdint.h>

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

ExecStack *init_stack();

void exec_stack_push_frame(ExecStack *stack, WORD frame, WORD_TYPE type);

bool exec_stack_pop_frame(ExecStack *stack, WORD *target_frame, WORD_TYPE *target_type);

void exec_stack_print_dump(const ExecStack *stack);

void free_stack(ExecStack *stack);

#endif //FENCER_EXEC_STACK_H
