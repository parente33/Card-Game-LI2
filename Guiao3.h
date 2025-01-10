#ifndef GUIAO3_H
#define GUIAO3_H

/**
 * @brief Remove uma carta da mão do jogador, quando jogada
 * @param mao A mão do jogador, antes de fazer a jogada
 * @param carta A carta a remover
 */
void removerCarta(wchar_t *mao, wchar_t carta);

/**
 * @brief Remove todas as cartas de uma jogada da mão do jogador
 * @param mao A mão do jogador, antes de fazer a jogada
 * @param jogada A jogada a fazer
 */
void removerCartasJogadas(wchar_t *mao, wchar_t *jogada);

/**
 * @brief Verifica se a jogada é válida
 * @param jogadaAtual Jogada a ser verifica
 * @return 1 se é válida, 0 se não
 */
int aMinhaJogadaEValida (wchar_t jogadaAtual[]);

/**
 * @brief Verifica se todas as três jogadas anteriores são "PASSO"
 * @param jogadasAnteriores Jogadas anteriores
 * @param N Número de jogadas feitas
 * @return 1 se foram, 0 se não
 */
int todosPassaram(wchar_t jogadasAnteriores[][56], int N);

/**
 * @brief Verifica se uma jogada é um Rei
 * @param jogada Jogada
 * @return 1 se é, 0 se não
 */
int umRei (wchar_t *jogada);

/**
 * @brief Verifica se uma jogada são dois Reis
 * @param jogada Jogada
 * @return 1 se é, 0 se não
 */
int doisReis (wchar_t *jogada);

/**
 * @brief Verifica se uma jogada são três Reis
 * @param jogada Jogada
 * @return 1 se é, 0 se não
 */
int tresReis (wchar_t *jogada);

/**
 * @brief Valida a jogada, caso um jogador não tenha passado
 * @param jogadasAnteriores Jogadas anteriores
 * @param N Número de jogadas anteriores
 * @param jogadaAtual Jogada que se quer fazer
 * @return 1 se é, 0 se não
 */
int validaJogadaNaoPassou(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]);

/**
 * @brief Valida a jogada, se for jogada uma das exceções de Reis
 * @param jogadasAnteriores Jogadas anteriores
 * @param N Número de jogadas anteriores
 * @param jogadaAtual Jogada que se quer fazer
 * @return 1 se é, 0 se não
 */
int validaJogadaReis(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]);

/**
 * @brief Função geral de validação
 * @param jogadasAnteriores Jogadas anteriores
 * @param N Número de jogadas anteriores
 * @param jogadaAtual Jogada que se quer fazer
 * @return 1 se é, 0 se não
 */
int validaJogada(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]);

/**
 * @brief Função geral de validação
 * @param jogadasAnteriores Jogadas anteriores
 * @param N Número de jogadas anteriores
 * @param jogadaAtual Jogada que se quer fazer
 * @return 1 se é, 0 se não
 */
int validaAJogadaSeTodosPassaram(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]);

/**
 * @brief Processa as jogadas dentro dos testes
 * @param mao Mão do jogador 
 * @param jogadasAnteriores Jogadas anteriores
 * @param N Número de jogadas anteriores
 * @param jogadaAtual Jogada que se quer fazer
 * @param resultado Array onde se armazena os resultados
 */
void processarCasoTeste(wchar_t mao[], wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[], wchar_t resultado[]);

/**
 * @brief Lê a mão do jogador
 * @param mao Mão do jogador
 */
void lerMao(wchar_t mao[]);

/**
 * @brief Lê as jogadas anteriores
 * @param jogadasAnteriores Jogadas Anteriores
 */
void lerJogadasAnteriores(wchar_t jogadasAnteriores[][56], int N);

#endif // GUIAO3_H