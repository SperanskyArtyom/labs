#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random(int N) { return rand() % N; }
void Task1();
void Task2();
void Task3();

int main()
{
    srand(time(NULL));
    printf("Task 1.\n-------\n");
    Task1();
    printf("\n\nTask 2.\n-------\n");
    Task2();
    printf("\n\nTask 3.\n-------\n");
    Task3();

    return 0;
}

void Task1()
{
    int i, n, m = 0, k = 0, j = 0, q = 0;
    int *b, *c, *d;
    printf("Input n: ");
    scanf("%d", &n);
    b = (int *)malloc(n * sizeof(int));
    if (b == NULL)
    {
        printf("Error! Memory was not allocated.\n");
        exit(-1);
    }
    for (i = 0; i < n; i++)
    {
        b[i] = random(101) - 50;
        if (b[i] < 0)
            k++;
        else if (b[i] > 0)
            m++;
    }

    c = (int *)malloc(m * sizeof(int));
    d = (int *)malloc(k * sizeof(int));
    if ((c == NULL) || (d == NULL))
    {
        printf("Error! Memory was not allocated.\n");
        exit(-1);
    }
    printf("b = { ");
    for (i = 0; i < n; i++)
    {
        if (*(b + i) > 0)
        {
            *(c + j) = *(b + i);
            j++;
        }
        else if (b[i] < 0)
        {
            d[q] = b[i];
            q++;
        }
        printf("%d ", *(b + i));
    }
    printf("}\nc = { ");
    for (i = 0; i < m; i++)
        printf("%d ", c[i]);
    printf("}\nd = { ");
    for (i = 0; i < k; i++)
        printf("%d ", d[i]);
    printf("}\n");
    free(b);
    free(c);
    free(d);
    b = NULL;
    c = NULL;
    d = NULL;
}

void Task2()
{
    int i, j, n;
    float *a, **b, *temp;
    printf("Input n: ");
    scanf("%d", &n);
    a = new float[n];
    if (a == NULL)
    {
        printf("Error! Memory was not allocated.\n");
        exit(-1);
    }
    b = new float *[n];
    if (b == NULL)
    {
        printf("Error! Memory was not allocated.\n");
        exit(-1);
    }
    for (i = 0; i < n; i++)
    {
        a[i] = (float)rand() / 1000000;
        b[i] = &a[i];
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = n - 1; j > i; j--)
        {
            if (*b[j] < *b[j - 1])
            {
                temp = b[j];
                b[j] = b[j - 1];
                b[j - 1] = temp;
            }
        }
    }
    printf("Source array: { ");
    for (i = 0; i < n; i++)
        printf("%.3f ", a[i]);
    printf("}\nSorted array: { ");
    for (i = 0; i < n; i++)
        printf("%.3f ", *b[i]);
    printf("}\n");

    delete a;
    delete b;
    a = NULL;
    b = NULL;
}

void Task3()
{
    int n, i, j, *a;
    printf("Input n: ");
    scanf("%d", &n);
    a = new int[n + 1];
    if (a == NULL)
    {
        printf("Error! Memory was not allocated.\n");
        exit(-1);
    }
    for (i = 0; i <= n; i++)
        a[i] = i;
    a[1] = 0;
    i = 2;
    while (i <= n)
    {
        if (a[i] != 0)
        {
            j = 2 * i;
            while (j <= n)
            {
                a[j] = 0;
                j += i;
            }
        }
        i++;
    }
    printf("Prime numbers in the range from 2 to N:\n");
    for (i = 0; i < n + 1; i++)
        if (a[i] != 0)
            printf("%d ", a[i]);
    printf("\n");
    delete a;
    a = NULL;
}
