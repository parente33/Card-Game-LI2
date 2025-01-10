#include "Guiao1.h"
#include "Guiao2.h"
#include "Guiao3.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stddef.h>
#include <stdlib.h>

// Remove uma carta da mão do jogador, quando jogada
void removerCarta(wchar_t *mao, wchar_t carta) {
    wchar_t *pos = wcschr(mao, carta);
    qsort(mao, wcslen(mao), sizeof(wchar_t), comparaCartas);
    if (pos != NULL) {
        while (*(pos + 1) != L'\0') {
            *pos = *(pos + 1);
            pos++;
        }
        *pos = L'\0';
    }
}

// Remove todas as cartas de uma jogada da mão do jogador
void removerCartasJogadas(wchar_t *mao, wchar_t *jogada) {
    size_t len = wcslen(jogada);
    for (size_t i = 0; i < len; i++) {
        if (jogada[i] != L' ') {
            removerCarta(mao, jogada[i]);
        }
    }
}

// Verifica se a jogada é válida
int aMinhaJogadaEValida (wchar_t jogadaAtual[]) {
    int r = 0;
    if (verificaSequencia(jogadaAtual, wcslen(jogadaAtual)) ||
        verificaDuplaSequencia(jogadaAtual, wcslen(jogadaAtual)) ||
        todasIguais (jogadaAtual, wcslen(jogadaAtual)) ||
        wcscmp(jogadaAtual, L"PASSO") == 0) {
            r = 1;
    }

    return r;
}

// Verifica se todas as três jogadas anteriores são "PASSO"
int todosPassaram(wchar_t jogadasAnteriores[][56], int N) {
    int r = 1;
    if (N < 3) r = 0;

    for (int i = N - 1; i >= N - 3; i--) {
        if (wcscmp(jogadasAnteriores[i], L"PASSO") != 0) r = 0;
    }

    return r;
}

// Verifica se uma jogada é apenas uma carta do tipo Rei
int umRei (wchar_t *jogada) {
    int r = 0;
    if (wcslen(jogada) == 1) {
        for (int i = 0; i < (int)wcslen(jogada); i++) {
            if (valorCheck(jogada[i]) != 13) break;
        }
        r = 1;
    }   
    return r;
}

// Verifica se uma jogada são duas cartas do tipo Rei
int doisReis(wchar_t *jogada) {
    int r = 0;
    if (wcslen(jogada) == 2) {
        for (int j = 0; j < (int)wcslen(jogada); j++) {
            if (valorCheck(jogada[j]) != 13) break;
        }
        r = 1;
    }
    return r;
}

// Verifica se uma jogada são três cartas do tipo Rei
int tresReis (wchar_t *jogada) {
    int r = 0;
    if (wcslen(jogada) == 3) {
        for (int k = 0; k < (int)wcslen(jogada); k++) {
            if (valorCheck(jogada[k]) != 13) break;
        }
        r = 1;
    }
    return r;
}

// Valida a jogada, caso um jogador não tenha passado
int validaJogadaNaoPassou(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    int r = 0;
    int ultimoNaoPasso = -1;
    for (int i = N - 1; i >= N - 3; i--) {
        if (wcscmp(jogadasAnteriores[i], L"PASSO") != 0) {
            ultimoNaoPasso = i;
            break;
        }
    }

    if (wcscmp(jogadaAtual, L"PASSO") == 0) r = 1;

    if (ultimoNaoPasso != -1 && wcslen(jogadasAnteriores[ultimoNaoPasso]) == wcslen(jogadaAtual)) {
        wchar_t ultimacartaAnterior = jogadasAnteriores[ultimoNaoPasso][wcslen(jogadasAnteriores[ultimoNaoPasso]) - 1];
        wchar_t ultimacartaAtual = jogadaAtual[wcslen(jogadaAtual) - 1];

        if (aMinhaJogadaEValida(jogadaAtual) && valorCheck(ultimacartaAtual) > valorCheck(ultimacartaAnterior)) { 
            r = 1;
        } else if (valorCheck(ultimacartaAtual) == valorCheck(ultimacartaAnterior)) {
            if (naipeCheck(ultimacartaAtual) > naipeCheck(ultimacartaAnterior)) r = 1;
        }
    }

    return r;
}

// Valida a jogada, se for jogada uma das exceções de Reis
int validaJogadaReis(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    int r = 0;
    int ultimoNaoPasso = -1;
    for (int i = N - 1; i >= N - 3; i--) {
        if (wcscmp(jogadasAnteriores[i], L"PASSO") != 0) {
            ultimoNaoPasso = i;
        }
    }

    if (wcscmp(jogadaAtual, L"PASSO") == 0) r = 1;

    int tamJogadaAnterior = wcslen(jogadasAnteriores[ultimoNaoPasso]);
    int tamJogadaAtual = wcslen(jogadaAtual);
    qsort(jogadasAnteriores[ultimoNaoPasso], tamJogadaAnterior, sizeof(wchar_t), comparaCartas);

    if (umRei(jogadasAnteriores[ultimoNaoPasso]) && todasIguais(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 4) {
        r = 1;
    } else if (umRei(jogadasAnteriores[ultimoNaoPasso]) && verificaDuplaSequencia(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 6) {
        r = 1;
    } else if (doisReis(jogadasAnteriores[ultimoNaoPasso]) && verificaDuplaSequencia(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 8) {
        r = 1;
    } else if (tresReis(jogadasAnteriores[ultimoNaoPasso]) && verificaDuplaSequencia(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 10) {
        r = 1;
    } else if (umRei(jogadasAnteriores[ultimoNaoPasso]) && (validaJogadaNaoPassou(jogadasAnteriores,N,jogadaAtual))) {
        r = 1;
    } else if (doisReis(jogadasAnteriores[ultimoNaoPasso]) && (validaJogadaNaoPassou(jogadasAnteriores,N,jogadaAtual))) {
        r = 1;
    }

    return r;
}

// Função geral de validação
int validaJogada(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    int resultado = validaJogadaNaoPassou(jogadasAnteriores, N, jogadaAtual) || validaJogadaReis(jogadasAnteriores, N, jogadaAtual);
    
    if (resultado) return 1;
    
    if (N == 0 && aMinhaJogadaEValida(jogadaAtual)) return 1;
    
    return 0;
}

// Função geral de validação
int validaAJogadaSeTodosPassaram(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    int todaAGentePassou = todosPassaram(jogadasAnteriores, N);

    if (todaAGentePassou && aMinhaJogadaEValida(jogadaAtual)) return 1;

    return 0;
}

// Processa as jogadas dentro dos testes
void processarCasoTeste(wchar_t mao[], wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[], wchar_t resultado[]) {
    int podeJogar = validaAJogadaSeTodosPassaram(jogadasAnteriores, N, jogadaAtual) || validaJogada(jogadasAnteriores, N, jogadaAtual);
    
    if (podeJogar) {
        removerCartasJogadas(mao, jogadaAtual);
        wcscpy(resultado, mao);
    } else {
        wcscpy(resultado, mao);
    }
}

// Lê a mão do jogador
void lerMao(wchar_t mao[]) {
    wscanf(L"%ls", mao);
    qsort(mao, wcslen(mao), sizeof(wchar_t), comparaCartas);
}

// Lê as jogadas anteriores
void lerJogadasAnteriores(wchar_t jogadasAnteriores[][56], int N) {
    for (int i = 0; i < N; i++) {
        wscanf(L"%ls", jogadasAnteriores[i]);
    }
}

int main() {
    setlocale(LC_ALL, "C.UTF-8");

    int T;
    wscanf(L"%d", &T);

    wchar_t resultados[T][56];

    for (int t = 0; t < T; t++) {
        int N;
        wscanf(L"%d", &N);

        wchar_t mao[56];
        lerMao(mao);

        wchar_t jogadasAnteriores[BUFSIZ][56];
        lerJogadasAnteriores(jogadasAnteriores, N);

        wchar_t jogadaAtual[56];
        wscanf(L"%ls", jogadaAtual);
        qsort(jogadaAtual, wcslen(jogadaAtual), sizeof(wchar_t), comparaCartas);

        processarCasoTeste(mao, jogadasAnteriores, N, jogadaAtual, resultados[t]);
    }

    for (int i = 0; i < T; i++) {
        wprintf(L"Teste %d\n", i + 1);

        for (int j = 0; resultados[i][j] != L'\0'; j++) {
            qsort(resultados[i], wcslen(resultados[i]), sizeof(wchar_t), comparaCartas);

            wprintf(L"%lc", resultados[i][j]);
            if (resultados[i][j + 1] != L'\0') wprintf(L" ");
        }
        wprintf(L"\n");
    }

    return 0;
}