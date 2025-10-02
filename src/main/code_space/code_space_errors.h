#ifndef FENCER_CODE_SPACE_ERRORS_H
#define FENCER_CODE_SPACE_ERRORS_H

#include "../core/errors.h"
#include "../destreza/destreza_version.h"

#define UNKNOWN_CODE_SPACE_LOAD_ERROR "An unexpected error occurred while loading executable file"
#define EXECUTABLE_FORMAT_IS_MALFORMED_ERROR "Cannot read executable file: format is malformed"

FencerError *init_executable_file_not_found_error(const char *exec_file_path);

FencerError *init_executable_destreza_version_mismatch_error(
    DestrezaVersion destreza_version,
    DestrezaVersion executable_version
);

#endif //FENCER_CODE_SPACE_ERRORS_H
