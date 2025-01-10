#ifndef GUIAO1_H
#define GUIAO1_H

#include <wchar.h>
#include <stdio.h>

/**
 * @brief Função que verifica o naipe de uma carta
 * @param carta Carácter Unicode (no intervalo U+1F0A0 a U+1F0FF), onde cada naipe ocupa um intervalo de 16 posições
 * @return Índice do naipe da carta (0 para Espadas, 1 para Copas, 2 para Ouros, 3 para Paus)
*/
int naipeCheck(wchar_t carta);

/**
 * @brief Função que verifica o valor de uma carta
 * @param carta Carácter Unicode (no intervalo U+1F0A0 a U+1F0FF), onde cada naipe ocupa um intervalo de 16 posições
 * @return O valor da carta (1 para Ás, 2 a 10 para cartas numeradas, 11 para Valete, 12 para Dama, 13 para Rei)
*/
int valorCheck (wchar_t carta);

/**
 * @brief Função de comparação entre duas cartas
 * @param a Ponteiro para a primeira carta
 * @param b Ponterio para a segunda carta
 * @return -1 se 'a' vem antes de 'b'
 *         1 se 'a' vem depois de 'b'
 *         0 se são a mesma carta
*/
int comparaCartas(const void *a, const void *b);

/**
 * @brief Função que verifica se uma jogada é uma sequência
 * @param cartas Ponteiro para as cartas da jogada
 * @param tamanho Tamanho da jogada
 * @return 1 se é sequência, 0 se não é
 * @note Uma sequência é uma jogada composta por três ou mais cartas de valores consecutivos 
 *       (não necessariamente todas do mesmo naipe)
*/
int verificaSequencia(wchar_t *cartas, int tamanho);

/**
 * @brief Função que verifica se uma jogada é uma dupla sequência
 * @param cartas Ponteiro para as cartas da jogada
 * @param tamanho Tamanho da jogada
 * @return 1 se é dupla sequência, 0 se não é
 * @note Uma dupla sequência é uma jogada composta por três ou mais pares de valores consecutivos
*/
int verificaDuplaSequencia(wchar_t *cartas, int tamanho);

/**
 * @brief Função que verifica se uma jogada é um conjunto
 * @param cartas Ponteiro para as cartas da jogada
 * @param tamanho Tamanho da jogada
 * @return 1 se é conjunto, 0 se não é
 * @note Um conjunto é uma jogada composta por uma até quatro cartas todas com o mesmo valor mas de naipes diferentes
*/
int todasIguais(wchar_t *cartas, int tamanho);

/**
 * @brief Processa um conjunto de jogadas
 * @param linha Array Bidimensional de cartas representando as jogadas
 *              Cada linha do array representa uma jogada
 * @param ntestes Número total de linhas presentes no array
 * @return A função imprime, para cada jogada:
 *         - O seu tipo (conjunto, sequência, dupla sequência, ou nada)
 *         - O número de cartas da jogada
 *         - A carta mais alta da jogada
*/
void processar(wchar_t linha[][BUFSIZ], int ntestes);

#endif // GUIAO1_H