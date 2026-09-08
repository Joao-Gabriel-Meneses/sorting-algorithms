#include <iostream>
#include <chrono>

struct Estatisticas {
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
    double tempoExecucao; 
};

void insertionSort(int arr[], int n, Estatisticas& stats) {
    stats.comparacoes = 0;
    stats.movimentacoes = 0;
    stats.tempoExecucao = 0.0;

    auto inicio = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        stats.movimentacoes++; 
        
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
    
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    stats.tempoExecucao = duracao.count();
}