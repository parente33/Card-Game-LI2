#include "Guiao1.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stddef.h>
#include <stdlib.h>

// Verifica o naipe de uma carta
int naipeCheck(wchar_t carta) {
    return ((carta-0x1F0A1)/16);
}

// Verifica o valor de uma carta
int valorCheck (wchar_t carta) {
    return (carta-0x1F0A1)%16;
}

// Compara duas cartas (pelo valor e/ou naipe)
int comparaCartas(const void *a, const void *b) {
    const wchar_t *wchar_a = (const wchar_t *)a;
    const wchar_t *wchar_b = (const wchar_t *)b;

    if (valorCheck(*wchar_a) < valorCheck(*wchar_b)) return -1;
    if (valorCheck(*wchar_a) > valorCheck(*wchar_b)) return 1;
    if (naipeCheck(*wchar_a) < naipeCheck(*wchar_b)) return -1;
    if (naipeCheck(*wchar_a) > naipeCheck(*wchar_b)) return 1;

    return 0;
}

// Verifica se uma jogada é uma sequência
int verificaSequencia(wchar_t *cartas, int tamanho) {
    int r = 1;
    if (tamanho < 3) r = 0;

    qsort(cartas, tamanho, sizeof(wchar_t), comparaCartas);
    
    for (int i = 1; i < tamanho; i++) {
        if (valorCheck(cartas[i]) != valorCheck(cartas[i - 1]) + 1) r = 0;
    }
    return r;
}

// Verifica se uma jogada é uma dupla sequência
int verificaDuplaSequencia(wchar_t *cartas, int tamanho) {
    int r = 1;
    if (tamanho < 6) r = 0;
    
    for (int i = 2; i < tamanho; i += 2) {
        if (valorCheck(cartas[i]) != valorCheck(cartas[i - 2]) + 1) r = 0;
    }
    return r;
}

// Verifica se uma jogada é um conjunto
int todasIguais(wchar_t *cartas, int tamanho) {
    int r = 1;
    if (tamanho > 4) r = 0;

    for (int j = 1; j < tamanho; j++) {
        if (valorCheck(cartas[j]) != valorCheck(cartas[0])) r = 0;
    }
    return r;
}

// Processa as jogadas
void processar(wchar_t linha[][BUFSIZ], int ntestes) {
    for (int i = 0; i < ntestes ; i++) {
        wchar_t maisalta = linha[i][0];
        int tamanho = wcslen(linha[i]);

        qsort(linha[i], tamanho, sizeof(wchar_t), comparaCartas);
        int todasIguais = 1;
        int sequencia = verificaSequencia(linha[i], tamanho);
        int duplaSequencia = verificaDuplaSequencia(linha[i],  tamanho);

        for (int k = 1; k < tamanho; k++) {
            if (valorCheck(linha[i][k]) != valorCheck(linha[i][k-1])) todasIguais = 0;
            maisalta = linha[i][k];
        }

        if (todasIguais) {
            wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n", tamanho, maisalta);
        } else if (sequencia) {
            wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", tamanho, maisalta);
        } else if (duplaSequencia) {
            wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", tamanho/2, maisalta);
        } else {
            wprintf(L"Nada!\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "C.UTF-8");

    int num_testes;
    wscanf(L"%d", &num_testes);
    while (getwchar() != L'\n');

    wchar_t (*cartas)[BUFSIZ] = malloc(num_testes * sizeof(*cartas));
    if (cartas == NULL) {
        fprintf(stderr, "Falha na memoria.\n");
        return 1;
    }

    for(int i = 0; i < num_testes; i++) {
        if (fgetws(cartas[i], BUFSIZ, stdin)){
            size_t len = wcslen(cartas[i]);
            if (cartas[i][len - 1] == L'\n') cartas[i][len - 1] = L'\0';
        }
    }

    processar(cartas, num_testes);

    free(cartas);

    return 0;
}