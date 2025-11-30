/**
* @file encoder.h
 * @brief Interface de codificação de imagem (Algoritmo Quadtree).
 */

#ifndef ENCODER_H
#define ENCODER_H

#include "image.h"

/**
 * @brief Codifica uma imagem binária em uma string compactada.
 *
 * Utiliza recursão para dividir a imagem em quadrantes homogêneos.
 *
 * @param img A imagem carregada na memória.
 * @return char* String contendo o código (deve ser liberada com free()).
 */
char* encode_image(Image *img);

#endif // ENCODER_H