/**
 * @file encoder.c
 * @brief Implementação da lógica recursiva de codificação.
 */

#include "encoder.h"
#include "string_builder.h"

// Função auxiliar privada: A "engine" da recursão
static void encode_recursive(Image *img, int r_start, int r_end, int c_start, int c_end, StringBuilder *sb) {

    // Caso base de segurança: Se a região não existe (ex: corte em dimensão 1)
    if (r_start > r_end || c_start > c_end) return;

    // 1. Verificação de Uniformidade
    char first_color = img->pixels[r_start][c_start];
    int is_uniform = 1;

    // Varredura da região para checar se todos os pixels são iguais
    for (int i = r_start; i <= r_end && is_uniform; i++) {
        for (int j = c_start; j <= c_end; j++) {
            if (img->pixels[i][j] != first_color) {
                is_uniform = 0;
                break;
            }
        }
    }

    // 2. Tomada de Decisão
    if (is_uniform) {
        // Regra 1: Se uniforme, adiciona o código da cor (O(1) com StringBuilder)
        sb_append_char(sb, first_color);
    } else {
        // Regra 2: Se misto, adiciona 'X' e divide
        sb_append_char(sb, CODE_DIVISAO);

        int height = r_end - r_start + 1;
        int width = c_end - c_start + 1;

        // Cálculo dos pontos de corte (Divisão inteira empurra o resto para a esquerda/topo)
        int mid_r = r_start + (height + 1) / 2 - 1;
        int mid_c = c_start + (width + 1) / 2 - 1;

        // Chamadas recursivas para os 4 quadrantes
        encode_recursive(img, r_start, mid_r, c_start, mid_c, sb);     // Q1: Sup. Esq
        encode_recursive(img, r_start, mid_r, mid_c + 1, c_end, sb);   // Q2: Sup. Dir
        encode_recursive(img, mid_r + 1, r_end, c_start, mid_c, sb);   // Q3: Inf. Esq
        encode_recursive(img, mid_r + 1, r_end, mid_c + 1, c_end, sb); // Q4: Inf. Dir
    }
}

char* encode_image(Image *img) {
    // Cria o buffer dinâmico otimizado
    StringBuilder *sb = sb_create();

    // Inicia a recursão cobrindo a imagem inteira
    encode_recursive(img, 0, img->height - 1, 0, img->width - 1, sb);

    // Finaliza e retorna a string bruta
    return sb_to_string(sb);
}