#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Necessário para std::swap

// Enumeração para representar as 4 situações exigidas no PDF
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
            // Dados previamente ordenados [1, 2, 3, ..., N]
            for (int i = 0; i < N; ++i) {
                vetor[i] = i + 1;
            }
            break;
            
        case INVERSO:
            // Dados em ordem inversa [N, N-1, ..., 1]
            for (int i = 0; i < N; ++i) {
                vetor[i] = N - i;
            }
            break;
            
        case ALEATORIO:
            // Dados totalmente aleatórios
            for (int i = 0; i < N; ++i) {
                vetor[i] = std::rand() % (N * 10);
            }
            break;
            
        case PARCIALMENTE_ORDENADO:
            // Primeiro gera o vetor ordenado
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

    return vetor; // Retorna o vetor gerado
}

// Função para exibir os dados (requisito do menu do PDF)
void exibirDados(const std::vector<int>& vetor, int limite = 50) {
    std::cout << "Exibindo os primeiros " << limite << " elementos do vetor:\n[ ";
    for (int i = 0; i < vetor.size() && i < limite; ++i) {
        std::cout << vetor[i] << " ";
    }
    std::cout << "]\n\n";
}

int main() {
    // Inicializa a semente para a geração de números aleatórios
    std::srand(std::time(NULL));
    
    int N = 1000;
    
    // Gera o vetor
    std::vector<int> dadosOriginais = gerarConjuntoDeDados(N, PARCIALMENTE_ORDENADO);
    
    std::cout << "Vetor gerado com sucesso! Tamanho: " << dadosOriginais.size() << "\n\n";

    // Mostra os primeiros 50 elementos para você confirmar visualmente a geração
    exibirDados(dadosOriginais, 50);

    // Pausa a tela para o console não fechar imediatamente no Windows
    std::cout << "Pressione Enter para encerrar...";
    std::cin.get(); 

    return 0;
}