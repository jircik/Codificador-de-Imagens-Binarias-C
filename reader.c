/**
 * @file reader.c
 * @brief Implementação do parser PBM e leitura manual.
 *
 * Contém as funções responsáveis por ler dados de imagem, seja de arquivos
 * no formato PBM (Portable Bitmap) ou diretamente da entrada padrão (teclado).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "reader.h"

/**
 * @brief Função auxiliar (estática) para ignorar comentários e espaços.
 *
 * Avança o cursor do arquivo ignorando qualquer espaço em branco ou
 * linhas de comentário (que começam com '#') até encontrar um dado útil.
 *
 * @param fp Ponteiro para o arquivo aberto.
 */
static void skip_comments(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        // 1. Se for espaço em branco, ignora e continua
        if (isspace(c)) {
            continue;
        }

        // 2. Se for comentário, consome até o fim da linha
        if (c == '#') {
            while ((c = fgetc(fp)) != '\n' && c != EOF);
            continue; // Volta ao loop principal para checar a próxima linha
        }

        // 3. Se não é espaço nem comentário, é um dado útil (ex: um dígito).
        // Devolve o caractere para o fluxo (ungetc) para ser lido corretamente pelo fscanf.
        ungetc(c, fp);
        break; // Sai do loop e retorna o controle para a função de leitura
    }
}

/**
 * @brief Lê uma imagem de um arquivo PBM.
 *
 * @param filename Caminho do arquivo.
 * @return Image* Ponteiro para a nova imagem ou NULL se houver erro.
 */
Image* read_pbm(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo"); // Imprime o erro do sistema (ex: arquivo não encontrado)
        return NULL;
    }

    // 1. Validação do Header PBM (Magic Number)
    char magic[4];
    if (fscanf(fp, "%s", magic) != 1 || strcmp(magic, "P1") != 0) {
        fprintf(stderr, "Formato invalido: Esperado P1\n");
        fclose(fp);
        return NULL;
    }

    // Prepara para ler as dimensões (pula comentários entre o P1 e a largura)
    skip_comments(fp);

    // 2. Leitura das Dimensões
    int w, h;
    if (fscanf(fp, "%d %d", &w, &h) != 2) {
        fprintf(stderr, "Erro ao ler dimensoes da imagem.\n");
        fclose(fp);
        return NULL;
    }

    // 3. Criação da Imagem (Alocação Dinâmica)
    Image *img = create_image(w, h);
    if (!img) {
        // Se a alocação falhar, fecha o arquivo e retorna NULL
        fclose(fp);
        return NULL;
    }

    // 4. Leitura dos Pixels
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int val;
            // Tenta ler o próximo inteiro (fscanf pula espaços automaticamente)
            if (fscanf(fp, "%d", &val) != 1) {
                fprintf(stderr, "Erro ao ler dados da imagem (arquivo incompleto?).\n");
                free_image(img); // Limpeza de memória antes de sair
                fclose(fp);
                return NULL;
            }
            // Converte 0/1 para as constantes internas
            img->pixels[i][j] = (val == 1) ? PIXEL_PRETO : PIXEL_BRANCO;
        }
    }

    fclose(fp);
    return img;
}

/**
 * @brief Lê uma imagem via entrada manual (teclado).
 *
 * @return Image* Ponteiro para a nova imagem ou NULL se houver erro.
 */
Image* read_manual(void) {
    int w, h;
    printf("Insira a LARGURA e ALTURA da imagem: \n");

    // Validação básica de entrada numérica
    if (scanf("%d %d", &w, &h) != 2) {
        fprintf(stderr, "Entrada de dimensoes invalida.\n");
        // Limpa o buffer caso o usuário tenha digitado letras
        while(getchar() != '\n');
        return NULL;
    }

    // Aloca a imagem com as dimensões informadas
    Image *img = create_image(w, h);
    if (!img) return NULL; // Falha de alocação (ex: falta de memória)

    printf("Digite os pixels (0 ou 1) sequencialmente:\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int val;
            printf("Pixel [%d][%d]: ", i, j);

            // Loop de validação para garantir que o usuário digite um número
            // Se scanf falhar (retornar 0), limpa o buffer e pede de novo
            while (scanf("%d", &val) != 1) {
                printf("Entrada invalida. Digite apenas 0 ou 1: ");
                while(getchar() != '\n'); // Limpa buffer de entrada (flush)
            }

            img->pixels[i][j] = (val == 1) ? PIXEL_PRETO : PIXEL_BRANCO;
        }
    }
    return img;
}