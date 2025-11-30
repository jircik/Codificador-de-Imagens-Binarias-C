# Codificador de Imagens Binárias 

Este projeto implementa um codificador de imagens binárias (preto e branco). O algoritmo analisa a imagem e a divide recursivamente em quatro quadrantes até que cada sub-região seja uniforme (composta inteiramente por pixels pretos ou brancos) ou atinja o tamanho de um único pixel.

O projeto foi desenvolvido em C, priorizando a **eficiência** e a **segurança de memória** para lidar com imagens de diversas dimensões e tamanhos de saída.

### Características de Implementação

*   **Gerenciamento Dinâmico de Imagem:** A estrutura de dados `Image` utiliza alocação dinâmica de memória, permitindo que o programa processe imagens de qualquer dimensão, superando as limitações de memória *stack* de matrizes estáticas.
*   **Performance Otimizada:** A geração do código de saída é realizada através de um utilitário `StringBuilder` (buffer dinâmico), garantindo que a concatenação da string de código seja executada de forma eficiente, com complexidade de tempo linear, mesmo para imagens que resultam em códigos de saída muito longos.
*   **Código Modular:** O projeto é dividido em módulos claros (`CLI`, `Reader`, `Encoder`, `Image`, `StringBuilder`), facilitando a manutenção e a compreensão.

O código de saída é uma string que representa a estrutura da Quadtree, onde:
*   `P` (Preto) e `B` (Branco) indicam uma região uniforme.
*   `X` (Divisão) indica que a região foi dividida em quatro sub-regiões, seguidas pelos códigos dessas sub-regiões na ordem: Superior Esquerdo, Superior Direito, Inferior Esquerdo e Inferior Direito.

## Funcionalidades

O programa aceita a entrada de dados de duas maneiras:

1.  **Modo Manual:** O usuário insere as dimensões da imagem e, em seguida, os valores de cada pixel (0 para Branco, 1 para Preto) via teclado.
2.  **Modo Arquivo:** O programa lê uma imagem binária a partir de um arquivo no formato **PBM (Portable Bitmap)**, especificamente o formato **P1 (ASCII)**.

## Como Compilar e Executar

O projeto é escrito em C e pode ser compilado com um compilador C padrão, como o GCC.

```bash
# Exemplo de compilação (assumindo que todos os arquivos .c estão no diretório)
gcc -o encoder main.c cli.c encoder.c reader.c image.c string_builder.c
```

### Uso

O programa deve ser executado com argumentos de linha de comando para especificar o modo de operação.

| Modo | Comando | Descrição |
| :--- | :--- | :--- |
| **Ajuda** | `./encoder -h` ou `./encoder --help` | Exibe a mensagem de ajuda. |
| **Manual** | `./encoder -m` ou `./encoder --manual` | Permite a entrada manual dos dados da imagem. |
| **Arquivo** | `./encoder -f <arquivo.pbm>` ou `./encoder --file <arquivo.pbm>` | Lê a imagem do arquivo PBM especificado. |

## Casos de Teste (Exemplos de Uso)

Os seguintes arquivos de teste demonstram a funcionalidade do programa no **Modo Arquivo**.

### 1. Imagem Simples (teste.txt)

Este arquivo representa uma imagem de 6x10 pixels, formando a letra "J".

```
P1
# Comentário: este é um exemplo de imagem da letra "J"
6 10
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 1 0
1 0 0 0 1 0
0 1 1 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```


**Comando de Execução:**

```bash
./encoder -f teste.txt
```

**Resultado Esperado (Exemplo de Saída Codificada):**

O resultado será a string: `XBXXBPBPBXBPBPBXXXBPBBPXBPBBXXBPPBBBB` 

## Estrutura do Projeto

| Arquivo | Descrição |
| :--- | :--- |
| `main.c` | Ponto de entrada principal. Orquestra o fluxo do programa, incluindo a crucial **limpeza de memória** após a codificação. |
| `cli.c`/`cli.h` | Módulo de Interface de Linha de Comando (CLI). Responsável por analisar argumentos e definir o modo de operação. |
| `reader.c`/`reader.h` | Módulo de Leitura. Contém funções para ler dados de imagem via entrada manual e de arquivos PBM, construindo a estrutura `Image`. |
| `encoder.c`/`encoder.h` | Módulo de Codificação. Implementa o algoritmo recursivo de Quadtree, utilizando o `StringBuilder` para a saída. |
| `image.c`/`image.h` | Módulo de Imagem. Define a estrutura `Image` e as funções de gerenciamento de memória (`create_image`, `free_image`) para alocação dinâmica. |
| `string_builder.c`/`string_builder.h` | Módulo de Utilidade. Implementa o `StringBuilder` para concatenação eficiente de strings. |

