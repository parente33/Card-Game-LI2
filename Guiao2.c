#include "Guiao1.h"
#include "Guiao2.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stddef.h>
#include <stdlib.h>

// Compara duas linhas de cartas com base na carta mais alta de cada uma
int comparaPrimeiraCarta(const void *a, const void *b) {
    const wchar_t (*linha_a)[56] = (const wchar_t (*)[56])a;
    const wchar_t (*linha_b)[56] = (const wchar_t (*)[56])b;

    wchar_t copia_linha_a[56];
    wchar_t copia_linha_b[56];
    wcscpy(copia_linha_a, *linha_a);
    wcscpy(copia_linha_b, *linha_b);

    qsort(copia_linha_a, wcslen(copia_linha_a), sizeof(wchar_t), comparaCartas);
    qsort(copia_linha_b, wcslen(copia_linha_b), sizeof(wchar_t), comparaCartas);

    int tamanho_linha_a = wcslen(copia_linha_a);
    int tamanho_linha_b = wcslen(copia_linha_b);

    wchar_t ultima_carta_a = copia_linha_a[tamanho_linha_a - 1];
    wchar_t ultima_carta_b = copia_linha_b[tamanho_linha_b - 1];

    int valor_ultima_carta_a = valorCheck(ultima_carta_a);
    int valor_ultima_carta_b = valorCheck(ultima_carta_b);

    if (valor_ultima_carta_a < valor_ultima_carta_b) return -1;
    if (valor_ultima_carta_a > valor_ultima_carta_b) return 1;

    int naipe_ultima_carta_a = naipeCheck(ultima_carta_a);
    int naipe_ultima_carta_b = naipeCheck(ultima_carta_b);

    if (naipe_ultima_carta_a < naipe_ultima_carta_b) return -1;
    if (naipe_ultima_carta_a > naipe_ultima_carta_b) return 1;

    return 0;
}

// Verifica se duas jogadas diferentes são o mesmo tipo de combinação
int combinacoesIguais(wchar_t linha[][56], int tamanho) {
    int r = 1;

    for (int i = 1; i < tamanho ; i++) {
        int t = wcslen(linha[i]);
        int t_ = wcslen(linha[i - 1]);

        qsort(linha[i], t, sizeof(wchar_t), comparaCartas);
        qsort(linha[i - 1], t_, sizeof(wchar_t), comparaCartas);

        int Iguais = todasIguais(linha[i], t_);
        int sequencia = verificaSequencia(linha[i], t_);
        int duplaSequencia = verificaDuplaSequencia(linha[i], t_);

        int Iguais1 = todasIguais(linha[i - 1], t);
        int sequencia1 = verificaSequencia(linha[i - 1], t);
        int duplaSequencia1 = verificaDuplaSequencia(linha[i - 1], t);

        if (t != t_ || Iguais != Iguais1 || sequencia != sequencia1 || duplaSequencia != duplaSequencia1) r = 0;
    }
    return r;
}

// Processa as jogadas
void processar1(wchar_t cartas[][56][56], int num_t, int *num_testes) {
    for (int k = 0; k < num_t; k++) {
        wprintf(L"Teste %d\n", k + 1);

        qsort(cartas[k], num_testes[k], sizeof(cartas[k][0]), comparaPrimeiraCarta);

        for (int i = 0; i < num_testes[k]; i++) {
            if (combinacoesIguais(cartas[k], num_testes[k])) {
                size_t comprimento = wcslen(cartas[k][i]);
                for (size_t g = 0; g < comprimento; g++) {
                    wprintf(L"%lc", cartas[k][i][g]);
                    if (g < comprimento - 1) {
                        wprintf(L" ");
                    }
                }
            } else {
                wprintf(L"Combinações não iguais!\n");
                break;
            }
            wprintf(L"\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "C.UTF-8");

    int num_t;
    int num_testes;
    int num_testes1[BUFSIZ];
    wscanf(L"%d", &num_t);
    while (getwchar() != L'\n');

    wchar_t (*cartas)[56][56] = malloc(num_t * sizeof(*cartas));
    if (cartas == NULL) {
        fprintf(stderr, "Falha na memoria.\n");
        return 1;
    }

    for (int k = 0; k < num_t; k++) {
        wscanf(L"%d", &num_testes);
        while (getwchar() != L'\n');
        num_testes1[k]=num_testes;
        for(int i = 0; i < num_testes; i++) {
            if (fgetws(cartas[k][i], BUFSIZ, stdin)){
                size_t len = wcslen(cartas[k][i]);
                if (cartas[k][i][len - 1] == L'\n') cartas[k][i][len - 1] = L'\0';
            }
        }
    }

    processar1(cartas, num_t, num_testes1);

    free(cartas);

    return 0;
}