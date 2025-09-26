#ifndef FENCER_DESTREZA_H
#define FENCER_DESTREZA_H

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
} Version;

extern const Version SUPPORTED_VERSION;

typedef struct {
    Version version;

    struct {
        struct {
            uint16_t push;
        } int_commands;

        struct {
            uint16_t add;
            uint16_t subtract;
            uint16_t negate;
            uint16_t multiply;
            uint16_t divide;
        } arithmetic;
    } commands;

    struct {
        uint16_t int_type;
    } types;
} Destreza;

Destreza *load_destreza();

void free_destreza(Destreza *destreza);

#endif //FENCER_DESTREZA_H
