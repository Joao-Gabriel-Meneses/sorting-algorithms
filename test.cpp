#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm> // std::swap, std::is_sorted

// -------------------------------------------------------------
// Tipos e Função a ser testada
// -------------------------------------------------------------
enum TipoOrganizacao {
    ALEATORIO,
    ORDENADO,
    INVERSO,
    PARCIALMENTE_ORDENADO
};

std::vector<int> gerarConjuntoDeDados(int N, TipoOrganizacao tipo) {
    std::vector<int> vetor(N);
    
    switch (tipo) {
        case ORDENADO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = i + 1;
            }
            break;
            
        case INVERSO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = N - i;
            }
            break;
            
        case ALEATORIO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = std::rand() % (N * 10);
            }
            break;
            
        case PARCIALMENTE_ORDENADO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = i + 1;
            }
            int numeroDeTrocas = N * 0.10;
            for (int i = 0; i < numeroDeTrocas; ++i) {
                int pos1 = std::rand() % N;
                int pos2 = std::rand() % N;
                std::swap(vetor[pos1], vetor[pos2]);
            }
            break;
    }

    return vetor;
}

// -------------------------------------------------------------
// Testes Unitários
// -------------------------------------------------------------

// 1. Testa se o tamanho do vetor gerado é exatamente N
void teste_tamanho_do_vetor() {
    int N = 1000;
    std::vector<int> v1 = gerarConjuntoDeDados(N, ALEATORIO);
    std::vector<int> v2 = gerarConjuntoDeDados(N, ORDENADO);
    
    assert(v1.size() == static_cast<size_t>(N));
    assert(v2.size() == static_cast<size_t>(N));
    
    std::cout << "[PASSOU] Teste de Tamanho do Vetor\n";
}

// 2. Testa se o conjunto ORDENADO está estritamente crescente
void teste_dados_ordenados() {
    int N = 500;
    std::vector<int> v = gerarConjuntoDeDados(N, ORDENADO);
    
    assert(v.size() == static_cast<size_t>(N));
    for (int i = 0; i < N - 1; ++i) {
        assert(v[i] < v[i + 1]); // Cada elemento deve ser menor que o proximo
    }
    
    std::cout << "[PASSOU] Teste de Dados Ordenados\n";
}

// 3. Testa se o conjunto INVERSO está estritamente decrescente
void teste_dados_inversos() {
    int N = 500;
    std::vector<int> v = gerarConjuntoDeDados(N, INVERSO);
    
    assert(v.size() == static_cast<size_t>(N));
    for (int i = 0; i < N - 1; ++i) {
        assert(v[i] > v[i + 1]); // Cada elemento deve ser maior que o proximo
    }
    
    std::cout << "[PASSOU] Teste de Dados Inversos\n";
}

// 4. Testa se o conjunto PARCIALMENTE_ORDENADO não está 100% ordenado, mas mantem coerência
void teste_dados_parcialmente_ordenados() {
    int N = 1000;
    std::vector<int> v = gerarConjuntoDeDados(N, PARCIALMENTE_ORDENADO);
    
    assert(v.size() == static_cast<size_t>(N));
    
    // Conta quantas posicoes estao fora da ordem estrita
    int desalinhados = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (v[i] > v[i + 1]) {
            desalinhados++;
        }
    }
    
    // Como trocamos 10% dos elementos, deve haver alguns elementos fora de ordem
    assert(desalinhados > 0);
    // Mas a maioria do vetor ainda deve manter a ordem relativa
    assert(desalinhados < N * 0.5);
    
    std::cout << "[PASSOU] Teste de Dados Parcialmente Ordenados\n";
}

// 5. Runner dos testes
int main() {
    std::srand(std::time(NULL));
    
    std::cout << "========================================\n";
    std::cout << " INICIANDO TESTES UNITARIOS DO GERADOR\n";
    std::cout << "========================================\n\n";

    teste_tamanho_do_vetor();
    teste_dados_ordenados();
    teste_dados_inversos();
    teste_dados_parcialmente_ordenados();

    std::cout << "\n----------------------------------------\n";
    std::cout << " TODOS OS TESTES PASSARAM COM SUCESSO!\n";
    std::cout << "----------------------------------------\n";

    std::cout << "\nPressione Enter para sair...";
    std::cin.get();

    return 0;
}