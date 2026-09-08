#include <iostream>
#include <vector>
#include <algorithm> // std::sort, std::is_sorted (apenas como referencia nos testes)
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../src/heap-sort.cpp"

// -------------------------------------------------------------
// Utilitarios
// -------------------------------------------------------------

// Ordena uma copia com a std::sort para servir de gabarito
static std::vector<int> gabarito(const std::vector<int>& v) {
    std::vector<int> copia = v;
    std::sort(copia.begin(), copia.end());
    return copia;
}

// Roda o heapSort sobre uma copia e valida o resultado contra o gabarito
static Estatisticas ordenarEValidar(const char* nome, const std::vector<int>& entrada) {
    std::vector<int> v = entrada;
    std::vector<int> esperado = gabarito(entrada);

    Estatisticas stats;
    heapSort(v.data(), static_cast<int>(v.size()), stats);

    // 1. O vetor precisa estar em ordem crescente
    assert(std::is_sorted(v.begin(), v.end()));
    // 2. E precisa conter exatamente os mesmos elementos da entrada (nada perdido/duplicado)
    assert(v == esperado);
    // 3. O tempo medido nunca pode ser negativo
    assert(stats.tempoExecucao >= 0.0);

    std::cout << "[PASSOU] " << nome
              << " (n=" << v.size()
              << ", comparacoes=" << stats.comparacoes
              << ", movimentacoes=" << stats.movimentacoes
              << ", tempo=" << stats.tempoExecucao << " ms)\n";

    return stats;
}

// -------------------------------------------------------------
// Testes Unitarios
// -------------------------------------------------------------

// 1. Casos limite: vetor vazio, um elemento e dois elementos
void teste_casos_limite() {
    std::vector<int> vazio;
    Estatisticas stats;
    heapSort(vazio.data(), 0, stats); // nao pode quebrar nem acessar memoria invalida
    assert(stats.comparacoes == 0);
    assert(stats.movimentacoes == 0);

    ordenarEValidar("Vetor com 1 elemento", {42});
    ordenarEValidar("Vetor com 2 elementos (fora de ordem)", {2, 1});
    ordenarEValidar("Vetor com 2 elementos (em ordem)", {1, 2});

    std::cout << "[PASSOU] Teste de Casos Limite\n";
}

// 2. Casos pequenos escritos a mao, incluindo repetidos e negativos
void teste_vetores_pequenos() {
    ordenarEValidar("Aleatorio pequeno", {33, 10, 440, 0, 100, 45});
    ordenarEValidar("Todos iguais", {7, 7, 7, 7, 7});
    ordenarEValidar("Ordem inversa", {5, 4, 3, 2, 1});
    ordenarEValidar("Com negativos e repetidos", {-3, 10, -3, 0, 7, -100, 10});
}

// 3. Os quatro cenarios de organizacao exigidos pelo laboratorio
void teste_cenarios_de_organizacao() {
    const int N = 2000;

    std::vector<int> ordenado(N);
    for (int i = 0; i < N; ++i) ordenado[i] = i + 1;

    std::vector<int> inverso(N);
    for (int i = 0; i < N; ++i) inverso[i] = N - i;

    std::vector<int> aleatorio(N);
    for (int i = 0; i < N; ++i) aleatorio[i] = std::rand() % (N * 10);

    std::vector<int> parcial = ordenado;
    int numeroDeTrocas = static_cast<int>(N * 0.10);
    for (int i = 0; i < numeroDeTrocas; ++i) {
        std::swap(parcial[std::rand() % N], parcial[std::rand() % N]);
    }

    ordenarEValidar("Cenario ORDENADO", ordenado);
    ordenarEValidar("Cenario INVERSO", inverso);
    ordenarEValidar("Cenario ALEATORIO", aleatorio);
    ordenarEValidar("Cenario PARCIALMENTE_ORDENADO", parcial);
}

// 4. Teste aleatorio repetido: varios vetores de tamanhos variados
void teste_aleatorio_repetido() {
    for (int rodada = 0; rodada < 200; ++rodada) {
        int n = std::rand() % 100;
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = std::rand() % 50 - 25; // repetidos e negativos

        std::vector<int> esperado = gabarito(v);
        Estatisticas stats;
        heapSort(v.data(), n, stats);
        assert(v == esperado);
    }

    std::cout << "[PASSOU] Teste Aleatorio Repetido (200 rodadas)\n";
}

// 5. A instrumentacao deve refletir o comportamento O(n log n) do Heap Sort
void teste_instrumentacao() {
    const int N = 10000;
    std::vector<int> v(N);
    for (int i = 0; i < N; ++i) v[i] = std::rand();

    Estatisticas stats;
    heapSort(v.data(), N, stats);

    // Cada troca conta 3 movimentacoes, entao com N > 1 sempre ha movimentacao
    assert(stats.comparacoes > 0);
    assert(stats.movimentacoes > 0);

    // Limite teorico folgado: heapify faz no maximo 2 comparacoes por nivel,
    // e sao O(n log n) descidas. Usamos 6*n*log2(n) como teto de seguranca.
    double teto = 6.0 * N * std::log2(static_cast<double>(N));
    assert(static_cast<double>(stats.comparacoes) < teto);

    // O vetor ja ordenado NAO e o melhor caso do Heap Sort: ele continua O(n log n)
    std::vector<int> ordenado(N);
    for (int i = 0; i < N; ++i) ordenado[i] = i;
    Estatisticas statsOrdenado;
    heapSort(ordenado.data(), N, statsOrdenado);
    assert(statsOrdenado.comparacoes > static_cast<unsigned long long>(N));

    std::cout << "[PASSOU] Teste de Instrumentacao (comparacoes=" << stats.comparacoes
              << ", movimentacoes=" << stats.movimentacoes << ")\n";
}

// 6. Runner dos testes
int main() {
    std::srand(std::time(NULL));

    std::cout << "========================================\n";
    std::cout << " INICIANDO TESTES UNITARIOS DO HEAP SORT\n";
    std::cout << "========================================\n\n";

    teste_casos_limite();
    teste_vetores_pequenos();
    teste_cenarios_de_organizacao();
    teste_aleatorio_repetido();
    teste_instrumentacao();

    std::cout << "\n----------------------------------------\n";
    std::cout << " TODOS OS TESTES PASSARAM COM SUCESSO!\n";
    std::cout << "----------------------------------------\n";

    return 0;
}
