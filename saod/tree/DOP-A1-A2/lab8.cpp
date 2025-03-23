#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

struct tree
{
    int data;
    int weight;
    tree *left = nullptr;
    tree *right = nullptr;
};

void calculation_AW(int **AW, int **VW, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = (i + 1); j < size; j++)
        {
            AW[i][j] = AW[i][j - 1] + VW[1][j];
        }
    }
}

int sumLengthWaysTreeDOP(tree *root, int L)
{
    int S;
    if (root == nullptr)
    {
        S = 0;
    }
    else
    {
        S = root->weight * L + sumLengthWaysTreeDOP(root->left, L + 1) + sumLengthWaysTreeDOP(root->right, L + 1);
    }
    return S;
}

void outTree_ToptoBott(tree *p, bool root)
{
    if (root)
        std::cout << std::endl
                  << "▼ : ";
    if (p != nullptr)
    {
        std::cout << p->data << "; ";
        outTree_ToptoBott(p->left, 0);
        outTree_ToptoBott(p->right, 0);
    }
}

/* Вывод слева направо */
void outTree_LefttoRight(tree *p, bool root)
{
    // if (root)
    //     std::cout << std::endl << "> : ";
    if (p != nullptr)
    {
        outTree_LefttoRight(p->left, 0);
        std::cout << p->data << "\t";
        outTree_LefttoRight(p->right, 0);
    }
}

/* Вывод снизу вверх */
void outTree_BotttoTop(tree *p, bool root)
{
    if (root)
        std::cout << std::endl
                  << "▲ : ";
    if (p != nullptr)
    {
        outTree_BotttoTop(p->left, 0);
        outTree_BotttoTop(p->right, 0);
        std::cout << p->data << "; ";
    }
}

int sizeTree(tree *p, bool root)
{
    // if (root)
    //     std::cout << std::endl << "The size of the tree: ";
    if (p == nullptr)
        return 0;
    else
        return (1 + sizeTree(p->left, 0) + sizeTree(p->right, 0));
}

/* Контрольная сумма дерева */
int checkSumTree(tree *p, int sum = 0)
{
    if (p == nullptr)
        return sum;
    sum += p->weight;
    sum = checkSumTree(p->left, sum);
    sum = checkSumTree(p->right, sum);
    return sum;
}

/* Сумма длин элементов дерева */
int sumOfPathLengths(tree *p, int depth, bool root)
{
    if (root)
        std::cout << std::endl
                  << "The sum of the lengths of the paths of the tree: ";
    if (p == nullptr)
        return 0;
    else
        return (depth + sumOfPathLengths(p->left, depth + 1, 0) +
                sumOfPathLengths(p->right, depth + 1, 0));
}

int maxHeight(int a, int b)
{
    if (a < b)
        return b;
    else
        return a;
}

/* Высота дерева */
int heightTree(tree *p, bool root)
{
    // if (root)
    //     std::cout << std::endl << "The height tree: ";
    if (p == nullptr)
        return 0;
    else
        return (1 + maxHeight(heightTree(p->left, 0), heightTree(p->right, 0)));
}

/* Средняя высота дерева */
float averageHeightTree(tree *p, bool root)
{
    // if (root)
    //     std::cout << std::endl << "The average height tree: ";
    return (float(sumOfPathLengths(p, 1, 0)) / sizeTree(p, 0));
}

int weightTree(tree *root)
{
    int n;
    if (root == nullptr)
    {
        n = 0;
    }
    else
    {
        n = root->weight + weightTree(root->left) + weightTree(root->right);
    }
    return n;
}

/* Средневзвешенная высота дерева */
float weightedAverageHeightTree(tree *p, bool root)
{
    float h;
    if (root)
        // std::cout << std::endl << "The weighted average height tree: ";
        h = (float)sumLengthWaysTreeDOP(p, 1) / weightTree(p);
    return h;
}

void addRST_R(tree *&p, int data, int weight)
{
    if (p == nullptr)
    {
        p = new tree;
        p->data = data;
        p->weight = weight;
        p->left = nullptr;
        p->right = nullptr;
    }
    else if (data < p->data)
    {
        addRST_R(p->left, data, weight);
    }
    else if (data > p->data)
    { // Избегаем добавления дубликатов
        addRST_R(p->right, data, weight);
    }
}

void createTree(tree *&root, int lBorder, int rBorder, int **AR, int **VW)
{
    if (lBorder < rBorder)
    {
        int k = AR[lBorder][rBorder];
        addRST_R(root, VW[0][k], VW[1][k]);
        createTree(root, lBorder, k - 1, AR, VW);
        createTree(root, k, rBorder, AR, VW);
    }
}

void calculation_APandAR(int **AP, int **AR, int **AW, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h < size; h++)
    {
        for (int i = 0; i < size - h; i++)
        {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];
            for (int k = m + 1; k <= AR[i + 1][j]; k++)
            {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min)
                {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void printSquareMatrix(int **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout.width(5);
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void QuickSortV2(int **A, int R, int L)
{
    while (L < R)
    {
        int x = A[1][L];
        int i = L;
        int j = R;
        while (i <= j)
        {
            while (A[1][i] > x)
                i++;
            while (A[1][j] < x)
                j--;
            if (i <= j)
            {
                swap(A[0][i], A[0][j]);
                swap(A[1][i], A[1][j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i)
        {
            QuickSortV2(A, R, i);
            R = j;
        }
        else
        {
            QuickSortV2(A, j, L);
            L = i;
        }
    }
}

void A1(tree *&p, int size, int **Adata)
{
    QuickSortV2(Adata, size - 1, 0);
    for (int i = 0; i < size; i++)
    {
        addRST_R(p, Adata[0][i], Adata[1][i]);
    }
}

// void A1(tree*& p, int size, int** VW)
// {
//     // Сначала выполняем сортировку по весам в убывающем порядке
//     QuickSortV2(VW, size, 0);

//     // Добавляем вершины в дерево из отсортированного массива
//     for (int i = 0; i < size; i++) {  // Индексация исправлена
//         addRST_R(p, VW[0][i], VW[1][i]);
//     }

//     // Вывод элементов для проверки
//     short int tmp = 0;
//     std::cout << "\nЭлементы и веса после добавления в A1:\n";
//     for (int i = 0; i < size; i++) {  // Индексация исправлена
//         std::cout.width(3);
//         std::cout << VW[0][i] << "[";
//         std::cout.width(2);
//         std::cout << VW[1][i] << "]  ";
//         tmp++;
//         if (tmp == 10) {
//             std::cout << "\n";
//             tmp = 0;
//         }
//     }
//     std::cout << std::endl;
// }

void A2(tree *&p, int L, int R, int **VW)
{
    int wes = 0, sum = 0;
    if (L <= R)
    {
        int i = 0;
        for (i = L; i < R; i++)
            wes = wes + VW[1][i];

        for (i = L; i < R; i++)
        {
            if ((sum <= wes / 2) && (sum + VW[1][i] > wes / 2))
                break;
            sum = sum + VW[1][i];
        }

        addRST_R(p, VW[0][i], VW[1][i]);
        A2(p, L, i - 1, VW);
        A2(p, i + 1, R, VW);
    }
}

void func()
{
    int **VandW = new int *[2];
    const int size = 10;

    for (int i = 0; i < 2; i++)
    {
        VandW[i] = new int[size + 1];
        VandW[i][0] = 0;
    }

    bool table[2 * size] = {false};
    int x;
    for (int i = 1; i < size + 1; i++)
    {
        while (table[x = rand() % (2 * size)])
            ;
        table[x] = true;
        VandW[0][i] = x;
    }

    for (int i = 1; i < size + 1; i++)
    {
        for (int j = size - 1 + 1; j > i; j--)
        {
            if (VandW[0][j] < VandW[0][j - 1])
            {
                swap(VandW[0][j], VandW[0][j - 1]);
            }
        }
    }

    for (int i = 1; i < size + 1; i++)
    {
        VandW[1][i] = rand() % size + 1;
    }

    /*short int tmp = 0;
    for (int i = 1; i < size + 1; i++) {
        std::cout.width(3);
        std::cout << VandW[0][i];
        std::cout << "[";
        std::cout.width(2);
        std::cout << VandW[1][i];
        std::cout << "]" << "  ";
        tmp++;
        if (tmp == 10) {
            std::cout << std::endl;
            tmp = 0;
        }
    }
    std::cout << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; */

    int **AW = new int *[size + 1]; // матрица весов
    int **AP = new int *[size + 1]; // матрица взвешенных высот
    int **AR = new int *[size + 1]; // матрица индексов

    for (int i = 0; i < size + 1; i++)
    {
        AW[i] = new int[size + 1];
        AP[i] = new int[size + 1];
        AR[i] = new int[size + 1];
        for (int j = 0; j < size + 1; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }
    calculation_AW(AW, VandW, size + 1);
    calculation_APandAR(AP, AR, AW, size + 1);
    if (size < 26)
    {
        std::cout << "Матрица AW:" << std::endl;
        printSquareMatrix(AW, size + 1);
        std::cout << "Матрица AP:" << std::endl;
        printSquareMatrix(AP, size + 1);
        std::cout << "Матрица AR:" << std::endl;
        printSquareMatrix(AR, size + 1);
    }
}

void printTable(int size, int checksum, int height, double avgHeight)
{
    std::cout << std::setfill('-') << std::setw(105) << "" << std::setfill(' ') << std::endl;
    // Устанавливаем заголовок таблицы
    std::cout << std::setw(15) << "n=100"
              << std::setw(20) << "Размер"
              << std::setw(15) << "       "
              << std::setw(20) << "Контр. Сумма"
              << std::setw(20) << "Высота"
              << std::setw(15) << "       "
              << std::setw(30) << "Средневзвеш. высота"
              << std::endl;

    // Выводим разделительную линию
    std::cout << std::setfill('-') << std::setw(105) << "" << std::setfill(' ') << std::endl;

    // Выводим данные таблицы
    std::cout << std::setw(18) << "ДОП"
              << std::setw(20) << size
              << std::setw(20) << checksum
              << std::setw(20) << height
              << std::setw(30) << std::fixed << std::setprecision(4) << avgHeight
              << std::endl;
    // std::cout << std::setfill('-') << std::setw(105) << "" << std::setfill(' ') << std::endl;

    // std::cout << std::endl << std::endl;
}

void printA1Table(int size, int checksum, int height, double avgHeight)
{
    // Выводим данные таблицы
    std::cout << std::setw(15) << "A1"
              << std::setw(20) << size
              << std::setw(20) << checksum
              << std::setw(20) << height
              << std::setw(30) << std::fixed << std::setprecision(4) << avgHeight
              << std::endl;
    // std::cout << std::endl << std::endl;
}

void printA2Table(int size, int checksum, int height, double avgHeight)
{
    // Выводим данные таблицы
    std::cout << std::setw(15) << "A2"
              << std::setw(20) << size
              << std::setw(20) << checksum
              << std::setw(20) << height
              << std::setw(30) << std::fixed << std::setprecision(4) << avgHeight
              << std::endl;
    std::cout << std::setfill('-') << std::setw(105) << "" << std::setfill(' ') << std::endl;
    std::cout << std::endl
              << std::endl;
}

int main()
{
    srand(time(0));

    func();

    int **VandW = new int *[2];
    const int size = 100;

    for (int i = 0; i < 2; i++)
    {
        VandW[i] = new int[size + 1];
        VandW[i][0] = 0;
    }

    bool table[2 * size] = {false};
    int x;
    for (int i = 1; i < size + 1; i++)
    {
        while (table[x = rand() % (2 * size)])
            ;
        table[x] = true;
        VandW[0][i] = x;
    }

    for (int i = 1; i < size + 1; i++)
    {
        for (int j = size - 1 + 1; j > i; j--)
        {
            if (VandW[0][j] < VandW[0][j - 1])
            {
                swap(VandW[0][j], VandW[0][j - 1]);
            }
        }
    }

    for (int i = 1; i < size + 1; i++)
    {
        VandW[1][i] = rand() % size + 1;
    }

    int **AW = new int *[size + 1]; // матрица весов
    int **AP = new int *[size + 1]; // матрица взвешенных высот
    int **AR = new int *[size + 1]; // матрица индексов

    for (int i = 0; i < size + 1; i++)
    {
        AW[i] = new int[size + 1];
        AP[i] = new int[size + 1];
        AR[i] = new int[size + 1];
        for (int j = 0; j < size + 1; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }
    calculation_AW(AW, VandW, size + 1);
    calculation_APandAR(AP, AR, AW, size + 1);

    tree *OST = nullptr;
    createTree(OST, 0, size, AR, VandW);
    std::cout << std::endl
              << "Дерево оптимального поиска (точный алгоритм)" << std::endl;
    outTree_LefttoRight(OST, 1);
    std::cout << std::endl
              << std::endl;
    // std::cout << std::endl << "_____________________";
    // std::cout << sizeTree(OST, 1);
    // std::cout << checkSumTree(OST, 1);
    // std::cout << weightedAverageHeightTree(OST, 1) << std::endl;
    // std::cout << "AP[0,size] / AW[0,size] = " << (double)AP[0][size] / AW[0][size] << std::endl;
    std::cout << std::endl
              << std::endl;

    int sizetree = 100;

    tree *OST_A1 = nullptr;
    tree *OST_A2 = nullptr;
    A2(OST_A2, 1, size, VandW);
    A1(OST_A1, size + 1, VandW);

    std::cout << std::endl
              << "Дерево оптимального поиска (приближенный алгоритм #1)" << std::endl;
    outTree_LefttoRight(OST_A1, 1);
    // std::cout << std::endl << "_____________________";
    // std::cout << sizeTree(OST_A1, 1);
    // std::cout << checkSumTree(OST_A1, 1);
    // std::cout << weightedAverageHeightTree(OST_A1, 1) << std::endl;
    // std::cout << std::endl << std::endl;

    std::cout << std::endl
              << "\nДерево оптимального поиска (приближенный алгоритм #2)" << std::endl;
    outTree_LefttoRight(OST_A2, 1);
    // std::cout << std::endl << "_____________________";
    // std::cout << sizeTree(OST_A2, 1);
    // std::cout << checkSumTree(OST_A2, 1);
    // std::cout << weightedAverageHeightTree(OST_A2, 1) << std::endl;
    // std::cout << std::endl << std::endl;
    cout << endl
         << endl;
    printTable(sizeTree(OST, 1), checkSumTree(OST, 1), heightTree(OST, 1), (double)AP[0][size] / AW[0][size]);
    printA1Table(sizetree, checkSumTree(OST_A1, 1), heightTree(OST_A1, 1), weightedAverageHeightTree(OST_A1, 1));
    printA2Table(sizeTree(OST_A2, 1), checkSumTree(OST_A2, 1), heightTree(OST_A2, 1), weightedAverageHeightTree(OST_A2, 1));

    return 0;
}
