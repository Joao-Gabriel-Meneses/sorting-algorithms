#include "test-comum.h"
#include "../src/selection-sort.h"

/* Especifico do Selection Sort: o numero de comparacoes e SEMPRE n(n-1)/2,
   independente da organizacao da entrada. */
void teste_comparacoes_fixas() {
    const int N = 1000;
    unsigned long long esperado = static_cast<unsigned long long>(N) * (N - 1) / 2;

    const TipoOrganizacao tipos[] = { ALEATORIO, ORDENADO, INVERSO, PARCIALMENTE_ORDENADO };
    for (int t = 0; t < 4; ++t) {
        std::vector<int> v = gerarConjuntoDeDados(N, tipos[t]);
        Estatisticas stats;
        selectionSort(v.data(), N, stats);
        assert(stats.comparacoes == esperado);
    }

    std::cout << "[PASSOU] Comparacoes fixas em n(n-1)/2 = " << esperado << "\n";
}

/* Especifico do Selection Sort: no maximo n-1 trocas, ou seja 3(n-1) movimentacoes.
   E esse e justamente o ponto forte do algoritmo. */
void teste_poucas_movimentacoes() {
    const int N = 1000;

    std::vector<int> aleatorio = gerarConjuntoDeDados(N, ALEATORIO);
    Estatisticas stats;
    selectionSort(aleatorio.data(), N, stats);
    assert(stats.movimentacoes <= 3ULL * (N - 1));

    // Vetor ja ordenado nao exige nenhuma troca
    std::vector<int> ordenado = gerarConjuntoDeDados(N, ORDENADO);
    Estatisticas statsOrdenado;
    selectionSort(ordenado.data(), N, statsOrdenado);
    assert(statsOrdenado.movimentacoes == 0);

    std::cout << "[PASSOU] Movimentacoes limitadas a 3(n-1) (aleatorio="
              << stats.movimentacoes << ", ordenado=0)\n";
}

int main() {
    rodarBateriaComum("SELECTION SORT", selectionSort);

    teste_comparacoes_fixas();
    teste_poucas_movimentacoes();

    encerrarTestes("Selection Sort");
    return 0;
}
