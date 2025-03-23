#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct tree
{
    int Data;
    int weight;
    int index;
    tree *Left = NULL;
    tree *Right = NULL;
};

int TreeSumm1(tree *p)
{
    if (p == nullptr)
        return 0;
    else
        return p->Data + TreeSumm1(p->Left) + TreeSumm1(p->Right);
}

int TreeSize1(tree *p)
{
    if (p == nullptr)
        return 0;
    else
        return TreeSize1(p->Left) + TreeSize1(p->Right) + 1;
}

int TreeHeight1(tree *p)
{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(TreeHeight1(p->Left), TreeHeight1(p->Right));
}

int sumLengthWaysTreeDOP(tree *Root, int k)
{
    int S;
    if (Root == NULL)
    {
        S = 0;
    }
    else
    {
        S = Root->weight * k + sumLengthWaysTreeDOP(Root->Left, k + 1) + sumLengthWaysTreeDOP(Root->Right, k + 1);
    }
    return S;
}

int weightTree(tree *Root)
{
    int n;
    if (Root == NULL)
    {
        n = 0;
    }
    else
    {
        n = Root->weight + weightTree(Root->Left) + weightTree(Root->Right);
    }
    return n;
}

float weightedAverageHeightTree(tree *p)
{
    if (p == NULL)
        return 0;
    else
        return (float)sumLengthWaysTreeDOP(p, 1) / weightTree(p);
}

void LefttoRight1(tree *p)
{
    if (p != NULL)
    {
        LefttoRight1(p->Left);
        cout << p->Data << " ";
        LefttoRight1(p->Right);
    }
}

void addRST_R(tree *&p, int data, int weight)
{
    if (p == NULL)
    {
        p = new tree;
        p->Data = data;
        p->weight = weight;
    }
    else if (p->Data > data)
        addRST_R(p->Left, data, weight);
    else if (data > p->Data)
        addRST_R(p->Right, data, weight);
}

void createTreeDOP(tree *&Root, int lBorder, int rBorder, int **AR, int **VW)
{
    if (lBorder < rBorder)
    {
        int k = AR[lBorder][rBorder];
        addRST_R(Root, VW[0][k], VW[1][k]);
        createTreeDOP(Root, lBorder, k - 1, AR, VW);
        createTreeDOP(Root, k, rBorder, AR, VW);
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

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
            cout << "\t";
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void eightlab()
{
    int x;
    srand(time(NULL));
    const int n = 100;
    const int n1 = 5;
    int **VandW = new int *[2];

    for (int i = 0; i < 2; i++)
    {
        VandW[i] = new int[n + 1];
        VandW[i][0] = 0;
    }

    bool table[n] = {false};
    for (int i = 1; i < n + 1; i++)
    {
        while (table[x = rand() % n])
            ;
        table[x] = true;
        VandW[0][i] = x;
    }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = n - 1 + 1; j > i; j--)
        {
            if (VandW[0][j] < VandW[0][j - 1])
            {
                swap(&VandW[0][j], &VandW[0][j - 1]);
            }
        }
    }

    for (int i = 1; i < n + 1; i++)
    {
        VandW[1][i] = rand() % n + 1;
    }

    cout << "n=9" << endl;
    int **AW1 = new int *[n1 + 1];
    int **AP1 = new int *[n1 + 1];
    int **AR1 = new int *[n1 + 1];

    for (int i = 0; i < n1 + 1; i++)
    {
        AW1[i] = new int[n1 + 1];
        AP1[i] = new int[n1 + 1];
        AR1[i] = new int[n1 + 1];
        for (int j = 0; j < n1 + 1; j++)
            AW1[i][j] = AP1[i][j] = AR1[i][j] = 0;
    }
    calculation_AW(AW1, VandW, n1 + 1);
    calculation_APandAR(AP1, AR1, AW1, n1 + 1);
    if (n1 < 26)
    {
        cout << "������� AW:" << endl;
        printSquareMatrix(AW1, n1 + 1);
        cout << "������� AP:" << endl;
        printSquareMatrix(AP1, n1 + 1);
        cout << "������� AR:" << endl;
        printSquareMatrix(AR1, n1 + 1);
    }
    cout << endl;
    // ����� ��������� ������ � �����
    short int tmp = 0;
    cout << "n=100" << endl;
    for (int i = 1; i < n + 1; i++)
    {
        cout.width(4);
        cout << VandW[0][i];
        cout << "[";
        cout.width(2);
        cout << VandW[1][i];
        cout << "]" << "  ";
        tmp++;
        if (tmp == 10)
        {
            cout << endl;
            tmp = 0;
        }
    }

    cout << endl;

    int **AW = new int *[n + 1]; // ������� �����
    int **AP = new int *[n + 1]; // ������� ���������� �����
    int **AR = new int *[n + 1]; // ������� ��������

    for (int i = 0; i < n + 1; i++)
    {
        AW[i] = new int[n + 1];
        AP[i] = new int[n + 1];
        AR[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }
    calculation_AW(AW, VandW, n + 1);
    calculation_APandAR(AP, AR, AW, n + 1);

    tree *DOP = NULL;
    createTreeDOP(DOP, 0, n, AR, VandW);
    cout << "��� (������ ��������)" << endl;
    cout << "����� ����� �������:" << endl;
    LefttoRight1(DOP);
    cout << endl
         << "������: " << TreeSize1(DOP) << endl;
    cout << "�����. �����: " << TreeSumm1(DOP) << endl;
    cout << "�����������.������: " << weightedAverageHeightTree(DOP) << endl;
    cout << "AP[0,n] / AW[0,n] = " << (double)AP[0][n] / AW[0][n] << endl;
    cout << endl
         << endl;
    printf("n=100       ������      �����. �����    ������      �����������.������\n");
    for (int q = 100; q < 101; q += 100)
    {
        cout << "���";
        cout << "\t    " << TreeSize1(DOP);
        cout << "\t         " << TreeSumm1(DOP);
        cout << "\t         " << TreeHeight1(DOP);
        cout << "\t       " << weightedAverageHeightTree(DOP);
        cout << endl;
    }
}
