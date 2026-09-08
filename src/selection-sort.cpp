#include "selection-sort.h"

#include <chrono>

void selectionSort(int arr[], int n, Estatisticas& stats) {
    zerarEstatisticas(stats);

    auto inicio = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int indice_minimo = i;

        for (int j = i + 1; j < n; j++) {
            stats.comparacoes++;

            if (arr[j] < arr[indice_minimo]) {
                indice_minimo = j;
            }
        }

        // Movimenta apenas se o menor elemento nao estiver ja na posicao correta
        if (indice_minimo != i) {
            trocar(arr[i], arr[indice_minimo], stats);
        }
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats.tempoExecucao = std::chrono::duration<double, std::milli>(fim - inicio).count();
}
