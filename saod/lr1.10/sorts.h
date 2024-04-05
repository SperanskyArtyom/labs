#pragma once

#include <cmath>

int M2, C2;

void kSort (int sortArr[], int size, int k)
{
    int temp;
    for (int i = k; i < size; i++)
    {
        M2++;
        temp = sortArr[i];
        int j = i - k;
        while (j >= 0 && ++C2 && temp < sortArr[j]) {
            sortArr[j + k] = sortArr[j], M2++;
            j = j - k;
        }
        sortArr[j + k] = temp, M2++;
    }
}

void ShellSort(int sortArr[], int size, const int H[], int m)
{
    C2 = 0, M2 = 0;
    for (int h = m - 1; h >= 0; h--)
    {
        kSort(sortArr, size, H[h]);
    }
}

int KnuthSequence(int *H , int n)
{
    int m = (int)floor(std::log2(n)) - 1;
    H[0] = 1;
    for (int i = 1; i < m; i++)
        H[i] = 2 * H[i-1] + 1;
    return m;
}

void AddElementToHeap(int* arr, size_t L, size_t R)
{
    int x = arr[L - 1];
    M2++;
    size_t i = L;
    while (true){
        size_t j = 2 * i;
        if (j > R)
            break;
        if (j < R){
            C2++;
            if (arr[j] <= arr[j - 1])
                j++;
        }
        C2++;
        if (x <= arr[j - 1])
            break;
        arr[i - 1] = arr[j - 1], M2++;
        i = j;
    }
    arr[i - 1] = x, M2++;
}

void HeapSort(int* arr, size_t size)
{
    M2 = C2 = 0;
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
        M2 += 3;
        R--;
        AddElementToHeap(arr, 1, R);
    }
}