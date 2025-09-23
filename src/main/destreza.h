#ifndef FENCER_DESTREZA_H
#define FENCER_DESTREZA_H

#include <stdint.h>

typedef struct {
    uint16_t major;
    uint16_t minor;
} Version;

extern const Version SUPPORTED_VERSION;

typedef struct {
    Version version;

    struct {
        uint16_t push_int;

        struct {
            uint16_t call_constructor;
            uint16_t push_vararg_end;
        } function;

        struct {
            uint16_t add;
            uint16_t subtract;
            uint16_t negate;
            uint16_t multiply;
            uint16_t divide;
        } arithmetic;
    } commands;
} Destreza;

Destreza *load_destreza();

void free_destreza(Destreza *destreza);

#endif //FENCER_DESTREZA_H
