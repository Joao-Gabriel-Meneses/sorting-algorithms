#include "shell-sort.h"

#include <chrono>

void shellSort(int vetor[], int n, Estatisticas& stats) {
    zerarEstatisticas(stats);

    auto inicio = std::chrono::high_resolution_clock::now();

    // Sequencia de Knuth: 1, 4, 13, 40, 121, ...
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        /* Insertion sort "espacado" de h em h posicoes */
        for (int i = h; i < n; i++) {
            int atual = vetor[i];
            stats.movimentacoes++; // guarda a chave

            int j = i;

            while (j >= h) {
                stats.comparacoes++;

                if (vetor[j - h] > atual) {
                    vetor[j] = vetor[j - h];
                    stats.movimentacoes++;
                    j -= h;
                } else {
                    break;
                }
            }

            vetor[j] = atual;
            stats.movimentacoes++;
        }
        h = h / 3;
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats.tempoExecucao = std::chrono::duration<double, std::milli>(fim - inicio).count();
}
