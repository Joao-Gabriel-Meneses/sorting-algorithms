#ifndef TABELA_H
#define TABELA_H

#include <string>
#include <vector>

#include "estatisticas.h"

/* Uma linha da tabela comparativa: o resultado de um algoritmo em um cenario. */
struct Resultado {
    std::string algoritmo;
    std::string cenario;
    int         n;
    Estatisticas stats;
    bool        ordenadoCorretamente;
};

/* Tabela de um unico cenario: coluna por metrica, uma linha por algoritmo. */
void imprimirTabela(const std::string& titulo, const std::vector<Resultado>& linhas);

/* Matriz completa: uma linha por algoritmo, uma coluna por cenario. */
void imprimirMatriz(const std::string& titulo,
                    const std::vector<std::string>& cenarios,
                    const std::vector<Resultado>& linhas);

#endif
