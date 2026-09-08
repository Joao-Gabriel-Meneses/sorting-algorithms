#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "estatisticas.h"
#include "selection-sort.h"
#include "insertion-sort.h"
#include "shell-sort.h"
#include "quick-sort.h"
#include "heap-sort.h"

/* Assinatura comum a todos os algoritmos do projeto. */
typedef void (*FuncaoOrdenacao)(int[], int, Estatisticas&);

struct Algoritmo {
    const char*     nome;
    FuncaoOrdenacao ordenar;
    const char*     complexidadeMedia;
    bool            quadratico; // usado para avisar sobre N grande
};

/* Ordem em que aparecem no menu e nas tabelas. */
const Algoritmo ALGORITMOS[] = {
    { "Selection Sort", selectionSort, "O(n^2)",     true  },
    { "Insertion Sort", insertionSort, "O(n^2)",     true  },
    { "Shell Sort",     shellSort,     "O(n^1.25)",  false },
    { "Quick Sort",     quickSort,     "O(n log n)", false },
    { "Heap Sort",      heapSort,      "O(n log n)", false }
};

const int TOTAL_ALGORITMOS = sizeof(ALGORITMOS) / sizeof(ALGORITMOS[0]);

#endif
