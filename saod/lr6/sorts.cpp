//
// Created by artem on 08.03.24.
//

#include "sorts.h"
#include <cmath>

int M, C;

void SelectSort(int *sortArr, int size)
{
    C = 0;
    M = 0;
    int i, k, j, temp;
    for (i = 0; i < size - 1; i++)
    {
        k = i;
        for (j = i + 1; j < size; j++)
        {
            C++;
            if (sortArr[j] < sortArr[k])
            {
                k = j;
            }
        }
        temp = sortArr[i];
        sortArr[i] = sortArr[k];
        sortArr[k] = temp;
        M += 3;
    }
}

void UpgradeSelectSort(int *sortArr, int size)
{
    C = 0;
    M = 0;
    int i, k, j, temp;
    for (i = 0; i < size - 1; i++)
    {
        k = i;
        for (j = i + 1; j < size; j++)
        {
            C++;
            if (sortArr[j] < sortArr[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = sortArr[i];
            sortArr[i] = sortArr[k];
            sortArr[k] = temp;
            M += 3;
        }
    }
}

void BubbleSort(int *sortArr, int size)
{
    C = 0;
    M = 0;
    int i, j, temp;

    for (i = 0; i < size - 1; i++)
    {
        for (j = size - 1; j > i; j--)
        {
            C++;
            if (sortArr[j] < sortArr[j - 1])
            {
                temp = sortArr[j];
                sortArr[j] = sortArr[j - 1];
                sortArr[j - 1] = temp;
                M += 3;
            }
        }
    }
}

void ShakerSort(int sortArr[], int size)
{
    C = 0, M = 0;
    int left = 0, right = size - 1, k = right, temp;
    do
    {
        for (int j = right; j > left; j--)
        {
            C++;
            if (sortArr[j] < sortArr[j - 1])
            {
                temp = sortArr[j - 1], sortArr[j - 1] = sortArr[j], sortArr[j] = temp;
                M += 3;
                k = j;
            }
        }
        left = k;
        for (int j = left; j < right; j++)
        {
            C++;
            if (sortArr[j] > sortArr[j + 1])
            {
                temp = sortArr[j], sortArr[j] = sortArr[j + 1], sortArr[j + 1] = temp;
                M += 3;
                k = j;
            }
        }
        right = k;

    } while (left < right);
}

void InsertSort(int *sortArr, int size)
{
    C = 0, M = 0;
    int temp, i, j;
    for (i = 1; i < size; i++)
    {
        temp = sortArr[i], M++;
        j = i - 1;
        while (j >= 0 && ++C && temp < sortArr[j])
        {
            sortArr[j + 1] = sortArr[j], M++;
            j--;
        }
        sortArr[j + 1] = temp, M++;
    }
}

void kSort (int sortArr[], int size, int k)
{
    int temp;
    for (int i = k; i < size; i++)
    {
        M++;
        temp = sortArr[i];
        int j = i - k;
        while (j >= 0 && ++C && temp < sortArr[j]) {
            sortArr[j + k] = sortArr[j], M++;
            j = j - k;
        }
        sortArr[j + k] = temp, M++;
    }
}

void ShellSort(int sortArr[], int size, const int H[], int m)
{
    C = 0, M = 0;
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