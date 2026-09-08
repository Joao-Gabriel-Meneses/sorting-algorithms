#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

/* Metricas coletadas em cada execucao de um algoritmo de ordenacao.

   Convencao unica para todo o projeto (necessaria para que a tabela
   comparativa faca sentido):

   - comparacoes:   cada comparacao entre duas CHAVES do vetor conta 1.
                    Comparacoes de indice/controle de laco nao contam.
   - movimentacoes: cada COPIA de um elemento conta 1, seja para uma posicao
                    do vetor, seja para uma variavel auxiliar. Logo uma troca
                    conta 3 (temp = a; a = b; b = temp) e uma insercao conta
                    1 (guardar a chave) + os deslocamentos + 1 (gravar a chave).
   - tempoExecucao: tempo de parede da ordenacao, em milissegundos. */
struct Estatisticas {
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
    double tempoExecucao; // em milissegundos
};

inline void zerarEstatisticas(Estatisticas& stats) {
    stats.comparacoes = 0;
    stats.movimentacoes = 0;
    stats.tempoExecucao = 0.0;
}

/* Troca duas posicoes do vetor contabilizando as 3 escritas envolvidas. */
inline void trocar(int& a, int& b, Estatisticas& stats) {
    int temp = a;
    a = b;
    b = temp;
    stats.movimentacoes += 3;
}

#endif
