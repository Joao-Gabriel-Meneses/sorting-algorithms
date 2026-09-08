#include "gerador.h"

#include <iostream>
#include <cstdlib>
#include <algorithm> // std::swap

const char* nomeOrganizacao(TipoOrganizacao tipo) {
    switch (tipo) {
        case ALEATORIO:             return "Aleatorio";
        case ORDENADO:              return "Ordenado";
        case INVERSO:               return "Inverso";
        case PARCIALMENTE_ORDENADO: return "Parcialmente ordenado";
    }
    return "Desconhecido";
}

std::vector<int> gerarConjuntoDeDados(int N, TipoOrganizacao tipo) {
    if (N < 0) N = 0;
    std::vector<int> vetor(N);

    switch (tipo) {
        case ORDENADO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = i + 1;
            }
            break;

        case INVERSO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = N - i;
            }
            break;

        case ALEATORIO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = std::rand() % (N > 0 ? N * 10 : 1);
            }
            break;

        case PARCIALMENTE_ORDENADO: {
            for (int i = 0; i < N; ++i) {
                vetor[i] = i + 1;
            }
            // Desordena aleatoriamente cerca de 10% das posicoes
            int numeroDeTrocas = static_cast<int>(N * 0.10);
            for (int i = 0; i < numeroDeTrocas; ++i) {
                int pos1 = std::rand() % N;
                int pos2 = std::rand() % N;
                std::swap(vetor[pos1], vetor[pos2]);
            }
            break;
        }
    }

    return vetor;
}

void exibirDados(const std::vector<int>& vetor, int limite) {
    int mostrar = static_cast<int>(vetor.size()) < limite ? static_cast<int>(vetor.size()) : limite;
    std::cout << "Primeiros " << mostrar << " de " << vetor.size() << " elementos:\n[ ";
    for (int i = 0; i < mostrar; ++i) {
        std::cout << vetor[i] << " ";
    }
    std::cout << "]\n\n";
}
