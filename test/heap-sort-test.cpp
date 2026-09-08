#include "test-comum.h"
#include "../src/heap-sort.h"

/* O Heap Sort NAO e adaptativo: um vetor ja ordenado continua custando
   O(n log n). Esse e um resultado importante para a analise do laboratorio. */
void teste_nao_e_adaptativo() {
    const int N = 10000;

    std::vector<int> ordenado  = gerarConjuntoDeDados(N, ORDENADO);
    std::vector<int> aleatorio = gerarConjuntoDeDados(N, ALEATORIO);

    Estatisticas sOrd, sAle;
    heapSort(ordenado.data(),  N, sOrd);
    heapSort(aleatorio.data(), N, sAle);

    // O caso ordenado nao fica barato como no Insertion Sort
    assert(sOrd.comparacoes > static_cast<unsigned long long>(N));

    // E as duas execucoes ficam na mesma ordem de grandeza (menos de 2x de diferenca)
    double razao = static_cast<double>(sOrd.comparacoes) / static_cast<double>(sAle.comparacoes);
    assert(razao > 0.5 && razao < 2.0);

    std::cout << "[PASSOU] Nao adaptativo: ordenado=" << sOrd.comparacoes
              << " vs aleatorio=" << sAle.comparacoes << " comparacoes\n";
}

/* Limite teorico: heapify faz no maximo 2 comparacoes por nivel descido,
   e sao O(n log n) descidas. 6*n*log2(n) e um teto folgado. */
void teste_limite_n_log_n() {
    const int N = 10000;
    std::vector<int> v = gerarConjuntoDeDados(N, ALEATORIO);

    Estatisticas stats;
    heapSort(v.data(), N, stats);

    double teto = 6.0 * N * std::log2(static_cast<double>(N));
    assert(static_cast<double>(stats.comparacoes) < teto);

    std::cout << "[PASSOU] Comparacoes dentro do teto O(n log n) ("
              << stats.comparacoes << " < " << static_cast<unsigned long long>(teto) << ")\n";
}

/* Verifica a fase de construcao do heap isoladamente: apos os n/2 primeiros
   heapify o vetor precisa satisfazer a propriedade de heap maximo.
   Como heapify e interno ao modulo, validamos pelo efeito: o maior elemento
   sempre termina na ultima posicao apos a ordenacao completa. */
void teste_maior_elemento_no_fim() {
    const int N = 5000;
    std::vector<int> v = gerarConjuntoDeDados(N, ALEATORIO);
    int maior = *std::max_element(v.begin(), v.end());

    Estatisticas stats;
    heapSort(v.data(), N, stats);

    assert(v[N - 1] == maior);

    std::cout << "[PASSOU] Maior elemento na ultima posicao (" << maior << ")\n";
}

/* heapify e iterativo: nao pode estourar a pilha com vetores grandes. */
void teste_vetor_grande() {
    const int N = 200000;
    std::vector<int> v = gerarConjuntoDeDados(N, INVERSO);

    Estatisticas stats;
    heapSort(v.data(), N, stats);

    assert(std::is_sorted(v.begin(), v.end()));

    std::cout << "[PASSOU] 200.000 elementos (" << stats.tempoExecucao << " ms)\n";
}

int main() {
    rodarBateriaComum("HEAP SORT", heapSort);

    teste_nao_e_adaptativo();
    teste_limite_n_log_n();
    teste_maior_elemento_no_fim();
    teste_vetor_grande();

    encerrarTestes("Heap Sort");
    return 0;
}
