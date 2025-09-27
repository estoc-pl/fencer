#ifndef FENCER_CODE_SPACE_H
#define FENCER_CODE_SPACE_H

#include "../errors.h"
#include "../destreza/destreza_version.h"

typedef struct {
    DestrezaVersion version;
    uint64_t size;
    uint8_t *data;
    uint64_t ip;
} CodeSpace;

CodeSpace *init_code_space(const char *exec_file_path, DestrezaVersion destreza_version, FencerError **error);

void code_space_read_next_instruction(
    const CodeSpace *code_space,
    uint16_t *code,
    uint8_t **data,
    uint64_t *length_left
);

void code_space_shift_ip(CodeSpace *code_space, int64_t offset);

void free_code_space(CodeSpace *code_space);

#endif //FENCER_CODE_SPACE_H
