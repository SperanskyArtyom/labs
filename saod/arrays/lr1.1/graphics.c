#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "selectsort.h"

extern int M, C;

int M_plus_C(int arr[], int n)
{
    FillRand(arr, n);
    UpgradeSelectSort(arr, n);
    return M + C;
}

int main()
{
    srand(time(NULL));
    int N, *A;

    FILE *fp;
    char name[] = "selectsort.txt";
    fp = fopen(name, "w");
    for (N = 1; N <= 2000; N++)
    {
        A = (int *)malloc(N * sizeof(int));
        fprintf(fp, "%d\t%d\n", N, M_plus_C(A, N));
        free(A);
    }

    fclose(fp);
    return 0;
}
