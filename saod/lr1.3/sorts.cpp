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

void ShakerSort(int sortArr[], int size)
{
    C = 0, M = 0;
    int left = 0, right = size - 1, k = right, temp;
    do
    {
        for (int j = right; j > left; j--)
        {
            C++;
            if (sortArr[j] < sortArr[j - 1])
            {
                temp = sortArr[j - 1], sortArr[j - 1] = sortArr[j], sortArr[j] = temp;
                M += 3;
                k = j;
            }
        }
        left = k;
        for (int j = left; j < right; j++)
        {
            C++;
            if (sortArr[j] > sortArr[j + 1])
            {
                temp = sortArr[j], sortArr[j] = sortArr[j + 1], sortArr[j + 1] = temp;
                M += 3;
                k = j;
            }
        }
        right = k;

    } while (left < right);
}
