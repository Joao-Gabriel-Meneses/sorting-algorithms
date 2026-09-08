#include <iostream>
#include <chrono>

// Estrutura para armazenar as estatisticas de execucao do algoritmo
struct EstatisticasOrdenacao {
    long comparacoes;
    long movimentacoes;
    double tempoExecucao; /* em segundos */
};

EstatisticasOrdenacao shellSort(int vetor[], int n) {
    EstatisticasOrdenacao stats;
    stats.comparacoes = 0;
    stats.movimentacoes = 0;
    stats.tempoExecucao = 0.0;

    auto inicio = std::chrono::high_resolution_clock::now();

    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        /* Insertion sort "espacado" de h em h posicoes */
        for (int i = h; i < n; i++) {
            int atual = vetor[i]; 

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

            if (j != i) {
                vetor[j] = atual;
                stats.movimentacoes++;
            }
        }
        h = h / 3;
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats.tempoExecucao = std::chrono::duration<double>(fim - inicio).count();

    return stats;
}

/* Funcao auxiliar para exibir o vetor (util para testes/depuracao) */
void exibirVetor(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;
}