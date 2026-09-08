#include "test-comum.h"
#include "../src/insertion-sort.h"

/* Melhor caso do Insertion Sort: vetor ja ordenado faz exatamente n-1 comparacoes. */
void teste_melhor_caso() {
    const int N = 1000;
    std::vector<int> v = gerarConjuntoDeDados(N, ORDENADO);

    Estatisticas stats;
    insertionSort(v.data(), N, stats);

    assert(stats.comparacoes == static_cast<unsigned long long>(N - 1));

    std::cout << "[PASSOU] Melhor caso (ordenado): " << stats.comparacoes
              << " comparacoes = n-1\n";
}

/* Pior caso do Insertion Sort: ordem inversa faz n(n-1)/2 comparacoes. */
void teste_pior_caso() {
    const int N = 1000;
    std::vector<int> v = gerarConjuntoDeDados(N, INVERSO);

    Estatisticas stats;
    insertionSort(v.data(), N, stats);

    unsigned long long esperado = static_cast<unsigned long long>(N) * (N - 1) / 2;
    assert(stats.comparacoes == esperado);

    std::cout << "[PASSOU] Pior caso (inverso): " << stats.comparacoes
              << " comparacoes = n(n-1)/2\n";
}

/* O Insertion Sort e adaptativo: quanto mais ordenada a entrada, menos trabalho. */
void teste_adaptatividade() {
    const int N = 2000;

    std::vector<int> ordenado = gerarConjuntoDeDados(N, ORDENADO);
    std::vector<int> parcial  = gerarConjuntoDeDados(N, PARCIALMENTE_ORDENADO);
    std::vector<int> inverso  = gerarConjuntoDeDados(N, INVERSO);

    Estatisticas sOrd, sParcial, sInv;
    insertionSort(ordenado.data(), N, sOrd);
    insertionSort(parcial.data(),  N, sParcial);
    insertionSort(inverso.data(),  N, sInv);

    assert(sOrd.comparacoes < sParcial.comparacoes);
    assert(sParcial.comparacoes < sInv.comparacoes);

    std::cout << "[PASSOU] Adaptatividade: ordenado(" << sOrd.comparacoes
              << ") < parcial(" << sParcial.comparacoes
              << ") < inverso(" << sInv.comparacoes << ")\n";
}

int main() {
    rodarBateriaComum("INSERTION SORT", insertionSort);

    teste_melhor_caso();
    teste_pior_caso();
    teste_adaptatividade();

    encerrarTestes("Insertion Sort");
    return 0;
}
