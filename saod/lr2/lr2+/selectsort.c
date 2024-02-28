int M, C;

void SelectSort(int arr[], int n)
{
    C = 0;
    M = 0;
    int i = 0, k = 0, j = 0, temp = 0;
    for (i; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            C++;
            if (arr[j] < arr[k])
            {
                k = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;
        M += 3;
    }
}

void UpgradeSelectSort(int arr[], int n)
{
    C = 0;
    M = 0;
    int i = 0, k = 0, j = 0, temp = 0;
    for (i; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            C++;
            if (arr[j] < arr[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
            M += 3;
        }
    }
}
