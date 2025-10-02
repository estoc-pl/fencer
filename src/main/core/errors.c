#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

FencerError *init_fencer_error(char *message, bool is_message_borrowed) {
    FencerError *error = malloc(sizeof(FencerError));
    if (!error) {
        return NULL;
    }

    error->message = message;
    error->is_message_borrowed = is_message_borrowed;

    return error;
}

void fencer_error_print(FencerError *error) {
    if (!error) {
        return;
    }

    fprintf(stderr, "ERROR: %s\n", error->message);
}

void free_fencer_error(FencerError *error) {
    if (error) {
        if (error->is_message_borrowed) {
            free(error->message);
        }
        free(error);
    }
}
