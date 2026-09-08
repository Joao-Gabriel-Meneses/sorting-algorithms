#include "test-comum.h"
#include "../src/quick-sort.h"

/* Com pivo central, entradas ordenadas e inversas caem no MELHOR caso do
   Quick Sort, e nao no pior: as comparacoes ficam na ordem de n log n. */
void teste_ordenado_nao_e_pior_caso() {
    const int N = 10000;

    std::vector<int> ordenado = gerarConjuntoDeDados(N, ORDENADO);
    std::vector<int> inverso  = gerarConjuntoDeDados(N, INVERSO);

    Estatisticas sOrd, sInv;
    quickSort(ordenado.data(), N, sOrd);
    quickSort(inverso.data(),  N, sInv);

    double teto = 10.0 * N * std::log2(static_cast<double>(N));
    assert(static_cast<double>(sOrd.comparacoes) < teto);
    assert(static_cast<double>(sInv.comparacoes) < teto);

    std::cout << "[PASSOU] Ordenado/inverso nao sao pior caso (ordenado="
              << sOrd.comparacoes << ", inverso=" << sInv.comparacoes
              << " comparacoes, teto=" << static_cast<unsigned long long>(teto) << ")\n";
}

/* Vetor inteiro de valores repetidos e o caso classico que trava particoes mal
   feitas: a particao do Wirth precisa dividir o vetor mesmo assim. */
void teste_todos_iguais_em_larga_escala() {
    const int N = 20000;
    std::vector<int> v(N, 7);

    Estatisticas stats;
    quickSort(v.data(), N, stats);

    assert(std::is_sorted(v.begin(), v.end()));
    double teto = 10.0 * N * std::log2(static_cast<double>(N));
    assert(static_cast<double>(stats.comparacoes) < teto);

    std::cout << "[PASSOU] 20.000 elementos iguais (" << stats.comparacoes
              << " comparacoes)\n";
}

/* A recursao ocorre apenas na MENOR particao, entao a pilha nao pode estourar
   nem com vetores grandes ja ordenados. */
void teste_profundidade_da_pilha() {
    const int N = 200000;
    std::vector<int> v = gerarConjuntoDeDados(N, ORDENADO);

    Estatisticas stats;
    quickSort(v.data(), N, stats);

    assert(std::is_sorted(v.begin(), v.end()));

    std::cout << "[PASSOU] 200.000 elementos ordenados sem estouro de pilha ("
              << stats.tempoExecucao << " ms)\n";
}

/* O Quick Sort movimenta muito menos que os algoritmos quadraticos. */
void teste_poucas_movimentacoes() {
    const int N = 10000;
    std::vector<int> v = gerarConjuntoDeDados(N, ALEATORIO);

    Estatisticas stats;
    quickSort(v.data(), N, stats);

    assert(stats.movimentacoes < static_cast<unsigned long long>(N) * 20);

    std::cout << "[PASSOU] Movimentacoes contidas (" << stats.movimentacoes
              << " para n=" << N << ")\n";
}

int main() {
    rodarBateriaComum("QUICK SORT", quickSort);

    teste_ordenado_nao_e_pior_caso();
    teste_todos_iguais_em_larga_escala();
    teste_profundidade_da_pilha();
    teste_poucas_movimentacoes();

    encerrarTestes("Quick Sort");
    return 0;
}
