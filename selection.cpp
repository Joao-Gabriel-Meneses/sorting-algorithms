#include <iostream>
#include <chrono>
#include <cassert>

struct Estatisticas {
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
    double tempoExecucao; 
};

void trocar(int& a, int& b, Estatisticas& stats) {
    int temp = a;
    a = b;
    b = temp;
    stats.movimentacoes++; 
}

void selectionSort(int arr[], int n, Estatisticas& stats) {
    // Inicializando as estatísticas para garantir que comecem do zero nesta execução
    stats.comparacoes = 0;
    stats.movimentacoes = 0;
    stats.tempoExecucao = 0.0;

    // Marcando o tempo de início
    auto inicio = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int indice_minimo = i;

        for (int j = i + 1; j < n; j++) {
            stats.comparacoes++; // Contabilizando a comparação
            
            if (arr[j] < arr[indice_minimo]) {
                indice_minimo = j;
            }
        }

        // Realiza a movimentação apenas se o menor elemento não estiver na posição atual
        if (indice_minimo != i) {
            trocar(arr[i], arr[indice_minimo], stats);
        }
    }

    // Marcando o tempo de fim
    auto fim = std::chrono::high_resolution_clock::now();
    
    // Calculando o tempo de execução em milissegundos
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    stats.tempoExecucao = duracao.count();
}