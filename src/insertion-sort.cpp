#include "insertion-sort.h"

#include <chrono>

void insertionSort(int arr[], int n, Estatisticas& stats) {
    zerarEstatisticas(stats);

    auto inicio = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        stats.movimentacoes++; // guarda a chave

        int j = i - 1;

        while (j >= 0) {
            stats.comparacoes++;

            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                stats.movimentacoes++;
                j--;
            } else {
                break;
            }
        }

        arr[j + 1] = chave;
        stats.movimentacoes++;
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats.tempoExecucao = std::chrono::duration<double, std::milli>(fim - inicio).count();
}
