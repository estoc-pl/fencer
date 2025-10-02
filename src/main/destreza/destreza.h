#ifndef FENCER_DESTREZA_H
#define FENCER_DESTREZA_H

#include <stdint.h>

#include "../core/errors.h"
#include "destreza_version.h"

typedef struct {
    DestrezaVersion version;

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

Destreza *load_destreza(FencerError **error);

void free_destreza(Destreza *destreza);

#endif //FENCER_DESTREZA_H
