/**
* @file reader.h
 * @brief Interface para leitura de imagens (Arquivo ou Teclado).
 */

#ifndef READER_H
#define READER_H

#include "image.h"

/**
 * @brief Lê um arquivo PBM (formato P1) e cria uma estrutura Image.
 *
 * @param filename Caminho do arquivo a ser lido.
 * @return Image* Ponteiro para a imagem criada ou NULL em caso de erro.
 */
Image* read_pbm(const char *filename);

/**
 * @brief Solicita dados da imagem interativamente via console.
 *
 * @return Image* Ponteiro para a imagem criada ou NULL em caso de erro.
 */
Image* read_manual(void);

#endif // READER_H