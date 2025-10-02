#include "code_space.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./code_space_errors.h"

bool read_version(CodeSpace *code_space, FILE *exec_file, FencerError **error);

bool verify_executable_version(const CodeSpace *code_space, DestrezaVersion destreza_version, FencerError **error);

bool read_data(CodeSpace *code_space, FILE *exec_file, FencerError **error);

CodeSpace *init_code_space(const char *exec_file_path, const DestrezaVersion destreza_version, FencerError **error) {
    FILE *exec_file = fopen(exec_file_path, "rb");
    if (exec_file == NULL) {
        *error = init_executable_file_not_found_error(exec_file_path);
        return NULL;
    }

    CodeSpace *code_space = calloc(1, sizeof(CodeSpace));
    if (!code_space) {
        fclose(exec_file);
        *error = init_fencer_error(UNKNOWN_CODE_SPACE_LOAD_ERROR, false);
        return NULL;
    }

    if (
        !read_version(code_space, exec_file, error) ||
        !verify_executable_version(code_space, destreza_version, error) ||
        !read_data(code_space, exec_file, error)
    ) {
        free_code_space(code_space);
        fclose(exec_file);
        return NULL;
    }

    fclose(exec_file);

    return code_space;
}

void code_space_read_next_instruction(
    const CodeSpace *code_space,
    uint16_t *code,
    uint8_t **data,
    uint64_t *length_left,
    FencerError **error
) {
    if (!code_space) {
        return;
    }

    const uint64_t current_length_left = code_space->size - code_space->ip;
    if (current_length_left >= 2) {
        *code = (uint16_t) code_space->data[code_space->ip] << 8 | code_space->data[code_space->ip + 1];
        *data = &code_space->data[code_space->ip + 2];
        *length_left = current_length_left - 2;
    } else {
        *error = init_fencer_error(EXECUTABLE_FORMAT_IS_MALFORMED_ERROR, false);
    }
}

void code_space_shift_ip(CodeSpace *code_space, const int64_t offset) {
    if (!code_space) {
        return;
    }

    code_space->ip = code_space->ip + offset;
}

bool read_version(CodeSpace *code_space, FILE *exec_file, FencerError **error) {
    uint8_t version_buffer[4];
    const size_t num_of_read = fread(version_buffer, 1, 4, exec_file);
    if (num_of_read != 4) {
        *error = init_fencer_error(EXECUTABLE_FORMAT_IS_MALFORMED_ERROR, false);
        return false;
    }

    code_space->version.major = (uint16_t) version_buffer[0] << 8 | (uint16_t) version_buffer[1];
    code_space->version.minor = (uint16_t) version_buffer[2] << 8 | (uint16_t) version_buffer[3];

    return true;
}

bool verify_executable_version(
    const CodeSpace *code_space,
    const DestrezaVersion destreza_version,
    FencerError **error
) {
    if (code_space->version.major != destreza_version.major || code_space->version.minor != destreza_version.minor) {
        *error = init_executable_destreza_version_mismatch_error(destreza_version, code_space->version);
        return false;
    }
    return true;
}

bool read_data(CodeSpace *code_space, FILE *exec_file, FencerError **error) {
    fseek(exec_file, 0, SEEK_END);
    const long data_size = ftell(exec_file) - 4;
    if (data_size < 0) {
        *error = init_fencer_error(UNKNOWN_CODE_SPACE_LOAD_ERROR, false);
        return false;
    }

    uint8_t *data = malloc(data_size);
    if (!data) {
        *error = init_fencer_error(UNKNOWN_CODE_SPACE_LOAD_ERROR, false);
        return false;
    }
    fseek(exec_file, 4, SEEK_SET);
    const size_t num_of_read = fread(data, 1, data_size, exec_file);
    if (num_of_read != data_size) {
        *error = init_fencer_error(UNKNOWN_CODE_SPACE_LOAD_ERROR, false);
        return false;
    }

    code_space->data = data;
    code_space->size = data_size;

    return true;
}

void free_code_space(CodeSpace *code_space) {
    if (code_space) {
        if (code_space->data) {
            free(code_space->data);
        }
        free(code_space);
    }
}
