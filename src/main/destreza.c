#include "destreza.h"

#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

const Version SUPPORTED_VERSION = {.major = 0, .minor = 0};

void parse_version(Destreza *destreza, const json_object *root);

void parse_commands(Destreza *destreza, const json_object *root);

uint16_t parse_command_code(json_object *json);

void parse_int_commands(Destreza *destreza, const json_object *commands);

void parse_arithmetic_commands(Destreza *destreza, const json_object *commands);

void parse_types(Destreza *destreza, const json_object *root);

uint8_t parse_type_code(json_object *json);

Destreza *load_destreza() {
    json_object *root = json_object_from_file("resources/destreza.json");
    if (!root) {
        return NULL;
    }

    Destreza *destreza = calloc(1, sizeof(Destreza));
    if (!destreza) {
        json_object_put(root);
        return NULL;
    }

    parse_version(destreza, root);

    if (destreza->version.major != SUPPORTED_VERSION.major) {
        fprintf(
            stderr,
            "ERROR: Cannot parse Destreza config with major version (%d.%d) higher than supported (%d.%d)\n",
            destreza->version.major, destreza->version.minor,
            SUPPORTED_VERSION.major, SUPPORTED_VERSION.minor
        );
        free_destreza(destreza);
        return NULL;
    }
    if (destreza->version.minor != SUPPORTED_VERSION.minor) {
        fprintf(
            stderr,
            "WARNING: Destreza config's minor version (%d.%d) is higher than supported (%d.%d)\n",
            destreza->version.major, destreza->version.minor,
            SUPPORTED_VERSION.major, SUPPORTED_VERSION.minor
        );
    }

    parse_commands(destreza, root);
    parse_types(destreza, root);

    json_object_put(root);

    return destreza;
}

void parse_version(Destreza *destreza, const json_object *root) {
    if (!destreza) {
        return;
    }

    json_object *version_object = NULL;
    json_object_object_get_ex(root, "version", &version_object);

    const char *version = json_object_get_string(version_object);

    char *version_copy = strdup(version);
    const char *major = strtok(version_copy, ".");
    const char *minor = strtok(NULL, ".");

    destreza->version.major = strtol(major, NULL, 10);
    destreza->version.minor = strtol(minor, NULL, 10);

    free(version_copy);
}

void parse_commands(Destreza *destreza, const json_object *root) {
    json_object *commands = NULL;
    json_object_object_get_ex(root, "commands", &commands);

    parse_int_commands(destreza, commands);
    parse_arithmetic_commands(destreza, commands);
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
    if (!destreza || !commands) {
        return;
    }

    json_object *int_commands = NULL, *push = NULL;
    json_object_object_get_ex(commands, "int", &int_commands);
    if (!int_commands) {
        return;
    }

    json_object_object_get_ex(int_commands, "push", &push);

    destreza->commands.int_commands.push = parse_command_code(push);
}

void parse_arithmetic_commands(Destreza *destreza, const json_object *commands) {
    if (!destreza || !commands) {
        return;
    }

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
    if (destreza != NULL) {
        free(destreza);
    }
}
