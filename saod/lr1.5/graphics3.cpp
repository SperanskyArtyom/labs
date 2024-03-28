#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "sorts.h"

extern int M, C;

void T_sorts(int n, int &t1, int &t2)
{
    int *arr1 = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr1[i] = rand();
        arr2[i] = arr1[i];
    }
    int m1 = floor(std::log2(n)) - 1;
    int H1[m1];
    KnuthSequence(H1, n);
    ShellSort(arr1, n, H1, m1);
    t1 = M + C;
    if (M + C == 0)
        t1++;
    int m = sejsize(n);
    int H[m];
    SedgewickSequence(H, m);
    ShellSort(arr2, n, H, m);
    t2 = M + C;
    if (M + C == 0)
        t2++;
    free(arr1);
    free(arr2);
}

int main()
{
    srand(time(NULL));
    int N, T_knut, T_sedg;
    FILE *fp;
    char name[] = "sort.txt";
    fp = fopen(name, "w");
    for (N = 10; N <= 500; N += 10)
    {
        T_sorts(N, T_knut, T_sedg);
        fprintf(fp, "%d\t%d\t%d\n", N, T_knut, T_sedg);
    }

    fclose(fp);
    system("./graphics2.gpi");
    return 0;
}
