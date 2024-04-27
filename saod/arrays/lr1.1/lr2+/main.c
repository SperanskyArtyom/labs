#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "selectsort.h"

#define N 10
extern int M, C;
int A[N];

int main()
{
    int B[N], i = 0;
    srand(time(NULL));
    printf("Аrray of increasing numbers:\n"); // Массив возрастающих чисел
    FillInc(A, N);
    PrintMass(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    SelectSort(A, N);
    printf("Sorting...\n");
    PrintMass(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Theoretical M = %d, theoretical C = %d\n", 3 * (N - 1), (N * N - N) / 2);
    printf("Actual M = %d, actual C = %d\n\n", M, C);
    FillInc(A, N);
    printf("Upgrade sorting...\n");
    UpgradeSelectSort(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Actual M = %d, actual C = %d\n\n", M, C);

    printf("Аrray of decreasing numbers:\n"); // Массив убывающих чисел
    FillDec(A, N);
    PrintMass(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    SelectSort(A, N);
    printf("Sorting...\n");
    PrintMass(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Theoretical M = %d, theoretical C = %d\n", 3 * (N - 1), (N * N - N) / 2);
    printf("Actual M = %d, actual C = %d\n\n", M, C);
    FillDec(A, N);
    printf("Upgrade sorting...\n");
    UpgradeSelectSort(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Actual M = %d, actual C = %d\n\n", M, C);

    printf("Аrray of random numbers:\n"); // Массив случайных чисел
    FillRand(A, N);
    PrintMass(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    for (i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
    SelectSort(A, N);
    printf("Sorting...\n");
    PrintMass(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Theoretical M = %d, theoretical C = %d\n", 3 * (N - 1), (N * N - N) / 2);
    printf("Actual M = %d, actual C = %d\n\n", M, C);
    printf("Upgrade sorting...\n");
    UpgradeSelectSort(B, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(B, N), RunNumbers(B, N));
    printf("Actual M = %d, actual C = %d\n\n", M, C);
}
