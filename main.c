/**
* @file main.c
 * @brief Ponto de entrada do programa (Versão Moderna/Otimizada).
 *
 * Orquestra a CLI, leitura, processamento e limpeza de memória.
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "reader.h"
#include "encoder.h"
#include "cli.h"

int main(int argc, char *argv[]) {
    // 1. Parsing: Obter configuração a partir dos argumentos
    AppConfig config = parse_args(argc, argv);

    Image *img = NULL;

    // 2. Execução: Decidir ação com base na configuração
    switch (config.mode) {
        case MODE_HELP:
            print_help();
            return 0; // Saída limpa (sucesso)

        case MODE_MANUAL:
            img = read_manual();
            break;

        case MODE_FILE:
            img = read_pbm(config.filepath);
            break;

        case MODE_UNKNOWN:
        default:
            print_help();
            return 1; // Saída de erro
    }

    // 3. Validação Central: Se falhou ao carregar a imagem, aborta.
    if (!img) {
        // Os erros detalhados já foram impressos pelas funções de leitura
        return 1;
    }

    // 4. Processamento: Codificação
    char *result = encode_image(img);

    // 5. Saída
    printf("Resultado: %s\n", result);

    // 6. Limpeza de Memória (Memory Safety)
    // Em C moderno, somos responsáveis por liberar o que alocamos.
    free(result);     // Libera a string do código
    free_image(img);  // Libera a matriz e a struct da imagem

    return 0;
}