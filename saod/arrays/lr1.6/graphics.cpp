#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"
#include "service_procedures.h"

extern int M, C;

void T_sorts(int n, int &t1, int &t2)
{
    int *arr = (int *)malloc(n * sizeof(int));
    FillRand(arr, n);
    InsertSort(arr, n);
    int key = rand() % n;
//    int key = 0;
    BSearch1(arr, n, arr[key]);
    t1 = C;
    BSearch2(arr, n, arr[key]);
    t2 = C;
    free(arr);
}

int main()
{
    srand(time(NULL));
    int N, T1, T2;
    FILE *fp;
    char name[] = "sort.txt";
    fp = fopen(name, "w");
    for (N = 10; N <= 2000; N += 10)
    {
        T_sorts(N, T1, T2);
        fprintf(fp, "%d\t%d\t%d\n", N, T1, T2);
    }

    fclose(fp);
    system("./graphics.gpi");
    return 0;
}
