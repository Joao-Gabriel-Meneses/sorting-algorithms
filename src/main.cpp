#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "algoritmos.h"
#include "gerador.h"
#include "tabela.h"

// -------------------------------------------------------------
// Estado da sessao
// -------------------------------------------------------------
static std::vector<int>  g_dados;   // conjunto gerado atualmente
static TipoOrganizacao   g_tipo = ALEATORIO;
static int               g_n    = 0;

static const TipoOrganizacao TODOS_OS_TIPOS[] = {
    ALEATORIO, ORDENADO, INVERSO, PARCIALMENTE_ORDENADO
};
static const int TOTAL_TIPOS = 4;

// -------------------------------------------------------------
// Entrada do usuario
// -------------------------------------------------------------
static int lerInteiro(const std::string& rotulo, int minimo, int maximo) {
    int valor;
    while (true) {
        std::cout << rotulo;
        if (std::cin >> valor && valor >= minimo && valor <= maximo) {
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Valor invalido. Informe um numero entre "
                  << minimo << " e " << maximo << ".\n";
    }
}

static bool confirmar(const std::string& pergunta) {
    std::cout << pergunta << " (1 = sim, 0 = nao): ";
    int r;
    if (!(std::cin >> r)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return r == 1;
}

// -------------------------------------------------------------
// Execucao dos algoritmos
// -------------------------------------------------------------

/* Verifica se o vetor ficou em ordem crescente (validacao de cada execucao). */
static bool estaOrdenado(const std::vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i - 1] > v[i]) return false;
    }
    return true;
}

/* Roda um algoritmo sobre uma COPIA do vetor original, preservando os dados. */
static Resultado executar(const Algoritmo& alg,
                          const std::vector<int>& original,
                          const char* cenario) {
    std::vector<int> copia = original; // copia de seguranca: o original nunca e alterado

    Estatisticas stats;
    if (copia.empty()) {
        zerarEstatisticas(stats);
    } else {
        alg.ordenar(copia.data(), static_cast<int>(copia.size()), stats);
    }

    Resultado r;
    r.algoritmo = alg.nome;
    r.cenario   = cenario;
    r.n         = static_cast<int>(original.size());
    r.stats     = stats;
    r.ordenadoCorretamente = estaOrdenado(copia);
    return r;
}

/* Avisa antes de rodar algoritmos O(n^2) com N grande. */
static bool avisarSeLento(int n, bool haQuadratico) {
    if (!haQuadratico || n < 50000) return true;
    std::cout << "\nATENCAO: algoritmos O(n^2) com N = " << n
              << " podem levar varios minutos.\n";
    return confirmar("Deseja continuar mesmo assim?");
}

// -------------------------------------------------------------
// Opcoes do menu
// -------------------------------------------------------------
static void gerarDados() {
    std::cout << "\n--- Geracao de dados ---\n";
    std::cout << " Tamanhos sugeridos: 1000, 10000, 50000, 100000\n";
    g_n = lerInteiro(" Informe N (1 a 1000000): ", 1, 1000000);

    std::cout << "\n Organizacao dos dados:\n";
    for (int i = 0; i < TOTAL_TIPOS; ++i) {
        std::cout << "  " << (i + 1) << ") " << nomeOrganizacao(TODOS_OS_TIPOS[i]) << "\n";
    }
    int escolha = lerInteiro(" Escolha o cenario: ", 1, TOTAL_TIPOS);
    g_tipo = TODOS_OS_TIPOS[escolha - 1];

    g_dados = gerarConjuntoDeDados(g_n, g_tipo);

    std::cout << "\n Conjunto gerado: N = " << g_dados.size()
              << ", cenario = " << nomeOrganizacao(g_tipo) << "\n";
    exibirDados(g_dados, 20);
}

static bool exigirDados() {
    if (g_dados.empty()) {
        std::cout << "\n Nenhum conjunto de dados gerado ainda. Use a opcao 1 primeiro.\n";
        return false;
    }
    return true;
}

static void executarUmAlgoritmo() {
    if (!exigirDados()) return;

    std::cout << "\n--- Executar um algoritmo ---\n";
    for (int i = 0; i < TOTAL_ALGORITMOS; ++i) {
        std::cout << "  " << (i + 1) << ") " << ALGORITMOS[i].nome
                  << "  [" << ALGORITMOS[i].complexidadeMedia << "]\n";
    }
    int escolha = lerInteiro(" Escolha o algoritmo: ", 1, TOTAL_ALGORITMOS);
    const Algoritmo& alg = ALGORITMOS[escolha - 1];

    if (!avisarSeLento(g_n, alg.quadratico)) return;

    std::cout << "\n Executando " << alg.nome << "...\n";
    Resultado r = executar(alg, g_dados, nomeOrganizacao(g_tipo));

    std::vector<Resultado> linhas;
    linhas.push_back(r);

    std::string titulo = std::string("Resultado individual | N = ") + std::to_string(g_n)
                       + " | cenario: " + nomeOrganizacao(g_tipo);
    imprimirTabela(titulo, linhas);
}

static void executarTodosNoCenarioAtual() {
    if (!exigirDados()) return;

    if (!avisarSeLento(g_n, true)) return;

    std::vector<Resultado> linhas;
    for (int i = 0; i < TOTAL_ALGORITMOS; ++i) {
        std::cout << " Executando " << ALGORITMOS[i].nome << "...\n";
        linhas.push_back(executar(ALGORITMOS[i], g_dados, nomeOrganizacao(g_tipo)));
    }

    std::string titulo = std::string("Comparativo | N = ") + std::to_string(g_n)
                       + " | cenario: " + nomeOrganizacao(g_tipo);
    imprimirTabela(titulo, linhas);
}

static void executarMatrizCompleta() {
    std::cout << "\n--- Todos os algoritmos x todos os cenarios ---\n";
    std::cout << " Tamanhos sugeridos: 1000, 10000, 50000, 100000\n";
    int n = lerInteiro(" Informe N (1 a 1000000): ", 1, 1000000);

    if (!avisarSeLento(n, true)) return;

    std::vector<Resultado>   linhas;
    std::vector<std::string> cenarios;

    for (int t = 0; t < TOTAL_TIPOS; ++t) {
        TipoOrganizacao tipo = TODOS_OS_TIPOS[t];
        cenarios.push_back(nomeOrganizacao(tipo));

        std::vector<int> dados = gerarConjuntoDeDados(n, tipo);

        for (int i = 0; i < TOTAL_ALGORITMOS; ++i) {
            std::cout << " " << nomeOrganizacao(tipo) << " / "
                      << ALGORITMOS[i].nome << "...\n";
            linhas.push_back(executar(ALGORITMOS[i], dados, nomeOrganizacao(tipo)));
        }
    }

    // Uma tabela por cenario
    for (size_t c = 0; c < cenarios.size(); ++c) {
        std::vector<Resultado> doCenario;
        for (size_t i = 0; i < linhas.size(); ++i) {
            if (linhas[i].cenario == cenarios[c]) doCenario.push_back(linhas[i]);
        }
        imprimirTabela("Cenario: " + cenarios[c] + " | N = " + std::to_string(n), doCenario);
    }

    // E a matriz consolidada
    imprimirMatriz("Matriz comparativa | N = " + std::to_string(n), cenarios, linhas);
}

static void exibirConjuntoAtual() {
    if (!exigirDados()) return;
    std::cout << "\n Cenario: " << nomeOrganizacao(g_tipo)
              << " | N = " << g_dados.size() << "\n";
    exibirDados(g_dados, 50);
}

static void exibirMenu() {
    std::cout << "\n========================================\n";
    std::cout << " LABORATORIO 1 - ALGORITMOS DE ORDENACAO\n";
    std::cout << "========================================\n";
    if (g_dados.empty()) {
        std::cout << " Conjunto atual: (nenhum)\n";
    } else {
        std::cout << " Conjunto atual: N = " << g_dados.size()
                  << " | " << nomeOrganizacao(g_tipo) << "\n";
    }
    std::cout << "----------------------------------------\n";
    std::cout << " 1) Gerar conjunto de dados\n";
    std::cout << " 2) Executar UM algoritmo no conjunto atual\n";
    std::cout << " 3) Executar TODOS os algoritmos no conjunto atual (tabela)\n";
    std::cout << " 4) Executar TODOS os algoritmos em TODOS os cenarios (matriz)\n";
    std::cout << " 5) Exibir o conjunto atual\n";
    std::cout << " 0) Sair\n";
    std::cout << "----------------------------------------\n";
}

int main() {
    std::srand(static_cast<unsigned>(std::time(NULL)));

    while (true) {
        exibirMenu();
        int opcao = lerInteiro(" Opcao: ", 0, 5);

        switch (opcao) {
            case 1: gerarDados();                  break;
            case 2: executarUmAlgoritmo();         break;
            case 3: executarTodosNoCenarioAtual(); break;
            case 4: executarMatrizCompleta();      break;
            case 5: exibirConjuntoAtual();         break;
            case 0:
                std::cout << "\n Encerrando.\n";
                return 0;
        }
    }
}
