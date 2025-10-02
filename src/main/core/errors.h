#ifndef FENCER_ERROR_H
#define FENCER_ERROR_H

#include <stdbool.h>

typedef struct {
    char *message;
    bool is_message_borrowed;
} FencerError;

FencerError *init_fencer_error(char *message, bool is_message_borrowed);

void fencer_error_print(FencerError *error);

void free_fencer_error(FencerError *error);

#endif //FENCER_ERROR_H
