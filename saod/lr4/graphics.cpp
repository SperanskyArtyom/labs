#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

extern int M, C;

void T_sorts(int arr1[], int arr2[], int n, int &t1, int &t2)
{
    for (int i = 0; i < n; i++)
    {
        arr1[i] = rand();
        arr2[i] = arr1[i];
    }
    BubbleSort(arr1, n);
    t1 = M + C;
    ShakerSort(arr2, n);
    t2 = M + C;
    if (M + C == 0)
        t1++, t2++;
}

int main()
{
    srand(time(NULL));
    int N, *A, T1, T2, *B;

    FILE *fp;
    char name[] = "sort.txt";
    fp = fopen(name, "w");
    for (N = 1000; N <= 20000; N += 1000)
    {
        A = (int *)malloc(N * sizeof(int));
        B = (int *)malloc(N * sizeof(int));
        T_sorts(A, B, N, T1, T2);
        fprintf(fp, "%d\t%d\t%d\n", N, T1, T2);
        free(A);
        free(B);
    }

    fclose(fp);
    return 0;
}
