//
// Created by artem on 08.03.24.
//

#include "service_procedures.h"
#include <stdio.h>
#include <stdlib.h>

void FillInc(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
}

void FillDec(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }
}

void FillRand(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        arr[i] = rand();
}

long long CheckSum(int arr[], int n)
{
    int i, sum = 0;
    for (i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int RunNumbers(int arr[], int n)
{
    int i, numbers = 1;
    for (i = 1; i < n; i++)
        if (arr[i] < arr[i - 1])
            numbers++;
    return numbers;
}

void PrintMass(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}