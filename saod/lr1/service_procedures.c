#include <stdio.h>
#include <stdlib.h>

void FillInc(int arr[], int n)
{
    int i = 0;
    for (i; i < n; i++)
    {
        arr[i] = i + 1;
    }
}

void FillDec(int arr[], int n)
{
    int i = 0;
    for (i; i < n; i++)
    {
        arr[i] = n - i;
    }
}

void FillRand(int arr[], int n)
{
    int i = 0;
    for (i; i < n; i++)
        arr[i] = rand();
}

int CheckSum(int arr[], int n)
{
    int i = 0, sum = 0;
    for (i; i < n; i++)
        sum += arr[i];
    return sum;
}

int RunNumbers(int arr[], int n)
{
    int i = 1, numbers = 1;
    for (i; i < n; i++)
        if (arr[i] < arr[i - 1])
            numbers++;
    return numbers;
}

void PrintMass(int arr[], int n)
{
    int i = 0;
    for (i; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
