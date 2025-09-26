#ifndef FENCER_EXEC_STACK_H
#define FENCER_EXEC_STACK_H

#include <stdint.h>

#define WORD uint64_t
#define WORD_TYPE uint8_t
#define BLOCK_SIZE 908

typedef struct StackBlock {
    WORD frames[BLOCK_SIZE];
    WORD_TYPE types[BLOCK_SIZE];
    uint64_t sp;
    struct StackBlock *prev_block;
} StackBlock;

typedef struct {
    StackBlock *active_block;
} ExecStack;

ExecStack *init_stack();

void free_stack(ExecStack *stack);

#endif //FENCER_EXEC_STACK_H
