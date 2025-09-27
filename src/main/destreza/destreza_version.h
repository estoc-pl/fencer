#ifndef FENCER_DESTREZA_VERSION_H
#define FENCER_DESTREZA_VERSION_H

#include <stdint.h>

/*
 * Minor version update:
 * - command/type code was changed;
 * - command/type was deleted.
 * Major version update:
 * - new command/type was added;
 * - command/type was renamed/moved;
 * - command/type code format was changed.
 */

typedef struct {
    uint16_t major;
    uint16_t minor;
} DestrezaVersion;

extern const DestrezaVersion SUPPORTED_VERSION;

#endif //FENCER_DESTREZA_VERSION_H
