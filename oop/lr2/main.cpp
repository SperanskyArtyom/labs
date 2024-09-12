#include <iostream>
#include <iomanip>

int **genRandMatrix(int size, int maxValue);
void printMatrix(int **matrix, int size);
void print(int *arr, int size);
int *matrixToArr_a(int **matrix, int size);
int *matrixToArr_b(int **matrix, int size);
int *matrixToArr_c(int **matrix, int size);
int *matrixToArr_d(int **matrix, int size);

int main()
{
    srand(time(nullptr));
    int size = rand() % 10 + 1;
    int maxValue = 100;
    auto matrix = genRandMatrix(size, maxValue);
    int *arr;
    std::cout << "Двумерный массив:\n";
    printMatrix(matrix, size);
    std::cout << "\n\n";

    std::cout << "a) по правым диагоналям, начиная с правого верхнего элемента:\n";
    arr = matrixToArr_a(matrix, size);
    print(arr, size * size);
    std::cout << "\n\n";
    delete[] arr;

    std::cout << "b) по левым диагоналям, начиная с левого верхнего элемента:\n";
    arr = matrixToArr_b(matrix, size);
    print(arr, size * size);
    std::cout << "\n\n";
    delete[] arr;

    std::cout << "c) по спирали, начиная с центрального элемента:\n";
    arr = matrixToArr_c(matrix, size);
    print(arr, size * size);
    std::cout << "\n\n";
    delete[] arr;

    std::cout << "d) по спирали, начиная с левого верхнего элемента:\n";
    arr = matrixToArr_d(matrix, size);
    print(arr, size * size);
    std::cout << "\n\n";
    delete[] arr;

    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

int *genRandArray(int size, int maxValue)
{
    int *array = new int[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % maxValue + 1;
    }
    return array;
}

int **genRandMatrix(int size, int maxValue)
{
    int **matrix = new int *[size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = genRandArray(size, maxValue);
    }
    return matrix;
}

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout << std::setw(5) << arr[i] << '\t';
    std::cout << std::endl;
}

void printMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
        print(matrix[i], size);
}

int *matrixToArr_a(int **matrix, int size)
{
    auto arr = new int[size * size];
    int c = 0, i = 0, j = size - 1;
    while (c < size * size)
    {
        arr[c++] = matrix[i][j];
        if (i == size - 1)
            i = size - j, j = 0;
        else if (j == size - 1)
            j = size - 2 - i, i = 0;
        else
            i++, j++;
    }
    return arr;
}

int *matrixToArr_b(int **matrix, int size)
{
    auto arr = new int[size * size];
    int c = 0, i = 0, j = 0;
    while (c < size * size)
    {
        arr[c++] = matrix[i][j];
        if (i == size - 1)
            i = 1 + j, j = size - 1;
        else if (j == 0)
            j = 1 + i, i = 0;
        else
            i++, j--;
    }
    return arr;
}

int *matrixToArr_c(int **matrix, int size)
{
    auto arr = new int[size * size];
    int c = 0, i = size / 2, j = size / 2, step = 1;
    while (true)
    {
        for (int k = 0; k < step; k++)
        {
            arr[c++] = matrix[i][j];
            if (c == size * size)
                return arr;
            step % 2 == 0 ? j++ : j--;
        }
        for (int k = 0; k < step; k++)
        {
            arr[c++] = matrix[i][j];
            step % 2 == 0 ? i++ : i--;
        }
        step++;
    }
}

int *matrixToArr_d(int **matrix, int size)
{
    auto arr = new int[size * size];
    int c, i, j, step = size - 1;
    c = i = j = 0;
    for (; j < size; j++)
        arr[c++] = matrix[i][j];
    j--;
    while (step != 0)
    {
        for (int k = 0; k < step; k++)
        {
            (step - size) % 2 == 0 ? i-- : i++;
            arr[c++] = matrix[i][j];
        }
        for (int k = 0; k < step; k++)
        {
            (step - size) % 2 == 0 ? j++ : j--;
            arr[c++] = matrix[i][j];
        }
        step--;
    }
    return arr;
}
