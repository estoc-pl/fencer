#include <cargs.h>

#include "errors.h"
#include "destreza/destreza.h"
#include "code_space/code_space.h"

static cag_option cli_options[] = {
    {
        .identifier = 'h',
        .access_letters = "h",
        .access_name = "help",
        .description = "Displays this help message"
    }
};

void print_help() {
    printf("Usage: fencer [OPTIONS] <exec_file>\n");
    printf("Arguments:\n");
    printf("  exec_file — Path to file containing Destreza byte code to be executed\n");
    printf("Options:\n");
    cag_option_print(cli_options, CAG_ARRAY_SIZE(cli_options), stdout);
}

int main(const int argc, char *argv[]) {
    cag_option_context context;
    cag_option_init(&context, cli_options, CAG_ARRAY_SIZE(cli_options), argc, argv);
    while (cag_option_fetch(&context)) {
        switch (cag_option_get_identifier(&context)) {
            case 'h':
                print_help();
                return 0;
            default:
                cag_option_print_error(&context, stdout);
                return 1;
        }
    }

    const int param_index = cag_option_get_index(&context);
    if (param_index >= argc) {
        print_help();
        return 1;
    }
    if (param_index < argc - 1) {
        fprintf(stderr, "ERROR: Executing multiple files is not supported yet\n");
        return 1;
    }

    const char *exec_file_path = argv[param_index];

    FencerError *error = NULL;

    const Destreza *destreza = load_destreza(&error);
    if (!destreza) {
        fencer_error_print(error);
        free_fencer_error(error);
        return 1;
    }

    CodeSpace *code_space = init_code_space(exec_file_path, destreza->version, &error);
    if (!code_space) {
        fencer_error_print(error);
        free_fencer_error(error);
        return 1;
    }

    free_fencer_error(error);

    return 0;
}
