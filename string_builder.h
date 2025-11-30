/**
* @file string_builder.h
 * @brief Utilitário para concatenação eficiente de strings (buffer dinâmico).
 *
 * Resolve o problema de performance do strcat (complexidade quadrática) usando
 * um array dinâmico com crescimento geométrico. Essencial para imagens grandes.
 */

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

/**
 * @brief Estrutura que mantém o estado do buffer de string.
 */
typedef struct {
    char *data;    ///< Ponteiro para os dados brutos (a string).
    int length;    ///< O comprimento atual da string armazenada.
    int capacity;  ///< A capacidade total alocada atualmente (sempre >= length).
} StringBuilder;

/**
 * @brief Cria um novo StringBuilder vazio.
 * @return Ponteiro para o builder inicializado.
 */
StringBuilder* sb_create(void);

/**
 * @brief Adiciona um único caractere ao final do buffer.
 *
 * Se a capacidade for atingida, realoca memória automaticamente (dobra o tamanho).
 * @param sb O builder alvo.
 * @param c O caractere a ser adicionado.
 */
void sb_append_char(StringBuilder *sb, char c);

/**
 * @brief Finaliza a construção e retorna a string resultante.
 *
 * Transfere a propriedade da memória da string para o chamador e libera a struct do builder.
 * @param sb O builder a ser consumido.
 * @return A string final (deve ser liberada com free() pelo usuário).
 */
char* sb_to_string(StringBuilder *sb);

/**
 * @brief Libera o builder e seus dados sem retornar a string (em caso de erro/cancelamento).
 */
void sb_free(StringBuilder *sb);

#endif // STRING_BUILDER_H