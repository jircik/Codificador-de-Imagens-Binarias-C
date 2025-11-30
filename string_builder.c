/**
* @file string_builder.c
 * @brief Implementação da lógica de crescimento dinâmico do buffer.
 */

#include <stdlib.h>
#include "string_builder.h"

#define INITIAL_CAPACITY 64 // Tamanho inicial pequeno para eficiência

StringBuilder* sb_create(void) {
    StringBuilder *sb = (StringBuilder*) malloc(sizeof(StringBuilder));
    sb->data = (char*) malloc(INITIAL_CAPACITY * sizeof(char));
    sb->data[0] = '\0'; // Inicializa como string vazia válida
    sb->length = 0;
    sb->capacity = INITIAL_CAPACITY;
    return sb;
}

// Função estática (privada): Garante que há espaço suficiente no buffer
static void sb_resize(StringBuilder *sb, int needed_capacity) {
    if (needed_capacity >= sb->capacity) {
        // Estratégia de crescimento geométrico: Dobrar a capacidade.
        // Isso transforma a operação de adicionar caracteres de O(N) para O(1) amortizado.
        while (needed_capacity >= sb->capacity) {
            sb->capacity *= 2;
        }
        // realloc pode mover o bloco de memória para um novo endereço se necessário
        sb->data = (char*) realloc(sb->data, sb->capacity * sizeof(char));
    }
}

void sb_append_char(StringBuilder *sb, char c) {
    // Garante espaço para o novo char + o terminador nulo
    sb_resize(sb, sb->length + 2);

    sb->data[sb->length] = c;       // Escreve o char
    sb->length++;                   // Atualiza o contador
    sb->data[sb->length] = '\0';    // Mantém a string sempre terminada com nulo
}

char* sb_to_string(StringBuilder *sb) {
    char *result = sb->data; // "Rouba" o ponteiro de dados para retornar
    free(sb); // Libera apenas a casca (a struct de controle)
    return result;
}

void sb_free(StringBuilder *sb) {
    if (sb) {
        free(sb->data);
        free(sb);
    }
}