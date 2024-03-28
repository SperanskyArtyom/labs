#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "bubblesort.h"

extern int M, C;

void Print_Theor_t(int n)
{
    int Ct, Mt;
    Ct = (n * n - n) / 2;
    Mt = 3 * Ct;
    printf("Average theoretical M = %d, theoretical C = %d\n", Mt / 2, Ct);
    printf("M min = %d, M max = %d\n", 0, Mt);
}

void ShowSort(int);
void PrintChar(char, int);

int main()
{
    srand(time(NULL));
    int N;
    ShowSort(100);
    // PrintChar('*', 50);
    // ShowSort(200);
    // PrintChar('*', 50);
    // ShowSort(300);
    // PrintChar('*', 50);
    // ShowSort(400);
    // PrintChar('*', 50);
    // ShowSort(500);
    getchar();
    return 0;
}

void ShowSort(int N)
{
    int *A;
    printf("n = %d\n", N);
    A = (int *)malloc(N * sizeof(int));

    printf("Аrray of increasing numbers:\n"); // Массив возрастающих чисел
    FillInc(A, N);

    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    BubbleSort(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    Print_Theor_t(N);
    printf("Actual M = %d, actual C = %d\n\n", M, C);

    printf("Аrray of decreasing numbers:\n"); // Массив убывающих чисел
    FillDec(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    BubbleSort(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    Print_Theor_t(N);
    printf("Actual M = %d, actual C = %d\n\n", M, C);

    printf("Аrray of random numbers:\n"); // Массив рандомных чисел
    FillRand(A, N);
    printf("Before sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    BubbleSort(A, N);
    printf("After sorting:\nCheck sum is %ld, number of series is %d\n", CheckSum(A, N), RunNumbers(A, N));
    Print_Theor_t(N);
    printf("Actual M = %d, actual C = %d\n\n", M, C);
}

void PrintChar(char symbol, int n)
{
    int i;
    printf("\n");
    for (i = 0; i < n + 1; i++)
        printf("%c", symbol);
    printf("\n\n");
}
