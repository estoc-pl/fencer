#ifndef FENCER_DESTREZA_ERRORS_H
#define FENCER_DESTREZA_ERRORS_H

#include "../core/errors.h"
#include "./destreza_version.h"

#define UNKNOWN_DESTREZA_LOAD_ERROR "An unexpected error occurred while loading Destreza config"
#define DESTREZA_FORMAT_IS_MALFORMED_ERROR "Cannot read Destreza config: format is malformed"

FencerError *init_destreza_major_version_mismatch_error(DestrezaVersion parsed_version);

#endif //FENCER_DESTREZA_ERRORS_H
