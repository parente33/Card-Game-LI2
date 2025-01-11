#include "Guiao1.h"
#include "Guiao2.h"
#include "Guiao3.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool aMinhaJogadaEValida (wchar_t jogadaAtual[]) {
    if (verificaSequencia(jogadaAtual, wcslen(jogadaAtual)) ||
        verificaDuplaSequencia(jogadaAtual, wcslen(jogadaAtual)) ||
        todasIguais (jogadaAtual, wcslen(jogadaAtual)) ||
        wcscmp(jogadaAtual, L"PASSO") == 0) {
            return true;
    }

    return false;
}


// Verifica se todas as três jogadas anteriores são "PASSO"
bool todosPassaram(wchar_t jogadasAnteriores[][56], int N) {
    if (N < 3)
        return false;

    for (int i = N - 1; i >= N - 3; i--) {
        if (wcscmp(jogadasAnteriores[i], L"PASSO") != 0)
            return false;
    }

    return true;
}


// Verifica se uma jogada é apenas uma carta do tipo Rei
bool umRei (wchar_t *jogada) {
    if (wcslen(jogada) == 1) {
        for (int i = 0; i < (int)wcslen(jogada); i++) {
            if (valorCheck(jogada[i]) != 13)
                return false;
        }
        return true;
    }   
    return false;
}

// Verifica se uma jogada são duas cartas do tipo Rei
bool doisReis(wchar_t *jogada) {
    if (wcslen(jogada) == 2) {
        for (int j = 0; j < (int)wcslen(jogada); j++) {
            if (valorCheck(jogada[j]) != 13)
                return false;
        }
        return true;
    }
    return false;
}

// Verifica se uma jogada são três cartas do tipo Rei
bool tresReis (wchar_t *jogada) {
    if (wcslen(jogada) == 3) {
        for (int k = 0; k < (int)wcslen(jogada); k++) {
            if (valorCheck(jogada[k]) != 13)
                return false;
        }
        return true;
    }
    return false;
}

// Valida a jogada, caso um jogador não tenha passado
bool validaJogadaNaoPassou(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    int ultimoNaoPasso = -1;
    for (int i = N - 1; i >= N - 3; i--) {
        if (wcscmp(jogadasAnteriores[i], L"PASSO") != 0) {
            ultimoNaoPasso = i;
            break;
        }
    }

    if (wcscmp(jogadaAtual, L"PASSO") == 0) {
            return true;
        }

    if (ultimoNaoPasso != -1 && wcslen(jogadasAnteriores[ultimoNaoPasso]) == wcslen(jogadaAtual)) {
        wchar_t ultimacartaAnterior = jogadasAnteriores[ultimoNaoPasso][wcslen(jogadasAnteriores[ultimoNaoPasso]) - 1];
        wchar_t ultimacartaAtual = jogadaAtual[wcslen(jogadaAtual) - 1];

        if (aMinhaJogadaEValida(jogadaAtual) && valorCheck(ultimacartaAtual) > valorCheck(ultimacartaAnterior)) { 
            return true;
        }
            else if (valorCheck(ultimacartaAtual) == valorCheck(ultimacartaAnterior)) {
            if (naipeCheck(ultimacartaAtual) > naipeCheck(ultimacartaAnterior)) {
                return true;
            } 
        }
    }

    return false;
}

// Valida a jogada, se for jogada uma das exceções de Reis
bool validaJogadaReis(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    int ultimoNaoPasso = -1;
    for (int i = N - 1; i >= N - 3; i--) {
        if (wcscmp(jogadasAnteriores[i], L"PASSO") != 0) {
            ultimoNaoPasso = i;
        }
    }

    if (wcscmp(jogadaAtual, L"PASSO") == 0) {
            return true;
        }

    int tamJogadaAnterior = wcslen(jogadasAnteriores[ultimoNaoPasso]);
    int tamJogadaAtual = wcslen(jogadaAtual);
    qsort(jogadasAnteriores[ultimoNaoPasso], tamJogadaAnterior, sizeof(wchar_t), comparaCartas);

    if (umRei(jogadasAnteriores[ultimoNaoPasso]) && todasIguais(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 4) {
        return true;
    } else if (umRei(jogadasAnteriores[ultimoNaoPasso]) && verificaDuplaSequencia(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 6) {
        return true;
    } else if (doisReis(jogadasAnteriores[ultimoNaoPasso]) && verificaDuplaSequencia(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 8) {
        return true;
    } else if (tresReis(jogadasAnteriores[ultimoNaoPasso]) && verificaDuplaSequencia(jogadaAtual,tamJogadaAtual) && tamJogadaAtual == 10) {
        return true;
    } else if (umRei(jogadasAnteriores[ultimoNaoPasso]) && (validaJogadaNaoPassou(jogadasAnteriores,N,jogadaAtual))) {
        return true;
    } else if (doisReis(jogadasAnteriores[ultimoNaoPasso]) && (validaJogadaNaoPassou(jogadasAnteriores,N,jogadaAtual))) {
        return true;
    }

    return false;
}

// Função geral de validação
bool validaJogada(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    bool resultado = validaJogadaNaoPassou(jogadasAnteriores, N, jogadaAtual) || validaJogadaReis(jogadasAnteriores, N, jogadaAtual);
    
    if (resultado)
        return true;
    
    if (N == 0 && aMinhaJogadaEValida(jogadaAtual)) { 
        return true;
    }
    
    return false;
}

// Função geral de validação
bool validaAJogadaSeTodosPassaram(wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[]) {
    bool todaAGentePassou = todosPassaram(jogadasAnteriores, N);

    if (todaAGentePassou && aMinhaJogadaEValida(jogadaAtual)) {
            return true;
    }

    return false;
}

// Processa as jogadas dentro dos testes
void processarCasoTeste(wchar_t mao[], wchar_t jogadasAnteriores[][56], int N, wchar_t jogadaAtual[], wchar_t resultado[]) {
    bool podeJogar = validaAJogadaSeTodosPassaram(jogadasAnteriores, N, jogadaAtual) || validaJogada(jogadasAnteriores, N, jogadaAtual);
    
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