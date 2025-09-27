#include "exec_stack.h"

#include <stdio.h>
#include <stdlib.h>

StackBlock *init_block();

void free_block(StackBlock *block);

ExecStack *init_stack() {
    ExecStack *stack = malloc(sizeof(ExecStack));
    if (!stack) {
        return NULL;
    }

    stack->active_block = init_block();
    if (!stack->active_block) {
        free(stack);
        return NULL;
    }

    return stack;
}

bool exec_stack_push_frame(ExecStack *stack, const WORD frame, const WORD_TYPE type) {
    if (!stack) {
        return false;
    }

    if (stack->active_block->sp == BLOCK_SIZE) {
        StackBlock *new_block = init_block();
        if (!new_block) {
            return false;
        }
        new_block->prev_block = stack->active_block;
        stack->active_block = new_block;
    }

    stack->active_block->frames[stack->active_block->sp] = frame;
    stack->active_block->types[stack->active_block->sp] = type;
    stack->active_block->sp++;

    return true;
}

bool exec_stack_pop_frame(ExecStack *stack, WORD *target_frame, WORD_TYPE *target_type) {
    if (!stack) {
        return false;
    }

    if (stack->active_block->sp == 0) {
        if (!stack->active_block->prev_block) {
            return false;
        }

        StackBlock *old_block = stack->active_block;
        stack->active_block = old_block->prev_block;
        free_block(old_block);
    }

    stack->active_block->sp--;
    if (target_frame) {
        *target_frame = stack->active_block->frames[stack->active_block->sp];
    }
    if (target_type) {
        *target_type = stack->active_block->types[stack->active_block->sp];
    }

    return true;
}

void print_binary(const uint8_t byte) {
    for (uint8_t mask = 0b10000000; mask != 0; mask >>= 1) {
        if (byte & mask) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

void exec_stack_print_dump(const ExecStack *stack) {
    if (!stack) {
        return;
    }

    const StackBlock *current_block = stack->active_block;
    while (current_block) {
        for (int64_t i = current_block->sp - 1; i >= 0; i--) {
            print_binary(current_block->types[i]);
            printf("     ");
            for (int j = 1; j <= 8; j++) {
                print_binary((uint8_t) (current_block->frames[i] >> (64 - j * 8)));
                if (j != 8) {
                    printf(".");
                } else {
                    printf("\n");
                }
            }
        }
        current_block = current_block->prev_block;
    }
}

void free_stack(ExecStack *stack) {
    if (stack) {
        StackBlock *block = stack->active_block;
        while (block) {
            StackBlock *prev_block = block->prev_block;
            free_block(block);
            block = prev_block;
        }
        free(stack);
    }
}

StackBlock *init_block() {
    StackBlock *active_block = calloc(1, sizeof(StackBlock));

    return active_block;
}

void free_block(StackBlock *block) {
    if (block) {
        free(block);
    }
}
