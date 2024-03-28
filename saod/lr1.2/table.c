#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "bubblesort.h"

extern int M, C;
int T_fact[3];

void SortIntensives(int[], int);
int Theoretical_T(int);

int main()
{
    srand(time(NULL));
    int N, i, *A;

    printf("n\t  M+C\t\t    Mфакт + Сфакт\n\tтеоретич.\t Убыв.\t Случ.\tВозвр.\n");
    for (N = 100; N <= 500; N += 100)
    {
        A = (int *)malloc(N * sizeof(int));
        SortIntensives(A, N);
        printf("%d\t %d\t\t%d\t%d\t%d\n", N, Theoretical_T(N), T_fact[0], T_fact[1], T_fact[2]);
    }
    getchar();
    return 0;
}

void SortIntensives(int arr[], int n)
{
    FillDec(arr, n);
    BubbleSort(arr, n);
    T_fact[0] = M + C;
    FillRand(arr, n);
    BubbleSort(arr, n);
    T_fact[1] = M + C;
    FillInc(arr, n);
    BubbleSort(arr, n);
    T_fact[2] = M + C;
}

int Theoretical_T(int n)
{
    return 5 * (n * n - n) / 4;
}
