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
    printf("Actual M = %d, actual C = %d\n", M, C);

    printf("Аrray of decreasing numbers:\n"); // Массив убывающих чисел
    FillDec(A, N);
    PrintMass(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    SelectSort(A, N);
    printf("Sorting...\n");
    PrintMass(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Theoretical M = %d, theoretical C = %d\n", 3 * (N - 1), (N * N - N) / 2);
    printf("Actual M = %d, actual C = %d\n", M, C);

    printf("Аrray of random numbers:\n"); // Массив случайных чисел
    FillRand(A, N);
    PrintMass(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    SelectSort(A, N);
    printf("Sorting...\n");
    PrintMass(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    printf("Theoretical M = %d, theoretical C = %d\n", 3 * (N - 1), (N * N - N) / 2);
    printf("Actual M = %d, actual C = %d\n", M, C);
}
