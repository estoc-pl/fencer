#include "destreza.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#include "destreza_errors.h"

bool parse_version(Destreza *destreza, const json_object *root, FencerError **error);

bool verify_destreza_version(DestrezaVersion parsed_version, FencerError **error);

void parse_commands(Destreza *destreza, const json_object *root);

uint16_t parse_command_code(json_object *json);

void parse_int_commands(Destreza *destreza, const json_object *commands);

void parse_arithmetic_commands(Destreza *destreza, const json_object *commands);

void parse_io_commands(Destreza *destreza, const json_object *commands);

void parse_types(Destreza *destreza, const json_object *root);

uint8_t parse_type_code(json_object *json);

Destreza *load_destreza(FencerError **error) {
    json_object *root = json_object_from_file("resources/destreza.json");
    if (!root) {
        *error = init_fencer_error(UNKNOWN_DESTREZA_LOAD_ERROR, false);
        return NULL;
    }

    Destreza *destreza = calloc(1, sizeof(Destreza));
    if (!destreza) {
        json_object_put(root);
        *error = init_fencer_error(UNKNOWN_DESTREZA_LOAD_ERROR, false);
        return NULL;
    }

    if (!parse_version(destreza, root, error) || !verify_destreza_version(destreza->version, error)) {
        json_object_put(root);
        free_destreza(destreza);
        return NULL;
    }

    parse_commands(destreza, root);
    parse_types(destreza, root);

    json_object_put(root);

    return destreza;
}

bool parse_version(Destreza *destreza, const json_object *root, FencerError **error) {
    json_object *version_object = NULL;
    json_object_object_get_ex(root, "version", &version_object);
    if (!version_object) {
        *error = init_fencer_error(DESTREZA_FORMAT_IS_MALFORMED_ERROR, false);
        return false;
    }

    const char *version = json_object_get_string(version_object);
    if (!version) {
        *error = init_fencer_error(DESTREZA_FORMAT_IS_MALFORMED_ERROR, false);
        return false;
    }

    char *version_copy = strdup(version);
    const char *major = strtok(version_copy, ".");
    const char *minor = strtok(NULL, ".");
    if (!major || !minor) {
        free(version_copy);
        *error = init_fencer_error(DESTREZA_FORMAT_IS_MALFORMED_ERROR, false);
        return false;
    }

    destreza->version.major = strtol(major, NULL, 10);
    destreza->version.minor = strtol(minor, NULL, 10);

    free(version_copy);

    return true;
}

bool verify_destreza_version(const DestrezaVersion parsed_version, FencerError **error) {
    if (parsed_version.major != SUPPORTED_VERSION.major) {
        *error = init_destreza_major_version_mismatch_error(parsed_version);
        return false;
    }
    if (parsed_version.minor != SUPPORTED_VERSION.minor) {
        fprintf(
            stderr,
            "WARNING: Destreza config's minor version (%d.%d) is higher than supported (%d.%d)\n",
            parsed_version.major, parsed_version.minor,
            SUPPORTED_VERSION.major, SUPPORTED_VERSION.minor
        );
    }
    return true;
}

void parse_commands(Destreza *destreza, const json_object *root) {
    json_object *commands = NULL;
    json_object_object_get_ex(root, "commands", &commands);
    if (!commands) {
        return;
    }

    parse_int_commands(destreza, commands);
    parse_arithmetic_commands(destreza, commands);
    parse_io_commands(destreza, commands);
}

void parse_types(Destreza *destreza, const json_object *root) {
    json_object *types = NULL;
    json_object_object_get_ex(root, "types", &types);
    if (!types) {
        return;
    }

    json_object *int_type = NULL;
    json_object_object_get_ex(types, "int", &int_type);

    destreza->types.int_type = parse_type_code(int_type);
}

void parse_int_commands(Destreza *destreza, const json_object *commands) {
    json_object *int_commands = NULL, *push = NULL;
    json_object_object_get_ex(commands, "int", &int_commands);
    if (!int_commands) {
        return;
    }

    json_object_object_get_ex(int_commands, "push", &push);

    destreza->commands.int_commands.push = parse_command_code(push);
}

void parse_arithmetic_commands(Destreza *destreza, const json_object *commands) {
    json_object *arithmetic = NULL, *add = NULL, *subtract = NULL, *negate = NULL, *multiply = NULL, *divide = NULL;
    json_object_object_get_ex(commands, "arithmetic", &arithmetic);
    if (!arithmetic) {
        return;
    }

    json_object_object_get_ex(arithmetic, "add", &add);
    json_object_object_get_ex(arithmetic, "subtract", &subtract);
    json_object_object_get_ex(arithmetic, "negate", &negate);
    json_object_object_get_ex(arithmetic, "multiply", &multiply);
    json_object_object_get_ex(arithmetic, "divide", &divide);

    destreza->commands.arithmetic.add = parse_command_code(add);
    destreza->commands.arithmetic.subtract = parse_command_code(subtract);
    destreza->commands.arithmetic.negate = parse_command_code(negate);
    destreza->commands.arithmetic.multiply = parse_command_code(multiply);
    destreza->commands.arithmetic.divide = parse_command_code(divide);
}

void parse_io_commands(Destreza *destreza, const json_object *commands) {
    json_object *io_commands = NULL, *print = NULL;
    json_object_object_get_ex(commands, "io", &io_commands);
    if (!io_commands) {
        return;
    }

    json_object_object_get_ex(io_commands, "print", &print);

    destreza->commands.io.print = parse_command_code(print);
}

uint16_t parse_command_code(json_object *json) {
    if (!json) {
        return 0;
    }
    const char *str = json_object_get_string(json);
    return strtol(str, NULL, 2);
}

uint8_t parse_type_code(json_object *json) {
    if (!json) {
        return 0;
    }
    const char *str = json_object_get_string(json);
    return strtol(str, NULL, 2);
}

void free_destreza(Destreza *destreza) {
    if (destreza) {
        free(destreza);
    }
}
