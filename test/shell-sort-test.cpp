#include "test-comum.h"
#include "../src/shell-sort.h"
#include "../src/insertion-sort.h"

/* O Shell Sort e um insertion sort com saltos: precisa ser bem melhor que o
   insertion puro no pior caso (ordem inversa). */
void teste_melhor_que_insertion() {
    const int N = 5000;

    std::vector<int> paraShell     = gerarConjuntoDeDados(N, INVERSO);
    std::vector<int> paraInsertion = paraShell;

    Estatisticas sShell, sInsertion;
    shellSort(paraShell.data(), N, sShell);
    insertionSort(paraInsertion.data(), N, sInsertion);

    assert(sShell.comparacoes < sInsertion.comparacoes);
    assert(sShell.movimentacoes < sInsertion.movimentacoes);

    std::cout << "[PASSOU] Shell(" << sShell.comparacoes
              << " comp) melhor que Insertion(" << sInsertion.comparacoes << " comp)\n";
}

/* Com a sequencia de Knuth o numero de comparacoes fica bem abaixo de n^2/4. */
void teste_ordem_de_grandeza() {
    const int N = 10000;
    std::vector<int> v = gerarConjuntoDeDados(N, ALEATORIO);

    Estatisticas stats;
    shellSort(v.data(), N, stats);

    double tetoQuadratico = 0.25 * static_cast<double>(N) * N;
    assert(static_cast<double>(stats.comparacoes) < tetoQuadratico);

    std::cout << "[PASSOU] Ordem de grandeza sub-quadratica (" << stats.comparacoes
              << " comparacoes para n=" << N << ")\n";
}

/* O ultimo passo do Shell Sort e sempre h = 1, entao o vetor tem de sair ordenado
   mesmo quando N e menor que o primeiro salto da sequencia. */
void teste_n_menor_que_o_salto() {
    for (int n = 1; n <= 20; ++n) {
        std::vector<int> v = gerarConjuntoDeDados(n, INVERSO);
        ordenarEValidar(shellSort, "n pequeno", v, false);
    }
    std::cout << "[PASSOU] N menor que o primeiro salto (n = 1 a 20)\n";
}

int main() {
    rodarBateriaComum("SHELL SORT", shellSort);

    teste_melhor_que_insertion();
    teste_ordem_de_grandeza();
    teste_n_menor_que_o_salto();

    encerrarTestes("Shell Sort");
    return 0;
}
