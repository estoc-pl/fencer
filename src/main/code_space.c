#include "code_space.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool read_version(CodeSpace *code_space, FILE *exec_file);

bool verify_version(const CodeSpace *code_space, Version destreza_version);

bool read_data(CodeSpace *code_space, FILE *exec_file);

CodeSpace *init_code_space(const char *exec_file_path, const Version destreza_version) {
    FILE *exec_file = fopen(exec_file_path, "rb");
    if (exec_file == NULL) {
        fprintf(stderr, "ERROR: Executable file could not be found at the specified path: %s\n", exec_file_path);
        return NULL;
    }

    CodeSpace *code_space = calloc(1, sizeof(CodeSpace));

    if (
        code_space &&
        read_version(code_space, exec_file) &&
        verify_version(code_space, destreza_version) &&
        read_data(code_space, exec_file)
    ) {
        fclose(exec_file);
        return code_space;
    }

    free_code_space(code_space);
    fclose(exec_file);

    return NULL;
}

void code_space_read_next_instruction(const CodeSpace *code_space, uint16_t *code, uint8_t *data) {
    *code = (uint16_t) code_space->data[code_space->ip] << 8 | code_space->data[code_space->ip + 1];
    *data = code_space->data[code_space->ip + 2];
}

void code_space_shift_ip(CodeSpace *code_space, const int64_t offset) {
    code_space->ip = code_space->ip + offset;
}

bool read_version(CodeSpace *code_space, FILE *exec_file) {
    uint8_t version_buffer[4];
    const size_t num_of_read = fread(version_buffer, 1, 4, exec_file);
    if (num_of_read != 4) {
        fprintf(stderr, "ERROR: Cannot read executable file: format is malformed\n");
        return false;
    }
    code_space->version.major = (uint16_t) version_buffer[0] << 8 | (uint16_t) version_buffer[1];
    code_space->version.minor = (uint16_t) version_buffer[2] << 8 | (uint16_t) version_buffer[3];
    return true;
}

bool verify_version(const CodeSpace *code_space, const Version destreza_version) {
    if (code_space->version.major != destreza_version.major || code_space->version.minor != destreza_version.minor) {
        fprintf(
            stderr,
            "ERROR: Cannot execute file: Destreza version (%d.%d) is different from version specified in config (%d.%d)\n",
            code_space->version.major, code_space->version.minor,
            destreza_version.major, destreza_version.minor
        );
        return false;
    }
    return true;
}

bool read_data(CodeSpace *code_space, FILE *exec_file) {
    fseek(exec_file, 0, SEEK_END);
    const long data_size = ftell(exec_file) - 4;

    uint8_t *data = malloc(data_size);
    if (!data) {
        return false;
    }
    fseek(exec_file, 4, SEEK_SET);
    const size_t num_of_read = fread(data, 1, data_size, exec_file);
    if (num_of_read != data_size) {
        fprintf(stderr, "ERROR: An unexpected error occurred while loading executable file\n");
    }

    code_space->data = data;
    code_space->size = data_size;

    return true;
}

void free_code_space(CodeSpace *code_space) {
    if (code_space != NULL) {
        if (code_space->data != NULL) {
            free(code_space->data);
        }
        free(code_space);
    }
}
