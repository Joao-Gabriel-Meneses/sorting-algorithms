# sorting-algorithms

# Laboratório 1: Algoritmos de Ordenação

**Universidade do Estado da Bahia (UNEB)**  
**Curso:** Sistemas de Informação - DCET/1  
**Disciplina:** Estruturas de Dados II  
**Docente:** Prof. Maria Inés Restovic  

---

## Sobre o Projeto

Este projeto tem como objetivo desenvolver e consolidar os conhecimentos relacionados aos principais algoritmos de ordenação de dados. A aplicação foi desenvolvida em linguagem **C/C++** e permite a execução de testes práticos para realizar uma análise comparativa do desempenho de diferentes algoritmos. 

O foco não é apenas implementar os algoritmos, mas analisar a relação entre a **complexidade teórica** e o **comportamento observado experimentalmente** ao lidar com diferentes volumes e organizações prévias de dados.

## Objetivos
- Implementar algoritmos de ordenação clássicos sem o uso de bibliotecas prontas da linguagem.
- Coletar métricas precisas (tempo, comparações e movimentações) para cada algoritmo.
- Comparar o desempenho dos algoritmos diante de diferentes cenários de dados (aleatórios, ordenados, inversamente ordenados e parcialmente ordenados).
- Elaborar uma análise crítica baseada nos resultados experimentais e nos conceitos de complexidade ciclomática (Big-O).

## ⚙️ Algoritmos Implementados

Os seguintes métodos de ordenação foram implementados neste projeto:
1. **Selection Sort**
2. **Insertion Sort**
3. **Shell Sort**
4. **Quick Sort**
5. **Heap Sort**

## Funcionalidades do Sistema

O sistema conta com um menu interativo operado via terminal, oferecendo as seguintes funcionalidades:

- **Geração de Dados:** Permite gerar conjuntos de dados numéricos para os testes. O usuário pode definir o tamanho $N$ do vetor (sugestões: `1.000`, `10.000`, `50.000`, `100.000`).
- **Cenários de Organização:** Os dados podem ser gerados em 4 estados diferentes:
  - Totalmente Aleatórios
  - Previamente Ordenados
  - Ordem Inversa
  - Parcialmente Ordenados
- **Execução Individual ou em Lote:** O usuário pode escolher executar um algoritmo específico ou rodar todos os algoritmos sequencialmente para fins de comparação.
- **Cópia de Segurança:** Para garantir a integridade dos testes, todos os algoritmos operam sobre uma cópia exata do vetor original gerado.

## Métricas Analisadas (Instrumentação)

Para cada execução, o sistema coleta e exibe (via `struct` dedicada) as seguintes estatísticas:
- **Número de Comparações:** Quantas vezes chaves/elementos foram comparados.
- **Número de Movimentações/Trocas:** Quantas vezes os elementos mudaram de posição na memória.
- **Tempo de Execução:** Tempo real gasto para concluir a ordenação.

A saída dos resultados é apresentada em formato de tabela para facilitar a análise visual.

## Estrutura do Projeto

```
src/
  estatisticas.h      Struct Estatisticas + convencao unica de metricas
  gerador.h/.cpp      Geracao dos 4 cenarios de dados
  selection-sort.h/.cpp
  insertion-sort.h/.cpp
  shell-sort.h/.cpp
  quick-sort.h/.cpp
  heap-sort.h/.cpp
  algoritmos.h        Registro dos 5 algoritmos usado pelo menu
  tabela.h/.cpp       Impressao das tabelas e da matriz comparativa
  main.cpp            Menu interativo
test/
  test-comum.h        Bateria de testes compartilhada
  gerador-test.cpp
  selection-sort-test.cpp
  insertion-sort-test.cpp
  shell-sort-test.cpp
  quick-sort-test.cpp
  heap-sort-test.cpp
```

Todos os algoritmos expoem a mesma assinatura, o que permite ao menu trata-los
de forma uniforme:

```cpp
void nomeSort(int vetor[], int n, Estatisticas& stats);
```

## Como Compilar e Executar

```bash
make            # compila o programa principal em bin/ordenacao
make run        # compila e abre o menu interativo
make test       # compila e roda os testes de todos os modulos
make test-heap-sort   # roda apenas os testes de um algoritmo
make clean      # remove os binarios
```

## Convencao das Metricas

Para que a tabela comparativa faca sentido, os cinco algoritmos contam da mesma forma:

- **Comparacoes:** cada comparacao entre duas chaves do vetor conta 1. Comparacoes
  de indice e de controle de laco nao sao contabilizadas.
- **Movimentacoes:** cada copia de um elemento conta 1, seja para uma posicao do
  vetor, seja para uma variavel auxiliar. Uma troca conta 3.
- **Tempo:** tempo de parede da ordenacao, em milissegundos, medido dentro da
  propria funcao com `std::chrono::high_resolution_clock`.
