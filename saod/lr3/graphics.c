#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "bubblesort.h"

extern int M, C;

int M_plus_C(int arr[], int n)
{
    FillRand(arr, n);
    BubbleSort(arr, n);
    return M + C;
}

int main()
{
    srand(time(NULL));
    int N, *A, T;

    FILE *fp;
    char name[] = "bubblesort.txt";
    fp = fopen(name, "w");
    for (N = 0; N <= 500; N += 25)
    {
        A = (int *)malloc(N * sizeof(int));
        T = M_plus_C(A, N);
        if(T == 0)
        	T++;
        fprintf(fp, "%d\t%d\n", N, T);
        free(A);
    }

    fclose(fp);
    return 0;
}
