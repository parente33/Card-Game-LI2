#ifndef GUIAO2_H
#define GUIAO2_H

#include <wchar.h>

/**
 * @brief Compara duas linhas de cartas com base na carta mais alta de cada linha
 * @param a Ponteiro para a primeira linha
 * @param b Ponterio para a segunda linha
 * @return -1 se a carta mais alta de 'a' for menor do que a de 'b'
 *         1 se a carta mais alta de 'a' for maior do que a de 'b'
 *         0 se as duas cartas mais altas forem iguais
 * @note Para cada linha:
 *          - As cartas são ordenadas por ordem crescente (de valor e naipe)
 *          - A carta mais alta (última) é identificada
 *          - As comparações são feitas primeiro pelo valor, e em caso de empate, pelo naipe 
*/
int comparaPrimeiraCarta(const void *a, const void *b);

/**
 * @brief Verifica se duas jogadas diferentes são o mesmo tipo de combinação
 * @param linha Array bidimensional com as jogadas
 * @param tamanho Número de linhas no array
 * @return 1 se são combinações do mesmo tipo e tamanho, 0 se não
*/
int combinacoesIguais(wchar_t linha[][56], int tamanho);

/**
 * @brief Processa conjuntos de jogadas e verifica se todas as combinações em cada teste são iguais
 * @param cartas Array tridimensional com o teste, e as combinações de cartas, 
 * @param num_t Número total de testes a serem processados
 * @param num_testes Array com o número de combinações para cada teste
 * @return A função imprime, para cada teste:
 *         - Se forem combinações iguais, cada combinação é imprimida (ordenadas)
 *         - Se não forem, imprime-se "Combinações não iguais!"
*/
void processar1(wchar_t cartas[][56][56], int num_t, int *num_testes);

#endif // GUIAO2_H