/**
* @file cli.h
 * @brief Definição da Interface de Linha de Comando (CLI).
 *
 * Utiliza o padrão "Objeto de Configuração" para desacoplar a lógica de
 * parsing de argumentos da lógica de execução principal.
 */

#ifndef CLI_H
#define CLI_H

// Enumeração para os modos de operação possíveis
typedef enum {
    MODE_UNKNOWN, ///< Modo inválido ou erro de sintaxe
    MODE_HELP,    ///< Solicitação de ajuda (-? ou --help)
    MODE_MANUAL,  ///< Entrada manual via teclado (-m)
    MODE_FILE     ///< Leitura de arquivo PBM (-f)
} RunMode;

/**
 * @brief Estrutura que guarda as configurações de execução.
 *
 * Armazena o modo decidido e, se aplicável, o caminho do arquivo.
 */
typedef struct {
    RunMode mode;
    const char *filepath; ///< Ponteiro para o nome do arquivo (em argv)
} AppConfig;

/**
 * @brief Analisa os argumentos da linha de comando.
 *
 * @param argc Contagem de argumentos.
 * @param argv Vetor de argumentos.
 * @return AppConfig Estrutura preenchida com a decisão de execução.
 */
AppConfig parse_args(int argc, char *argv[]);

/**
 * @brief Imprime as instruções de uso no console.
 */
void print_help(void);

#endif // CLI_H