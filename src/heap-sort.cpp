#include <iostream>
#include <chrono>

struct Estatisticas {
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
    double tempoExecucao; // em milissegundos
};

/* Reorganiza o sub-arvore de raiz 'i' para satisfazer a propriedade de heap maximo.
   'n' e o tamanho corrente do heap (pode ser menor que o tamanho do vetor). */
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

        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        stats.movimentacoes += 3;

        i = maior; // desce para o filho trocado
    }
}

void heapSort(int arr[], int n, Estatisticas& stats) {
    stats.comparacoes = 0;
    stats.movimentacoes = 0;
    stats.tempoExecucao = 0.0;

    auto inicio = std::chrono::high_resolution_clock::now();

    // 1. Constroi o heap maximo a partir do ultimo no interno
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, stats);
    }

    // 2. Especie de selection sort: move a raiz (maior) para o fim e reduz o heap
    for (int fim = n - 1; fim > 0; fim--) {
        int temp = arr[0];
        arr[0] = arr[fim];
        arr[fim] = temp;
        stats.movimentacoes += 3;

        heapify(arr, fim, 0, stats);
    }

    auto fim = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    stats.tempoExecucao = duracao.count();
}
