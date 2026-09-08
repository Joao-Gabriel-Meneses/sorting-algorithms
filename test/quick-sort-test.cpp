#include <iostream>
#include <chrono>
#include <vector>
#include "quick-sort.cpp"

static void roda(const char *nome, const int origem[], int n)
{
    std::vector<int> v(origem, origem + n);

    trocas = 0;
    auto ini = std::chrono::steady_clock::now();
    quicksort(v.data(), n);
    auto fim = std::chrono::steady_clock::now();
    double us = std::chrono::duration<double, std::micro>(fim - ini).count();

    printf("%-5s trocas=%-5lld tempo=%8.3f us  ", nome, trocas, us);
    for (int k = 0; k < n; ++k) printf("%i ", v[k]);
    printf("\n");
}

int main() {
    int arr1[] = {0};
    int arr2[] = {33, 10, 440, 0, 100, 45};
    int arr3[] = {7, 7, 7, 7, 7};
    int arr4[] = {5, 4, 3, 2, 1};

    roda("arr1", arr1, std::size(arr1));
    roda("arr2", arr2, std::size(arr2));
    roda("arr3", arr3, std::size(arr3));
    roda("arr4", arr4, std::size(arr4));
}
