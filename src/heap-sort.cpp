#include "heap-sort.h"

#include <chrono>

/* Reorganiza a sub-arvore de raiz 'i' para satisfazer a propriedade de heap
   maximo. 'n' e o tamanho corrente do heap (pode ser menor que o do vetor).
   Implementado com laco, e nao com recursao, para nao crescer a pilha. */
static void heapify(int arr[], int n, int i, Estatisticas& stats) {
    while (true) {
        int maior = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < n) {
            stats.comparacoes++;
            if (arr[esq] > arr[maior]) maior = esq;
        }

        if (dir < n) {
            stats.comparacoes++;
            if (arr[dir] > arr[maior]) maior = dir;
        }

        if (maior == i) break; // ja e um heap valido a partir daqui

        trocar(arr[i], arr[maior], stats);
        i = maior; // desce para o filho trocado
    }
}

void heapSort(int arr[], int n, Estatisticas& stats) {
    zerarEstatisticas(stats);

    auto inicio = std::chrono::high_resolution_clock::now();

    // 1. Constroi o heap maximo a partir do ultimo no interno
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, stats);
    }

    // 2. Especie de selection sort: leva a raiz (maior) para o fim e encolhe o heap
    for (int ultimo = n - 1; ultimo > 0; ultimo--) {
        trocar(arr[0], arr[ultimo], stats);
        heapify(arr, ultimo, 0, stats);
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats.tempoExecucao = std::chrono::duration<double, std::milli>(fim - inicio).count();
}
