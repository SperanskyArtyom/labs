#include <stdio.h>

void Task1();
void Task2();
void ConvertToBinary(int);

int main()
{
    int N = 10, i, x, A[10] = {1, 2, 28, -28, 65, 64, -1, 13, -23, -1};
    printf("Task 1\nEnter numbers untill 0 in the end:\n");
    Task1();
    printf("\n\nTask 2\nArray:");
    for (i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\nOutput: ");
    Task2(A, N);
    printf("\n\nTask 3\nEnter x which will converted to binary: ");
    scanf("%d", &x);
    printf("\nBinary: ");
    ConvertToBinary(x);
    printf("\n");

    return 0;
}

void Task1()
{
    int x;
    scanf("%d", &x);
    if (x)
        Task1();
    if (x > 0)
        printf("%d ", x);
}

void Task2(int arr[], int N)
{
    N--;
    if (N < 0)
        return;
    if (arr[N] < 0)
        printf("%d ", arr[N]);
    Task2(arr, N);
    if (arr[N] > 0)
        printf("%d ", arr[N]);
}

void ConvertToBinary(int x)
{
    if (x / 2 == 0 && x % 2 == 0)
        return;
    ConvertToBinary(x / 2);
    printf("%d", x % 2);
}
