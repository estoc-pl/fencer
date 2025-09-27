#include "destreza_errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./destreza_version.h"

#define DESTREZA_MAJOR_VERSION_MISMATCH_ERROR "Cannot parse Destreza config with major version (%d.%d) higher than supported (%d.%d)"

FencerError *init_destreza_major_version_mismatch_error(DestrezaVersion parsed_version) {
    char *message = calloc(strlen(DESTREZA_MAJOR_VERSION_MISMATCH_ERROR) - 4 * 2 + 4 * 5 + 1, sizeof(char));
    if (!message) {
        return NULL;
    }

    sprintf(
        message,
        DESTREZA_MAJOR_VERSION_MISMATCH_ERROR,
        parsed_version.major, parsed_version.minor,
        SUPPORTED_VERSION.major, SUPPORTED_VERSION.minor
    );

    return init_fencer_error(message, true);
}
