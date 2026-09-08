#include "quick-sort.h"

#include <chrono>

/* Particao de Hoare com pivo no elemento central (versao do Wirth).
   Devolve em i e j os limites das duas particoes resultantes. */
static void particao(int v[], int esq, int dir, int& i, int& j, Estatisticas& stats) {
    i = esq;
    j = dir;

    int x = v[esq + (dir - esq) / 2]; // pivo
    stats.movimentacoes++;            // copia do pivo para a variavel auxiliar

    do {
        while (true) {
            stats.comparacoes++;
            if (x > v[i]) i++; else break;
        }
        while (true) {
            stats.comparacoes++;
            if (x < v[j]) j--; else break;
        }

        if (i <= j) {
            trocar(v[i], v[j], stats);
            i++;
            j--;
        }
    } while (i <= j);
}

static void ordena(int v[], int esq, int dir, Estatisticas& stats) {
    /* Recursao apenas na menor particao; a maior continua neste mesmo laco.
       Isso limita a profundidade da pilha a O(log n) mesmo no pior caso. */
    while (esq < dir) {
        int i, j;
        particao(v, esq, dir, i, j, stats);

        if ((j - esq) < (dir - i)) {
            if (esq < j) ordena(v, esq, j, stats);
            esq = i; // continua com a particao da direita
        } else {
            if (i < dir) ordena(v, i, dir, stats);
            dir = j; // continua com a particao da esquerda
        }
    }
}

void quickSort(int v[], int n, Estatisticas& stats) {
    zerarEstatisticas(stats);

    auto inicio = std::chrono::high_resolution_clock::now();

    if (n > 1) ordena(v, 0, n - 1, stats);

    auto fim = std::chrono::high_resolution_clock::now();
    stats.tempoExecucao = std::chrono::duration<double, std::milli>(fim - inicio).count();
}
