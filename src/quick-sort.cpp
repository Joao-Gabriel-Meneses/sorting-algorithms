#include <iostream>

static int separa (int v[], int p, int r) {
   int c = v[r]; // pivô
   int t, j = p;
   for (int k = p; /*A*/ k < r; ++k)
      if (v[k] <= c) {
         t = v[j], v[j] = v[k], v[k] = t;
         ++j; 
      } 
   t = v[j], v[j] = v[r], v[r] = t;
   return j; 
}

void quicksort (int v[], int p, int r)
{
   if (p < r) {                   
      int j = separa (v, p, r);  
      quicksort (v, p, j-1);      
      quicksort (v, j+1, r);     
   }
}

