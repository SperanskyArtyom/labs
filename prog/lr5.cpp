#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Task1();
void Task2();

int main()
{
    printf("Task1.\n\n");
    Task1();
    printf("\nTask2.\n\n");
    Task2();
    return 0;
}

void Task1()
{
    int *A, m, k, l, **B;

    printf("Input m: ");
    scanf("%d", &m);
    printf("Input k: ");
    scanf("%d", &k);
    if (m % k == 0)
        l = m / k;
    else
        l = m / k + 1;
    A = new int[m];
    B = new int *[l];

    printf("\nA: ");
    for (int i = 0; i < m; i++)
    {
        A[i] = rand() % 100;
        printf("%d ", A[i]);
    }

    printf("\n\nB:\n");
    int c = 0;
    for (int i = 0; i < l; i++)
    {
        B[i] = new int[k];
        for (int j = 0; j < k; j++)
        {
            if (c < m)
                B[i][j] = A[c];
            else
                B[i][j] = 0;
            c++;
            printf("%5d", B[i][j]);
        }
        printf("\n");
    }
}

void Task2()
{
    int **Table = new int *[9];

    for (int i = 0; i < 9; i++)
    {
        Table[i] = new int[i + 1];
        for (int j = 0; j < i + 1; j++)
        {
            Table[i][j] = (i + 1) * (j + 1);
            printf("%2d ", Table[i][j]);
        }
        printf("\n");
    }
}
