#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearBetweenMins(int *, int);
void twoDimArray(int **, int);
void rowSums(int **, int);
void FillRand(int *, int);
void ShakerSort(int *, int);
int bruteforce(int *, int, int, int &);
int binarySearch(int *, int, int, int &);

int main()
{
    srand(time(NULL));

    // Задание 1
    printf("Task 1\n\n");
    int A[10];
    printf("A: ");
    for (int i = 0; i < 10; i++)
    {
        A[i] = rand() % 100;
        printf("%d ", A[i]);
    }
    clearBetweenMins(A, 10);
    printf("\nAfter clearing A: ");
    for (int i = 0; i < 10; i++)
        printf("%d ", A[i]);

    // Задание 2
    printf("\n\nTask 2\n\n");
    int **B, m, n;
    printf("Input m: ");
    scanf("%d", &m);
    // twoDimArray(B, m);
    B = new int *[m];
    for (int i = 0; i < m; i++)
    {
        n = rand() % 9 + 2;
        B[i] = new int[n + 2];
        B[i][0] = n;
        for (int j = 1; j < n + 1; j++)
            B[i][j] = rand() % 100;
    }
    // twoDimArray(B);
    rowSums(B, m);
    printf("B:\n");
    for (int i = 0; i < m; i++)
    {
        n = B[i][0] + 2;
        for (int j = 0; j < n; j++)
            printf("%5d", B[i][j]);
        printf("\n");
    }

    // Задание 3
    printf("\n\nTask 3\n\n");
    int N = 100;
    int *C = new int[N];
    FillRand(C, N);
    ShakerSort(C, N);
    int key = C[rand() % N];
    int c, index;
    index = bruteforce(C, N, key, c);
    printf("N = %d\nBrute force.\n", N);
    printf("The index of element with value %d is %d. C = %d", key, index, c);
    printf("\nBinary search.\n");
    index = binarySearch(C, N, key, c);
    printf("The index of element with value %d is %d. C = %d", key, index, c);
    delete C;

    N = 1000;
    C = new int[N];
    FillRand(C, N);
    ShakerSort(C, N);
    key = C[rand() % N];
    index = bruteforce(C, N, key, c);
    printf("\n\nN = %d\nBrute force.\n", N);
    printf("The index of element with value %d is %d. C = %d", key, index, c);
    printf("\nBinary search.\n");
    index = binarySearch(C, N, key, c);
    printf("The index of element with value %d is %d. C = %d\n", key, index, c);
    delete C;
    return 0;
}

void clearBetweenMins(int *arr, int size)
{
    int minl = 0, minr = 1;
    for (int i = 2; i < size; i++)
        if (arr[i] <= arr[minr])
            minr = i;
    for (int i = 1; i < size; i++)
        if (arr[i] < arr[minl] && i != minr)
            minl = i;
    if (minl > minr)
    {
        int temp = minl;
        minl = minr;
        minr = temp;
    }
    for (int i = 0; i < size; i++)
        if (i > minl && i < minr)
            arr[i] = 0;
}

void twoDimArray(int **arr, int m)
{
    int n;
    for (int i = 0; i < m; i++)
    {
        n = rand() % 9 + 2;
        arr[i] = new int[n + 2];
        arr[i][0] = n;
        for (int j = 1; j < n + 1; j++)
            arr[i][j] = rand() % 100;
    }
}

void rowSums(int **arr, int m)
{
    int sum, n;
    for (int i = 0; i < m; i++)
    {
        sum = 0;
        n = arr[i][0];
        for (int j = 1; j < n + 1; j++)
            sum += arr[i][j];
        arr[i][arr[i][0] + 1] = sum;
    }
}

void FillRand(int *arr, int n)
{
    int i = 0;
    for (i; i < n; i++)
        arr[i] = rand();
}

void ShakerSort(int *arr, int size)
{
    int left = 0, right = size - 1, k = right, temp;
    while (left != right)
    {
        for (int i = right; i > left; i--)
        {
            if (arr[i] > arr[i - 1])
            {
                k = i;
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }
        left = k;
        for (int i = left; i < right; i++)
        {
            if (arr[i] < arr[i + 1])
            {
                k = i;
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        right = k;
    }
}

int bruteforce(int *arr, int size, int key, int &C)
{
    C = 0;
    for (int index = 0; index < size; index++)
    {
        C++;
        if (arr[index] == key)
            return index;
    }
    return -1;
}

int binarySearch(int *arr, int size, int key, int &C)
{
    C = 0;
    int L = 0, R = size - 1, m;
    while (L <= R)
    {
        m = (L + R) / 2;
        C++;
        if (arr[m] == key)
            return m;
        C++;
        if (arr[m] > key)
            L = m + 1;
        else
            R = m - 1;
    }
    return -1;
}
