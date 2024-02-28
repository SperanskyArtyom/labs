int M, C;

void BubbleSort(int arr[], int n)
{
    C = 0;
    M = 0;
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = n - 1; j > i; j--)
        {
            C++;
            if (arr[j] < arr[j - 1])
            {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                M += 3;
            }
        }
    }
}
