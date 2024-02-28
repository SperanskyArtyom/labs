#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 5;
typedef int rown1[n];
typedef int rown2[n - 1];

void Task1();
void Task2();

int main()
{
    // srand(time(NULL));
    // printf("Task 1.\n\n");
    // Task1();
    // printf("\nTask2.\n\n");
    // Task2();

    int **A = (int **)malloc(5 * sizeof(int *));
    for (int i = 0; i < 5; i++)
    {
        A[i] = (int *)malloc(5 * sizeof(int));
    }

    return 0;
}

void Task1()
{
    int m, i, j, x, y, max = -1, max_m, max_n;
    rown1 *b;
    rown2 *c;
    printf("Input m: ");
    scanf("%d", &m);
    b = new rown1[m];
    c = new rown2[m - 1];
    if ((b == NULL) || (c == NULL))
    {
        printf("Error! Memory was not allocated.\n");
        exit(-1);
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            b[i][j] = rand() % 100;
            if (b[i][j] > max)
            {
                max = b[i][j];
                max_m = i;
                max_n = j;
            }
        }
    }

    x = 0;
    for (i = 0; i < m; i++)
    {
        y = 0;
        if (i == max_m)
            continue;
        for (j = 0; j < n; j++)
        {
            if (j == max_n)
                continue;
            c[x][y] = b[i][j];
            y++;
        }
        x++;
    }

    printf("B:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d\t", b[i][j]);
        printf("\n");
    }
    printf("C:\n");
    for (i = 0; i < m - 1; i++)
    {
        for (j = 0; j < n - 1; j++)
            printf("%d\t", c[i][j]);
        printf("\n");
    }
    delete b;
    delete c;
}

void Task2()
{
    int m, n, **A, **D, i, j;

    printf("Input m, n: ");
    scanf("%d %d", &m, &n);

    A = new int *[m];
    if (A == NULL)
    {
        printf("Не удалось выделить память");
        exit(1); // выход по ошибке, код ошибки 1
    }
    D = new int *[m + 1];
    if (D == NULL)
    {
        printf("Не удалось выделить память");
        exit(4); // выход по ошибке, код ошибки 1
    }
    for (i = 0; i < m; i++)
    {
        A[i] = new int[n];
        if (A[i] == NULL)
        {
            printf("Не удалось выделить память");
            exit(1); // выход по ошибке, код ошибки 1
        }
        D[i] = new int[n + 1];
        if (D[i] == NULL)
        {
            printf("Не удалось выделить память");
            exit(1); // выход по ошибке, код ошибки 1
        }
    }
    D[m] = new int[n + 1];
    if (D[m] == NULL)
    {
        printf("Не удалось выделить память");
        exit(1); // выход по ошибке, код ошибки 1
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            A[i][j] = rand() % 100;
            D[i][j] = A[i][j];
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            D[i][n] += D[i][j];
    }
    for (j = 0; j < n + 1; j++)
    {
        for (i = 0; i < m; i++)
            D[m][j] += D[i][j];
    }
    printf("A:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d\t", A[i][j]);
        printf("\n");
    }
    printf("D:\n");
    for (i = 0; i < m + 1; i++)
    {
        for (j = 0; j < n + 1; j++)
            printf("%d\t", D[i][j]);
        printf("\n");
    }
    for (i = 0; i < m; i++)
    {
        delete A[i];
        delete D[i];
    }
    delete A;
    delete D[m];
    delete D;
}
