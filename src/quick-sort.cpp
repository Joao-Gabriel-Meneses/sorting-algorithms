#include <iostream>

long long trocas = 0;

static void Particao(int v[], int esq, int dir, int *i, int *j)
{ 
   int x, w;
   *i = esq; *j = dir;
   x = v[(*i + *j)/2]; // pivo
   do
   { 
      while (x > v[*i]) (*i)++;
      while (x < v[*j]) (*j)--;
      if (*i <= *j)
      { 
         w = v[*i]; v[*i] = v[*j]; v[*j] = w;
         ++trocas;
         (*i)++; (*j)--;
      }
   } while (*i <= *j);
}

static void Ordena(int v[], int esq, int dir)
{ 
   int i, j;
   Particao(v, esq, dir, &i, &j);
   if (esq < j) Ordena(v, esq, j);
   if (i < dir) Ordena(v, i, dir);
}

void quicksort(int v[], int n)
{ if (n > 1) Ordena(v, 0, n-1); }
