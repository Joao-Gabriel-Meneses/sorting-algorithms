#ifndef GERADOR_H
#define GERADOR_H

#include <vector>

enum TipoOrganizacao {
    ALEATORIO,
    ORDENADO,
    INVERSO,
    PARCIALMENTE_ORDENADO
};

/* Nome legivel do cenario, usado nos cabecalhos das tabelas. */
const char* nomeOrganizacao(TipoOrganizacao tipo);

/* Cria e retorna um vetor de N elementos no cenario pedido. */
std::vector<int> gerarConjuntoDeDados(int N, TipoOrganizacao tipo);

/* Exibe os primeiros 'limite' elementos do vetor. */
void exibirDados(const std::vector<int>& vetor, int limite = 50);

#endif
