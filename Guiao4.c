#include "Guiao1.h"
#include "Guiao2.h"
#include "Guiao3.h"
#include "Guiao4.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

void gerarCombinacoes(wchar_t *mao, int tamanho, wchar_t combinacao[][56], int *combinacoesCount) {
    for (int i = 1; i <= tamanho; i++) {
        for (int j = 0; j < tamanho - i + 1; j++) {
            for (int k = 0; k < i; k++) {
                combinacao[*combinacoesCount][k] = mao[j + k];
            }
            (*combinacoesCount)++;
        }
    }
}

void todasCombinacoesMelhores(wchar_t jogadaAtual[], wchar_t mao[], int N) {
    int tamanho = wcslen(mao);
    wchar_t combinacao[56][56];
    int combinacoesCount = 0;

    gerarCombinacoes(mao, tamanho, combinacao, &combinacoesCount);

    qsort(combinacao, combinacoesCount, sizeof(wchar_t) * 56, comparaCartas);

    for (int i = 0; i < combinacoesCount; i++) {
        wchar_t jogadasAnteriores[3][56] = {{L'\0'}};
        if (validaJogada(jogadasAnteriores, N, combinacao[i])) {
            wprintf(L"%s\n", combinacao[i]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "C.UTF-8");
    int T;
    wscanf(L"%d", &T);

    wchar_t resultados[T][56];

    for (int t = 1; t <= T; t++) {
        wchar_t jogadaAtual[56], mao[56];
        wscanf(L"%ls", jogadaAtual);
        wscanf(L"%ls", mao);

        wprintf(L"Teste %d\n", t);

        todasCombinacoesMelhores(jogadaAtual, mao, t);
    }

    return 0;
}