/**
* @file cli.c
 * @brief Implementação do parsing de argumentos da CLI.
 */

#include <stdio.h>
#include <string.h>
#include "cli.h"

void print_help(void) {
    printf("Uso: ImageEncoder [OPCOES]\n");
    printf("  -?, --help        : Mostra esta ajuda.\n");
    printf("  -m, --manual      : Modo de entrada manual (teclado).\n");
    printf("  -f, --file <ARQ>  : Ler imagem de um arquivo PBM.\n");
}

AppConfig parse_args(int argc, char *argv[]) {
    // Inicialização padrão (estado inválido)
    AppConfig config = { .mode = MODE_UNKNOWN, .filepath = NULL };

    // Se não houver argumentos suficientes, assume ajuda
    if (argc < 2) {
        config.mode = MODE_HELP;
        return config;
    }

    const char *flag = argv[1];

    // Verifica flags de ajuda
    if (strcmp(flag, "-?") == 0 || strcmp(flag, "--help") == 0) {
        config.mode = MODE_HELP;
    }
    // Verifica flags de modo manual
    else if (strcmp(flag, "-m") == 0 || strcmp(flag, "--manual") == 0) {
        config.mode = MODE_MANUAL;
    }
    // Verifica flags de modo arquivo
    else if (strcmp(flag, "-f") == 0 || strcmp(flag, "--file") == 0) {
        // Validação extra: O modo arquivo exige um segundo parâmetro (o nome do arquivo)
        if (argc >= 3) {
            config.mode = MODE_FILE;
            config.filepath = argv[2]; // Captura o argumento do arquivo
        } else {
            fprintf(stderr, "Erro: A opcao -f requer um nome de arquivo.\n");
            config.mode = MODE_UNKNOWN;
        }
    }

    return config;
}