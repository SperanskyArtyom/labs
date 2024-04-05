#include <cmath>
#include "shellsort.h"

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