#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "sorts.h"

extern int M, C;

void Print_Theor_t(int n)
{
    float Cavg, Mavg;
    int Cmax, Mmax;
    Cmax = (n * n - n) / 2;
    Cavg = (float)((n * n - n) / 2 + n - 1) / 2;
    Mmax = 3 * Cmax;
    Mavg = Mmax / 2;
    printf("Avg theoretical M = %.2f, Avg theoretical C = %.1f\n", Mavg, Cavg);
    printf("M min = %d, M max = %d\n", 0, Mmax);
    printf("C min = %d, C max = %d\n", n - 1, Cmax);
}

void ShowSort(int);
void PrintChar(char, int);

int main()
{
    srand(time(NULL));
    int N;
    printf("Проверка правильности работы алгоритма.\n\n");
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

    printf("Массив возрастающих чисел:\n"); // Массив возрастающих чисел
    FillInc(A, N);

    printf("До сортировки:\nКонтрольная сумма - %ld, число серий - %d\n", CheckSum(A, N), RunNumbers(A, N));
    InsertSort(A, N);
    printf("После сортировки:\nКонтрольная сумма - %ld, число серий - %d\n\n", CheckSum(A, N), RunNumbers(A, N));
    // Print_Theor_t(N);
    printf("Actual M = %d, actual C = %d\n\n", M, C);

    printf("Массив убывающих чисел:\n"); // Массив убывающих чисел
    FillDec(A, N);
    printf("До сортировки:\nКонтрольная сумма - %ld, число серий - %d\n", CheckSum(A, N), RunNumbers(A, N));
    InsertSort(A, N);
    printf("После сортировки:\nКонтрольная сумма - %ld, число серий - %d\n\n", CheckSum(A, N), RunNumbers(A, N));
    // Print_Theor_t(N);
    printf("Actual M = %d, actual C = %d\n\n", M, C);

    printf("Массив случайных чисел:\n"); // Массив рандомных чисел
    FillRand(A, N);
    printf("До сортировки:\nКонтрольная сумма - %ld, число серий - %d\n", CheckSum(A, N), RunNumbers(A, N));
    InsertSort(A, N);
    printf("После сортировки:\nКонтрольная сумма - %ld, число серий - %d\n\n", CheckSum(A, N), RunNumbers(A, N));
    // Print_Theor_t(N);
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
