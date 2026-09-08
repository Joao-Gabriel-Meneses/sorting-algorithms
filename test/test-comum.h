#ifndef TEST_COMUM_H
#define TEST_COMUM_H

/* Bateria de testes compartilhada por todos os algoritmos de ordenacao.
   Cada arquivo *-sort-test.cpp so precisa informar o nome e a funcao. */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // std::sort, std::is_sorted (apenas como gabarito nos testes)
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../src/estatisticas.h"
#include "../src/gerador.h"

typedef void (*FuncaoOrdenacaoTeste)(int[], int, Estatisticas&);

// -------------------------------------------------------------
// Utilitarios
// -------------------------------------------------------------

/* Gabarito: a mesma entrada ordenada pela std::sort. */
inline std::vector<int> gabarito(const std::vector<int>& v) {
    std::vector<int> copia = v;
    std::sort(copia.begin(), copia.end());
    return copia;
}

/* Ordena uma copia e valida: ficou crescente, manteve exatamente os mesmos
   elementos e produziu estatisticas coerentes. */
inline Estatisticas ordenarEValidar(FuncaoOrdenacaoTeste ordenar,
                                    const std::string& caso,
                                    const std::vector<int>& entrada,
                                    bool imprimir = true) {
    std::vector<int> v = entrada;
    std::vector<int> esperado = gabarito(entrada);

    Estatisticas stats;
    zerarEstatisticas(stats);
    if (!v.empty()) {
        ordenar(v.data(), static_cast<int>(v.size()), stats);
    }

    assert(std::is_sorted(v.begin(), v.end()));   // ficou ordenado
    assert(v == esperado);                        // nada perdido nem duplicado
    assert(stats.tempoExecucao >= 0.0);           // tempo coerente

    if (imprimir) {
        std::cout << "[PASSOU] " << caso
                  << " (n=" << v.size()
                  << ", comparacoes=" << stats.comparacoes
                  << ", movimentacoes=" << stats.movimentacoes
                  << ", tempo=" << stats.tempoExecucao << " ms)\n";
    }

    return stats;
}

// -------------------------------------------------------------
// Testes comuns
// -------------------------------------------------------------

/* 1. Casos limite: vetor vazio, um elemento e dois elementos. */
inline void teste_casos_limite(FuncaoOrdenacaoTeste ordenar) {
    std::vector<int> vazio;
    Estatisticas stats;
    zerarEstatisticas(stats);
    ordenar(vazio.data(), 0, stats); // nao pode quebrar nem acessar memoria invalida
    assert(stats.comparacoes == 0);
    assert(stats.movimentacoes == 0);

    ordenarEValidar(ordenar, "1 elemento", std::vector<int>(1, 42), false);
    ordenarEValidar(ordenar, "2 elementos fora de ordem", {2, 1}, false);
    ordenarEValidar(ordenar, "2 elementos em ordem", {1, 2}, false);

    std::cout << "[PASSOU] Casos limite (n = 0, 1 e 2)\n";
}

/* 2. Vetores pequenos escritos a mao. */
inline void teste_vetores_pequenos(FuncaoOrdenacaoTeste ordenar) {
    ordenarEValidar(ordenar, "Aleatorio pequeno", {33, 10, 440, 0, 100, 45});
    ordenarEValidar(ordenar, "Todos iguais", {7, 7, 7, 7, 7});
    ordenarEValidar(ordenar, "Ordem inversa", {5, 4, 3, 2, 1});
    ordenarEValidar(ordenar, "Negativos e repetidos", {-3, 10, -3, 0, 7, -100, 10});
}

/* 3. Os quatro cenarios de organizacao exigidos pelo laboratorio. */
inline void teste_cenarios_de_organizacao(FuncaoOrdenacaoTeste ordenar, int N = 2000) {
    const TipoOrganizacao tipos[] = { ALEATORIO, ORDENADO, INVERSO, PARCIALMENTE_ORDENADO };

    for (int t = 0; t < 4; ++t) {
        std::vector<int> dados = gerarConjuntoDeDados(N, tipos[t]);
        ordenarEValidar(ordenar, std::string("Cenario ") + nomeOrganizacao(tipos[t]), dados);
    }
}

/* 4. Muitas rodadas aleatorias de tamanhos variados. */
inline void teste_aleatorio_repetido(FuncaoOrdenacaoTeste ordenar, int rodadas = 200) {
    for (int r = 0; r < rodadas; ++r) {
        int n = std::rand() % 100;
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = std::rand() % 50 - 25; // repetidos e negativos

        std::vector<int> esperado = gabarito(v);
        Estatisticas stats;
        zerarEstatisticas(stats);
        if (n > 0) ordenar(v.data(), n, stats);
        assert(v == esperado);
    }

    std::cout << "[PASSOU] Aleatorio repetido (" << rodadas << " rodadas)\n";
}

/* 5. A instrumentacao precisa contar de fato. */
inline void teste_instrumentacao(FuncaoOrdenacaoTeste ordenar, int N = 5000) {
    std::vector<int> dados = gerarConjuntoDeDados(N, ALEATORIO);
    Estatisticas stats = ordenarEValidar(ordenar, "Instrumentacao", dados, false);

    assert(stats.comparacoes > 0);
    assert(stats.movimentacoes > 0);
    // Nenhum destes algoritmos passa de n^2 comparacoes
    assert(stats.comparacoes <= static_cast<unsigned long long>(N) * N);

    // Uma segunda execucao precisa zerar os contadores (nao acumular)
    std::vector<int> outra = gerarConjuntoDeDados(N, ALEATORIO);
    Estatisticas stats2;
    ordenar(outra.data(), N, stats2);
    assert(stats2.comparacoes <= static_cast<unsigned long long>(N) * N);

    std::cout << "[PASSOU] Instrumentacao (comparacoes=" << stats.comparacoes
              << ", movimentacoes=" << stats.movimentacoes << ")\n";
}

/* Runner: roda a bateria comum inteira para um algoritmo. */
inline int rodarBateriaComum(const std::string& nome, FuncaoOrdenacaoTeste ordenar) {
    std::srand(static_cast<unsigned>(std::time(NULL)));

    std::cout << "========================================\n";
    std::cout << " TESTES UNITARIOS - " << nome << "\n";
    std::cout << "========================================\n\n";

    teste_casos_limite(ordenar);
    teste_vetores_pequenos(ordenar);
    teste_cenarios_de_organizacao(ordenar);
    teste_aleatorio_repetido(ordenar);
    teste_instrumentacao(ordenar);

    return 0;
}

inline void encerrarTestes(const std::string& nome) {
    std::cout << "\n----------------------------------------\n";
    std::cout << " " << nome << ": TODOS OS TESTES PASSARAM!\n";
    std::cout << "----------------------------------------\n";
}

#endif
