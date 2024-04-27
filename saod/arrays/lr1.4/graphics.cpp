#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

extern int M, C;

void T_sorts(int n, int &t1, int &t2, int &t3, int &t4)
{
    int *arr1 = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc(n * sizeof(int));
    int *arr3 = (int *)malloc(n * sizeof(int));
    int *arr4 = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr1[i] = rand();
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }
    SelectSort(arr1, n);
    t1 = M + C;
    if (M + C == 0)
        t1++;
    BubbleSort(arr2, n);
    t2 = M + C;
    if (M + C == 0)
        t2++;
    ShakerSort(arr3, n);
    t3 = M + C;
    if (M + C == 0)
        t3++;
    InsertSort(arr4, n);
    t4 = M + C;
    if (M + C == 0)
        t4++;
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
}

int main()
{
    srand(time(NULL));
    int N, T_select, T_bubble, T_shaker, T_insert;
    FILE *fp;
    char name[] = "sort.txt";
    fp = fopen(name, "w");
    for (N = 10; N <= 500; N += 10)
    {
        T_sorts(N, T_select, T_bubble, T_shaker, T_insert);
        fprintf(fp, "%d\t%d\t%d\t%d\t%d\n", N, T_select, T_bubble, T_shaker, T_insert);
    }

    fclose(fp);
    return 0;
}
