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
