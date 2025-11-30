/**
* @file image.c
 * @brief Implementação das funções de gerenciamento de memória da imagem.
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"

Image* create_image(int width, int height) {
    // 1. Aloca a estrutura principal ("casca" do objeto)
    Image *img = (Image*) malloc(sizeof(Image));
    if (!img) return NULL;

    img->width = width;
    img->height = height;

    // 2. Aloca o array de ponteiros para as linhas (o eixo Y)
    img->pixels = (char**) malloc(height * sizeof(char*));
    if (!img->pixels) {
        free(img); // Falha crítica: libera o que já foi alocado e retorna erro
        return NULL;
    }

    // 3. Aloca cada linha individualmente (o eixo X)
    for (int i = 0; i < height; i++) {
        img->pixels[i] = (char*) malloc(width * sizeof(char));

        // Tratamento de erro robusto: Se a memória acabar no meio do processo (linha 50 de 100)
        if (!img->pixels[i]) {
            // Rollback: Libera todas as linhas anteriores que tiveram sucesso
            for (int j = 0; j < i; j++) free(img->pixels[j]);
            free(img->pixels);
            free(img);
            return NULL;
        }
    }

    return img;
}

void free_image(Image *img) {
    if (!img) return; // Proteção contra free em ponteiro nulo

    // Libera a memória de "dentro para fora"
    if (img->pixels) {
        // 1. Libera cada linha de pixels
        for (int i = 0; i < img->height; i++) {
            if (img->pixels[i]) free(img->pixels[i]);
        }
        // 2. Libera o array de ponteiros de linha
        free(img->pixels);
    }
    // 3. Libera a estrutura principal
    free(img);
}