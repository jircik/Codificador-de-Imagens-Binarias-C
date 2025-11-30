/**
* @file image.h
 * @brief Definição da estrutura de dados para imagens e gerenciamento de memória.
 *
 * Este arquivo define a "classe" Image, utilizando alocação dinâmica e
 * ponteiros de ponteiros para permitir a criação de imagens de qualquer dimensão,
 * superando as limitações da memória Stack.
 */

#ifndef IMAGE_H
#define IMAGE_H

// Constantes que definem a representação textual dos pixels
#define PIXEL_BRANCO 'B'
#define PIXEL_PRETO  'P'
#define CODE_DIVISAO 'X'

/**
 * @brief Estrutura que representa uma imagem binária na memória.
 */
typedef struct {
    int width;      ///< Largura da imagem (número de colunas).
    int height;     ///< Altura da imagem (número de linhas).
    char **pixels;  ///< Matriz bidimensional dinâmica (acessada como pixels[y][x]).
} Image;

/**
 * @brief Construtor: Aloca e inicializa uma nova imagem.
 *
 * Aloca memória para a estrutura e para a matriz de pixels com base nas dimensões.
 *
 * @param width Largura desejada.
 * @param height Altura desejada.
 * @return Image* Ponteiro para a nova imagem ou NULL em caso de falha de alocação.
 */
Image* create_image(int width, int height);

/**
 * @brief Destrutor: Libera toda a memória alocada por uma imagem.
 *
 * Libera as linhas individuais, o vetor de ponteiros e a própria struct.
 * Deve ser chamada sempre que uma imagem não for mais necessária para evitar memory leaks.
 *
 * @param img Ponteiro para a imagem a ser liberada.
 */
void free_image(Image *img);

#endif // IMAGE_H