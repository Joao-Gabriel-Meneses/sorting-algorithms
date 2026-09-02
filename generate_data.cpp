#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Necessário para std::swap

enum TipoOrganizacao {
    ALEATORIO,
    ORDENADO,
    INVERSO,
    PARCIALMENTE_ORDENADO
};

// Função que cria e RETORNA o vetor com os dados gerados
std::vector<int> gerarConjuntoDeDados(int N, TipoOrganizacao tipo) {
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
                vetor[i] = std::rand() % (N * 10);
            }
            break;
            
        case PARCIALMENTE_ORDENADO:
            for (int i = 0; i < N; ++i) {
                vetor[i] = i + 1;
            }
            // Desordena aleatoriamente cerca de 10% das posições para simular ordenação parcial
            int numeroDeTrocas = N * 0.10;
            for (int i = 0; i < numeroDeTrocas; ++i) {
                int pos1 = std::rand() % N;
                int pos2 = std::rand() % N;
                std::swap(vetor[pos1], vetor[pos2]);
            }
            break;
    }

    return vetor; 
}

void exibirDados(const std::vector<int>& vetor, int limite = 50) {
    std::cout << "Exibindo os primeiros " << limite << " elementos do vetor:\n[ ";
    for (int i = 0; i < vetor.size() && i < limite; ++i) {
        std::cout << vetor[i] << " ";
    }
    std::cout << "]\n\n";
}

int main() {
    std::srand(std::time(NULL));
    
    int N = 1000;
    
    // Gera o vetor
    std::vector<int> dadosOriginais = gerarConjuntoDeDados(N, PARCIALMENTE_ORDENADO);
    
    std::cout << "Vetor gerado com sucesso! Tamanho: " << dadosOriginais.size() << "\n\n";

    exibirDados(dadosOriginais, 50);

    std::cout << "Pressione Enter para encerrar...";
    std::cin.get(); 

    return 0;
}