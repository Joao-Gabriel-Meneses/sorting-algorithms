#include "tabela.h"

#include <iostream>
#include <iomanip>
#include <map>

namespace {

/* Formata numeros grandes com separador de milhar: 1234567 -> 1.234.567 */
std::string comSeparador(unsigned long long valor) {
    std::string s = std::to_string(valor);
    std::string saida;
    int contador = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        saida += s[i];
        if (++contador % 3 == 0 && i > 0) saida += '.';
    }
    return std::string(saida.rbegin(), saida.rend());
}

std::string linhaHorizontal(int largura) {
    return std::string(largura, '-');
}

} // namespace

void imprimirTabela(const std::string& titulo, const std::vector<Resultado>& linhas) {
    const int LARGURA = 78;

    std::cout << "\n" << linhaHorizontal(LARGURA) << "\n";
    std::cout << titulo << "\n";
    std::cout << linhaHorizontal(LARGURA) << "\n";

    std::cout << std::left  << std::setw(16) << "Algoritmo"
              << std::right << std::setw(18) << "Comparacoes"
              << std::right << std::setw(18) << "Movimentacoes"
              << std::right << std::setw(16) << "Tempo (ms)"
              << std::right << std::setw(10) << "Correto"
              << "\n";
    std::cout << linhaHorizontal(LARGURA) << "\n";

    for (size_t i = 0; i < linhas.size(); ++i) {
        const Resultado& r = linhas[i];
        std::cout << std::left  << std::setw(16) << r.algoritmo
                  << std::right << std::setw(18) << comSeparador(r.stats.comparacoes)
                  << std::right << std::setw(18) << comSeparador(r.stats.movimentacoes)
                  << std::right << std::setw(16) << std::fixed << std::setprecision(3)
                  << r.stats.tempoExecucao
                  << std::right << std::setw(10) << (r.ordenadoCorretamente ? "sim" : "NAO")
                  << "\n";
    }
    std::cout << linhaHorizontal(LARGURA) << "\n";

    // Destaca o mais rapido do cenario
    if (!linhas.empty()) {
        size_t melhor = 0;
        for (size_t i = 1; i < linhas.size(); ++i) {
            if (linhas[i].stats.tempoExecucao < linhas[melhor].stats.tempoExecucao) melhor = i;
        }
        std::cout << "Mais rapido: " << linhas[melhor].algoritmo << " ("
                  << std::fixed << std::setprecision(3)
                  << linhas[melhor].stats.tempoExecucao << " ms)\n";
    }
}

void imprimirMatriz(const std::string& titulo,
                    const std::vector<std::string>& cenarios,
                    const std::vector<Resultado>& linhas) {
    // Indexa os resultados por (algoritmo, cenario)
    std::map<std::string, std::map<std::string, Estatisticas> > tabela;
    std::vector<std::string> algoritmos;
    for (size_t i = 0; i < linhas.size(); ++i) {
        const Resultado& r = linhas[i];
        if (tabela.find(r.algoritmo) == tabela.end()) algoritmos.push_back(r.algoritmo);
        tabela[r.algoritmo][r.cenario] = r.stats;
    }

    const int LARGURA = 18 + static_cast<int>(cenarios.size()) * 18;

    // Uma matriz por metrica
    const char* metricas[] = { "Tempo (ms)", "Comparacoes", "Movimentacoes" };

    for (int m = 0; m < 3; ++m) {
        std::cout << "\n" << linhaHorizontal(LARGURA) << "\n";
        std::cout << titulo << " | metrica: " << metricas[m] << "\n";
        std::cout << linhaHorizontal(LARGURA) << "\n";

        std::cout << std::left << std::setw(18) << "Algoritmo";
        for (size_t c = 0; c < cenarios.size(); ++c) {
            std::cout << std::right << std::setw(18) << cenarios[c].substr(0, 17);
        }
        std::cout << "\n" << linhaHorizontal(LARGURA) << "\n";

        for (size_t a = 0; a < algoritmos.size(); ++a) {
            std::cout << std::left << std::setw(18) << algoritmos[a];
            for (size_t c = 0; c < cenarios.size(); ++c) {
                const Estatisticas& s = tabela[algoritmos[a]][cenarios[c]];
                std::cout << std::right << std::setw(18);
                if (m == 0) {
                    std::cout << std::fixed << std::setprecision(3) << s.tempoExecucao;
                } else if (m == 1) {
                    std::cout << comSeparador(s.comparacoes);
                } else {
                    std::cout << comSeparador(s.movimentacoes);
                }
            }
            std::cout << "\n";
        }
        std::cout << linhaHorizontal(LARGURA) << "\n";
    }
}
