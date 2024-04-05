#include <cstdio>
#include <cstdlib>
#include <time.h>
#include "heapsort.h"
#include "shellsort.h"

extern int M, C, M2, C2;

void T_sorts(int n, int &t1, int &t2)
{
    int *arr1 = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr1[i] = rand();
        arr2[i] = arr1[i];
    }

    int H[n];
    int m = KnuthSequence(H, n);
    ShellSort(arr1, n, H, m);
    t1 = M2 + C2;
    if (M2 + C2 == 0)
        t1++;
    HeapSort(arr2, n);
    t2 = M + C;
    if (M + C == 0)
        t2++;
    free(arr1);
    free(arr2);
}

int main()
{
    srand(time(NULL));
    int N, T_shell, T_heap;
    FILE *fp;
    char name[] = "sort.txt";
    fp = fopen(name, "w");
    for (N = 10; N <= 500; N += 10)
    {
        T_sorts(N, T_shell, T_heap);
        fprintf(fp, "%d\t%d\t%d\n", N, T_shell, T_heap);
    }
    fclose(fp);
    system("./graphics.gpi");
    return 0;
}
