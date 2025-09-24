#include "exec_stack.h"

#include <stdbool.h>
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

void push_frame(ExecStack *stack, const WORD frame, const WORD_TYPE type) {
    if (!stack) {
        return;
    }

    if (stack->active_block->sp == BLOCK_SIZE) {
        StackBlock *new_block = init_block();
        if (!new_block) {
            return;
        }
        new_block->prev_block = stack->active_block;
        stack->active_block = new_block;
    }

    stack->active_block->frames[stack->active_block->sp] = frame;
    stack->active_block->types[stack->active_block->sp] = type;
    stack->active_block->sp++;
}

bool pop_frame(ExecStack *stack, WORD *target_frame, WORD_TYPE *target_type) {
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

void free_stack(ExecStack *stack) {
    if (stack != NULL) {
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
    if (block != NULL) {
        free(block);
    }
}
