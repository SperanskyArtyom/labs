//
// Created by artem on 17.03.24.
//

#include "sorts.h"

void SelectSort(int *sortArr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            if (sortArr[j] < sortArr[k])
            {
                k = j;
            }
        }
        int temp = sortArr[i];
        sortArr[i] = sortArr[k];
        sortArr[k] = temp;
    }
}

void SelectSort(float *sortArr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            if (sortArr[j] < sortArr[k])
            {
                k = j;
            }
        }
        float temp = sortArr[i];
        sortArr[i] = sortArr[k];
        sortArr[k] = temp;
    }
}

void UpgradeSelectSort(int *sortArr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            if (sortArr[j] < sortArr[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            int temp = sortArr[i];
            sortArr[i] = sortArr[k];
            sortArr[k] = temp;
        }
    }
}

void UpgradeSelectSort(float *sortArr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < size; j++)
        {
            if (sortArr[j] < sortArr[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            float temp = sortArr[i];
            sortArr[i] = sortArr[k];
            sortArr[k] = temp;
        }
    }
}

void BubbleSort(int *sortArr, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = size - 1; j > i; j--)
            if (sortArr[j] < sortArr[j - 1])
            {
                int temp = sortArr[j];
                sortArr[j] = sortArr[j - 1];
                sortArr[j - 1] = temp;
            }

}

void BubbleSort(float *sortArr, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = size - 1; j > i; j--)
            if (sortArr[j] < sortArr[j - 1])
            {
                float temp = sortArr[j];
                sortArr[j] = sortArr[j - 1];
                sortArr[j - 1] = temp;
            }
}

void ShakerSort(int *sortArr, int size)
{
    int left = 0, right = size - 1, k = right, temp;
    do
    {
        for (int j = right; j > left; j--)
        {
            if (sortArr[j] < sortArr[j - 1])
            {
                temp = sortArr[j - 1], sortArr[j - 1] = sortArr[j], sortArr[j] = temp;
                k = j;
            }
        }
        left = k;
        for (int j = left; j < right; j++)
        {
            if (sortArr[j] > sortArr[j + 1])
            {
                temp = sortArr[j], sortArr[j] = sortArr[j + 1], sortArr[j + 1] = temp;
                k = j;
            }
        }
        right = k;

    } while (left < right);
}

void ShakerSort(float *sortArr, int size)
{
    int left = 0, right = size - 1, k = right;
    float temp;
    do
    {
        for (int j = right; j > left; j--)
        {
            if (sortArr[j] < sortArr[j - 1])
            {
                temp = sortArr[j - 1], sortArr[j - 1] = sortArr[j], sortArr[j] = temp;
                k = j;
            }
        }
        left = k;
        for (int j = left; j < right; j++)
        {
            if (sortArr[j] > sortArr[j + 1])
            {
                temp = sortArr[j], sortArr[j] = sortArr[j + 1], sortArr[j + 1] = temp;
                k = j;
            }
        }
        right = k;

    } while (left < right);
}

void InsertSort(int *sortArr, int size)
{
    for (int i = 1; i < size; i++)
    {
        int temp = sortArr[i];
        int j = i - 1;
        while (j >= 0 && temp < sortArr[j])
        {
            sortArr[j + 1] = sortArr[j];
            j--;
        }
        sortArr[j + 1] = temp;
    }
}

void InsertSort(float *sortArr, int size)
{
    for (int i = 1; i < size; i++)
    {
        float temp = sortArr[i];
        int j = i - 1;
        while (j >= 0 && temp < sortArr[j])
        {
            sortArr[j + 1] = sortArr[j];
            j--;
        }
        sortArr[j + 1] = temp;
    }
}