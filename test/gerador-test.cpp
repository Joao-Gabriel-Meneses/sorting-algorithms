/* Testes do gerador de conjuntos de dados.
   Usa o modulo real (src/gerador.cpp), sem copia do codigo. */

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

#include "../src/gerador.h"

// 1. O vetor gerado tem exatamente N posicoes
void teste_tamanho_do_vetor() {
    int N = 1000;
    assert(gerarConjuntoDeDados(N, ALEATORIO).size() == static_cast<size_t>(N));
    assert(gerarConjuntoDeDados(N, ORDENADO).size()  == static_cast<size_t>(N));
    assert(gerarConjuntoDeDados(N, INVERSO).size()   == static_cast<size_t>(N));
    assert(gerarConjuntoDeDados(N, PARCIALMENTE_ORDENADO).size() == static_cast<size_t>(N));

    std::cout << "[PASSOU] Tamanho do vetor\n";
}

// 2. O cenario ORDENADO e estritamente crescente
void teste_dados_ordenados() {
    int N = 500;
    std::vector<int> v = gerarConjuntoDeDados(N, ORDENADO);

    for (int i = 0; i < N - 1; ++i) {
        assert(v[i] < v[i + 1]);
    }

    std::cout << "[PASSOU] Dados ordenados\n";
}

// 3. O cenario INVERSO e estritamente decrescente
void teste_dados_inversos() {
    int N = 500;
    std::vector<int> v = gerarConjuntoDeDados(N, INVERSO);

    for (int i = 0; i < N - 1; ++i) {
        assert(v[i] > v[i + 1]);
    }

    std::cout << "[PASSOU] Dados inversos\n";
}

// 4. O cenario PARCIALMENTE_ORDENADO fica desordenado, mas nao caotico
void teste_dados_parcialmente_ordenados() {
    int N = 1000;
    std::vector<int> v = gerarConjuntoDeDados(N, PARCIALMENTE_ORDENADO);

    int desalinhados = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (v[i] > v[i + 1]) desalinhados++;
    }

    assert(desalinhados > 0);          // as trocas surtiram efeito
    assert(desalinhados < N * 0.5);    // mas a maior parte da ordem foi mantida

    std::cout << "[PASSOU] Dados parcialmente ordenados (" << desalinhados
              << " posicoes fora de ordem)\n";
}

// 5. Casos limite de N
void teste_casos_limite() {
    assert(gerarConjuntoDeDados(0, ALEATORIO).empty());
    assert(gerarConjuntoDeDados(1, ORDENADO).size() == 1);
    assert(gerarConjuntoDeDados(1, PARCIALMENTE_ORDENADO).size() == 1);

    std::cout << "[PASSOU] Casos limite (N = 0 e 1)\n";
}

// 6. Todo cenario tem um nome legivel para os cabecalhos das tabelas
void teste_nomes_dos_cenarios() {
    const TipoOrganizacao tipos[] = { ALEATORIO, ORDENADO, INVERSO, PARCIALMENTE_ORDENADO };
    for (int i = 0; i < 4; ++i) {
        const char* nome = nomeOrganizacao(tipos[i]);
        assert(nome != NULL && nome[0] != '\0');
    }

    std::cout << "[PASSOU] Nomes dos cenarios\n";
}

int main() {
    std::srand(static_cast<unsigned>(std::time(NULL)));

    std::cout << "========================================\n";
    std::cout << " TESTES UNITARIOS - GERADOR DE DADOS\n";
    std::cout << "========================================\n\n";

    teste_tamanho_do_vetor();
    teste_dados_ordenados();
    teste_dados_inversos();
    teste_dados_parcialmente_ordenados();
    teste_casos_limite();
    teste_nomes_dos_cenarios();

    std::cout << "\n----------------------------------------\n";
    std::cout << " Gerador: TODOS OS TESTES PASSARAM!\n";
    std::cout << "----------------------------------------\n";

    return 0;
}
