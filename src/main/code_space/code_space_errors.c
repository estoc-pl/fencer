#include "code_space_errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXECUTABLE_FILE_NOT_FOUND_ERROR "Executable file could not be found at the specified path: %s"
#define EXECUTABLE_DESTREZA_VERSION_MISMATCH_ERROR "Cannot execute file: Destreza version (%d.%d) is different from version specified in config (%d.%d)"

FencerError *init_executable_file_not_found_error(const char *exec_file_path) {
    char *message = calloc(
        strlen(EXECUTABLE_FILE_NOT_FOUND_ERROR) - 1 * 2 + 1 * strlen(exec_file_path) + 1,
        sizeof(char)
    );
    if (!message) {
        return NULL;
    }

    sprintf(message, EXECUTABLE_FILE_NOT_FOUND_ERROR, exec_file_path);

    return init_fencer_error(message, true);
}

FencerError *init_executable_destreza_version_mismatch_error(
    const DestrezaVersion destreza_version,
    const DestrezaVersion executable_version
) {
    char *message = calloc(strlen(EXECUTABLE_DESTREZA_VERSION_MISMATCH_ERROR) - 4 * 2 + 4 * 5 + 1, sizeof(char));
    if (!message) {
        return NULL;
    }

    sprintf(
        message,
        EXECUTABLE_DESTREZA_VERSION_MISMATCH_ERROR,
        executable_version.major, executable_version.minor,
        destreza_version.major, destreza_version.minor
    );

    return init_fencer_error(message, true);
}
