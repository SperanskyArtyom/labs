#include "heapsort.h"

#include <cmath>

int M, C;

void AddElementToHeap(int* arr, size_t L, size_t R)
{
    int x = arr[L - 1];
    M++;
    size_t i = L;
    while (true){
        size_t j = 2 * i;
        if (j > R)
            break;
        if (j < R){
            C++;
            if (arr[j] <= arr[j - 1])
                j++;
        }
        C++;
        if (x <= arr[j - 1])
            break;
        arr[i - 1] = arr[j - 1], M++;
        i = j;
    }
    arr[i - 1] = x, M++;
}

void HeapSort(int* arr, size_t size)
{
    M = C = 0;
    size_t L = floor(size / 2);
    while (L > 0){
        AddElementToHeap(arr, L, size);
        L--;
    }
    size_t R = size;
    while (R > 1){
        int temp = arr[0];
        arr[0] = arr[R - 1];
        arr[R - 1] = temp;
        M += 3;
        R--;
        AddElementToHeap(arr, 1, R);
    }
}