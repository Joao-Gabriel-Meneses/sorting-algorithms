#include <iostream>
#include "quick-sort.cpp"

int main() {
    int arr1[] = {0};
    int arr2[] = {33, 10, 440, 0, 100, 45};

    int len1 = std::size(arr1);
    int len2 = std::size(arr2);

    quicksort(arr1, 0, len1 - 1);
    quicksort(arr2, 0, len2 -1);

    for (int item:arr2){
        printf("%i ",item);
    }
}