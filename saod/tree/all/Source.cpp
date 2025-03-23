#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <algorithm>
int MAX_RAND = 100;
int M = 0, C = 0;
const int Size = 100;

using namespace std;

void print_menu()
{
    system("cls");
    setlocale(LC_ALL, "ru");
    printf("�������� ��, ��� �����\n");
    printf("1. ���� 1\n");
    printf("2. ���� 2-3\n");
    printf("3. ���� 4\n");
    printf("4. ���� 5\n");
    printf("5. ���� 6\n");
    printf("6. ���� 7\n");
    printf("7. ���� 8\n");
    printf("8. ���� 9\n");
    printf("9. �����\n");
    printf(">");
}

int get_variant(int count)
{
    int variant;
    char s[100];
    cin >> s;
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count)
    {
        cout << "������������ ����: ���������� ��� ��� " << endl;
        cin >> s;
    }

    return variant;
}

struct Vertex
{
    int Data;
    Vertex *Left;
    Vertex *Right;
    int index;
    int balance;
    int Height;
    int weight;
};

struct tree
{
    int Data;
    int weight;
    int index;
    tree *Left = NULL;
    tree *Right = NULL;
};

int SummWays(Vertex *p, int L)
{
    if (p == nullptr)
        return 0;
    else
        return L + SummWays(p->Left, L + 1) + SummWays(p->Right, L + 1);
}

int TreeSize(Vertex *p)
{
    if (p == nullptr)
        return 0;
    else
        return TreeSize(p->Left) + TreeSize(p->Right) + 1;
}

int TreeSize1(tree *p)
{
    if (p == nullptr)
        return 0;
    else
        return TreeSize1(p->Left) + TreeSize1(p->Right) + 1;
}

int TreeSumm(Vertex *p)
{
    if (p == nullptr)
        return 0;
    else
        return p->Data + TreeSumm(p->Left) + TreeSumm(p->Right);
}

int TreeHeight(Vertex *p)
{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(TreeHeight(p->Left), TreeHeight(p->Right));
}

int TreeSumm1(tree *p)
{
    if (p == nullptr)
        return 0;
    else
        return p->Data + TreeSumm1(p->Left) + TreeSumm1(p->Right);
}

int TreeHeight1(tree *p)
{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(TreeHeight1(p->Left), TreeHeight1(p->Right));
}

double AveregeHeight(Vertex *root)
{
    return double(SummWays(root, 1)) / double(TreeSize(root));
}

void Obhod1(Vertex *p)
{
    if (p == nullptr)
        return;
    printf("%d ", p->Data);
    Obhod1(p->Left);
    Obhod1(p->Right);
}

void Obhod2(Vertex *p)
{
    if (p == nullptr)
        return;
    Obhod2(p->Left);
    printf("%d ", p->Data);
    Obhod2(p->Right);
}

void Obhod3(Vertex *p)
{
    if (p == nullptr)
        return;
    Obhod3(p->Left);
    Obhod3(p->Right);
    printf("%d ", p->Data);
}

void LefttoRight(Vertex *p)
{
    if (p != NULL)
    {
        LefttoRight(p->Left);
        cout << "(" << p->index << ":" << p->Data << ") ";
        LefttoRight(p->Right);
    }
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

void PrintInfo(Vertex *p, Vertex *root)
{
    cout << fixed;
    cout << setprecision(2);
    cout << endl;
    cout << "������ ������ \t ����������� ����� \t C���� ����� ����� \t������ ������\t������� ������ ������" << endl;
    cout << "   " << TreeSize(p) << "\t\t      " << TreeSumm(p) << "\t\t      " << SummWays(p, 1) << "\t\t\t" << TreeHeight(p) << "\t\t" << AveregeHeight(root);
    cout << endl;
}

void FillRand(int A[], int n)
{
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }

    random_shuffle(A, A + n);

    for (int i = 0; i < n; i++)
    {
        A[i] = A[i] % MAX_RAND;
    }
}

void pinning_index(Vertex *root)
{
    if (root == NULL)
    {
        return;
    }

    int currentID = 1;
    queue<Vertex *> q;
    q.push(root);

    while (!q.empty())
    {
        int level_size = q.size();

        for (int i = 0; i < level_size; i++)
        {
            Vertex *current = q.front();
            q.pop();

            current->index = currentID++;

            if (current->Left != NULL)
            {
                q.push(current->Left);
            }
            if (current->Right != NULL)
            {
                q.push(current->Right);
            }
        }
    }
}

void sdp1(int d, Vertex *&Root)
{ // �� ���

    Vertex **p = &Root;

    while (*p != NULL)
    {

        if (d < (*p)->Data)
            p = &((*p)->Left);
        else if (d > (*p)->Data)
            p = &((*p)->Right);
        else
            break;
    }
    if (*p == NULL)
    {
        *p = new Vertex;
        (*p)->Data = d;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
    }
}

void sdp2(int d, Vertex *&p) // ������
{
    if (p == NULL)
    {
        p = new Vertex;
        p->Data = d;
        p->Left = NULL;
        p->Right = NULL;
    }
    else if (d < p->Data)
        sdp2(d, p->Left);
    else if (d > p->Data)
        sdp2(d, p->Right);
}

Vertex *ISDP(int L, int R, int *arr)
{
    int m;
    if (L > R)
        return 0;
    else
    {
        m = ((L + R) / 2);
        Vertex *p = new Vertex;
        p->Data = arr[m];
        p->Left = ISDP(L, m - 1, arr);
        p->Right = ISDP(m + 1, R, arr);
        return p;
    }
}
// LL
void LL(Vertex *&p)
{
    Vertex *q = p->Left;
    p->balance = 0;
    q->balance = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}
// RR
void RR(Vertex *&p)
{
    Vertex *q = p->Right;
    p->balance = 0;
    q->balance = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}
// LR
void LR(Vertex *&p)
{
    Vertex *q = p->Left;
    Vertex *r = q->Right;
    if (r->balance < 0)
        p->balance = 1;
    else
        p->balance = 0;

    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;

    r->balance = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}
// RL
void RL(Vertex *&p)
{
    Vertex *q = p->Right;
    Vertex *r = q->Left;
    if (r->balance > 0)
        p->balance = -1;
    else
        p->balance = 0;

    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;

    r->balance = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Right = q;
    r->Left = p;
    p = r;
}

void LL1(Vertex *&p, bool &ymen)
{
    Vertex *q = p->Left;
    if (q->balance = 0)
    {
        q->balance = 1;
        p->balance = -1;
        ymen = false;
    }
    else
    {
        q->balance = 0;
        p->balance = 0;
    }
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

void RR1(Vertex *&p, bool &ymen)
{
    Vertex *q = p->Right;
    if (q->balance = 0)
    {
        q->balance = 1;
        p->balance = 1;
        ymen = false;
    }
    else
    {
        q->balance = 0;
        p->balance = 0;
    }
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void BL(Vertex *&p, bool &ymen)
{
    if (p->balance = -1)
    {
        p->balance = 0;
    }
    else if (p->balance = 0)
    {
        p->balance = 1;
        ymen = false;
    }
    else if (p->balance = 1)
    {
        if (p->Right->balance >= 0)
        {
            RR1(p, ymen);
        }
        else
            RL(p);
    }
}

void BR(Vertex *&p, bool &ymen)
{
    if (p->balance = 1)
    {
        p->balance = 0;
    }
    else if (p->balance = 0)
    {
        p->balance = -1;
        ymen = false;
    }
    else if (p->balance = -1)
    {
        if (p->Left->balance <= 0)
        {
            LL1(p, ymen);
        }
        else
            LR(p);
    }
}

void addAVL(Vertex *&p, int d, bool &rost)
{
    if (p == NULL)
    {
        p = new Vertex;
        p->Data = d;
        p->Left = NULL;
        p->Right = NULL;
        p->balance = 0;
        rost = true;
    }
    else if (p->Data > d)
    {
        addAVL(p->Left, d, rost);
        if (rost == true)
        {
            if (p->balance > 0)
            {
                p->balance = 0;
                rost = false;
            }
            else if (p->balance == 0)
            {
                p->balance = -1;
                rost = true;
            }
            else
            {
                if (p->Left->balance < 0)
                {
                    LL(p);
                    rost = false;
                }
                else
                {
                    LR(p);
                    rost = false;
                }
            }
        }
    }
    else if (p->Data < d)
    {
        addAVL(p->Right, d, rost);
        if (rost == true)
        {
            if (p->balance < 0)
            {
                p->balance = 0;
                rost = false;
            }
            else if (p->balance == 0)
            {
                p->balance = 1;
                rost = true;
            }
            else
            {
                if (p->Right->balance > 0)
                {
                    RR(p);
                    rost = false;
                }
                else
                {
                    RL(p);
                    rost = false;
                }
            }
        }
    }
}

bool DeleteSDP(int D, Vertex *&Root)
{
    Vertex **p = &Root;

    while (*p != NULL)
    {
        if (D < (*p)->Data)
            p = &((*p)->Left);
        else if (D > (*p)->Data)
            p = &((*p)->Right);
        else
            break;
    }

    if (*p == NULL)
    {
        cout << "������ ��� � ������" << endl;
        return false;
    }

    if (*p != NULL)
    {
        Vertex *q = *p;

        if (q->Left == NULL)
            *p = q->Right;
        else if (q->Right == NULL)
            *p = q->Left;
        else
        {
            Vertex *r = q->Left;
            Vertex *S = q;

            if (r->Right == NULL)
            {
                r->Right = q->Right;
                *p = r;
            }
            else
            {
                while (r->Right != NULL)
                {
                    S = r;
                    r = r->Right;
                }
                S->Right = r->Left;
                r->Left = q->Left;
                r->Right = q->Right;
                *p = r;
            }
        }
        delete q;
        return true;
    }
    return false;
}

void del(Vertex *&r, Vertex *&q, bool &ymen)
{
    if (r->Right != NULL)
    {
        del(r->Right, q, ymen);
        if (ymen = true)
        {
            BR(r, ymen);
        }
    }
    else
    {
        q->Data = r->Data;
        q = r;
        r = r->Left;
        ymen = true;
    }
}

bool DeleteAVL(int x, Vertex *&p, bool &ymen)
{
    Vertex *q = NULL;
    if (p == NULL)
    {
        cout << "������ ��� � ������" << endl;
        return 1;
    }
    else if (p->Data > x)
    {
        DeleteAVL(x, p->Left, ymen);
        if (ymen = true)
        {
            BL(p, ymen);
        }
    }
    else if (p->Data < x)
    {
        if (DeleteAVL(x, p->Right, ymen))
        {
            return 1;
        }
        if (ymen = true)
        {
            BR(p, ymen);
        }
    }
    else
    {
        q = p;
        if (q->Left == NULL)
        {
            p = q->Right;
            ymen = true;
        }
        else if (q->Right == NULL)
        {
            p = q->Left;
            ymen = true;
        }
        else
        {
            del(q->Left, q, ymen);
            if (ymen = true)
            {
                BL(p, ymen);
            }
        }
        delete (q);
        return true;
    }
    return false;
}

int height(Vertex *N)
{
    return (N == NULL) ? 0 : N->Height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Vertex *newVertex(int data)
{
    Vertex *node = new Vertex();
    node->Data = data;
    node->Left = NULL;
    node->Right = NULL;
    node->Height = 1;
    return node;
}

Vertex *rightRotate(Vertex *y)
{
    Vertex *x = y->Left;
    Vertex *T2 = x->Right;

    x->Right = y;
    y->Left = T2;

    y->Height = max(height(y->Left), height(y->Right)) + 1;
    x->Height = max(height(x->Left), height(x->Right)) + 1;

    return x;
}

Vertex *leftRotate(Vertex *x)
{
    Vertex *y = x->Right;
    Vertex *T2 = y->Left;

    y->Left = x;
    x->Right = T2;

    x->Height = max(height(x->Left), height(x->Right)) + 1;
    y->Height = max(height(y->Left), height(y->Right)) + 1;

    return y;
}

int getBalance(Vertex *N)
{
    return (N == NULL) ? 0 : height(N->Left) - height(N->Right);
}

Vertex *insert(Vertex *node, int data)
{
    if (node == NULL)
        return newVertex(data);

    if (data < node->Data)
        node->Left = insert(node->Left, data);
    else if (data > node->Data)
        node->Right = insert(node->Right, data);
    else
        return node;

    node->Height = 1 + max(height(node->Left), height(node->Right));
    int balance = getBalance(node);

    if (balance > 1 && data < node->Left->Data)
        return rightRotate(node);

    if (balance < -1 && data > node->Right->Data)
        return leftRotate(node);

    if (balance > 1 && data > node->Left->Data)
    {
        node->Left = leftRotate(node->Left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->Right->Data)
    {
        node->Right = rightRotate(node->Right);
        return leftRotate(node);
    }

    return node;
}

Vertex *minValueNode(Vertex *node)
{
    Vertex *current = node;
    while (current->Left != NULL)
        current = current->Left;
    return current;
}

Vertex *deleteNode(Vertex *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->Data)
        root->Left = deleteNode(root->Left, data);
    else if (data > root->Data)
        root->Right = deleteNode(root->Right, data);
    else
    {
        if ((root->Left == NULL) || (root->Right == NULL))
        {
            Vertex *temp = root->Left ? root->Left : root->Right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            Vertex *temp = minValueNode(root->Right);
            root->Data = temp->Data;
            root->Right = deleteNode(root->Right, temp->Data);
        }
    }

    if (root == NULL)
        return root;

    root->Height = 1 + max(height(root->Left), height(root->Right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->Left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->Left) < 0)
    {
        root->Left = leftRotate(root->Left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->Right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->Right) > 0)
    {
        root->Right = rightRotate(root->Right);
        return leftRotate(root);
    }

    return root;
}

void inOrderTraversal(Vertex *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->Left);
        cout << root->Data << " ";
        inOrderTraversal(root->Right);
    }
}

bool VR = true;
bool HR = true;

void B2INSERT(int D, Vertex *&p, bool &VR, bool &HR)
{
    if (p == NULL)
    {
        p = new Vertex;
        p->Data = D;
        p->Left = NULL;
        p->Right = NULL;
        p->balance = 0;
        VR = true;
    }
    else if (p->Data > D)
    {
        B2INSERT(D, p->Left, VR, HR);
        if (VR)
        {
            if (p->balance == 0)
            {
                Vertex *q = p->Left;
                p->Left = q->Right;
                q->Right = p;
                p = q;
                q->balance = 1;
                VR = false;
                HR = true;
            }
            else
            {
                p->balance = 0;
                VR = true;
                HR = false;
            }
        }
        else
        {
            HR = false;
        }
    }
    else if (p->Data < D)
    {
        B2INSERT(D, p->Right, VR, HR);
        if (VR)
        {
            p->balance = 1;
            HR = true;
            VR = false;
        }
        else if (HR)
        {
            if (p->balance == 1)
            {
                Vertex *q = p->Right;
                p->balance = 0;
                q->balance = 0;
                p->Right = q->Left;
                q->Left = p;
                p = q;
                VR = true;
                HR = false;
            }
            else
            {
                HR = false;
            }
        }
    }
}

int countLevels(Vertex *Ptr)
{
    if (Ptr == NULL)
    {
        return 0;
    }
    return 1 + max(countLevels(Ptr->Left), countLevels(Ptr->Right));
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// ���������� ������� ����� AW
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

// ���������� ������� ���������� ����� (AP) � ������� �������� (AR)
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

// Wn*hn
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

// ��� ������ W
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

// ���������������� ������ ������
float weightedAverageHeightTree(tree *p)
{
    if (p == NULL)
        return 0;
    else
        return (float)sumLengthWaysTreeDOP(p, 1) / weightTree(p);
}

// ���������� ������� ������� ������� ��������
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

int sumOfPathLengths(tree *p, int depth)
{
    if (p == NULL)
        return 0;
    else
        return (depth + sumOfPathLengths(p->Left, depth + 1) +
                sumOfPathLengths(p->Right, depth + 1));
}

void A1(tree *&p, int size, int **VW)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            if (VW[1][j] > VW[1][j - 1])
            {
                swap(VW[0][j], VW[0][j - 1]);
                swap(VW[1][j], VW[1][j - 1]);
            }
        }
    }
    for (int i = 1; i < size; i++)
    {
        addRST_R(p, VW[0][i], VW[1][i]);
    }
}

void A2(tree *&p, int left, int right, int **VW)
{
    int wes = 0, sum = 0;
    if (left <= right)
    {
        int i = 0;
        for (i = left; i < right; i++)
            wes = wes + VW[1][i];

        for (i = left; i < right; i++)
        {
            if ((sum <= wes / 2) && (sum + VW[1][i] > wes / 2))
                break;
            sum = sum + VW[1][i];
        }

        addRST_R(p, VW[0][i], VW[1][i]);
        A2(p, left, i - 1, VW);
        A2(p, i + 1, right, VW);
    }
}

void A1_print(tree *&p, int size, int **VW)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            if (VW[1][j] > VW[1][j - 1])
            {
                swap(VW[0][j], VW[0][j - 1]);
                swap(VW[1][j], VW[1][j - 1]);
            }
        }
    }

    short int tmp = 0;
    for (int i = 1; i < size; i++)
    {
        cout.width(3);
        cout << VW[0][i];
        cout << "[";
        cout.width(2);
        cout << VW[1][i];
        cout << "]" << "  ";
        tmp++;
        if (tmp == 10)
        {
            cout << endl;
            tmp = 0;
        }
    }

    for (int i = 1; i < size; i++)
    {
        addRST_R(p, VW[0][i], VW[1][i]);
    }
}

void A2_print(tree *&p, int left, int right, int **VW)
{
    int wes = 0, sum = 0;
    if (left <= right)
    {
        int i = 0;
        for (i = left; i < right; i++)
            wes = wes + VW[1][i];

        for (i = left; i < right; i++)
        {
            if ((sum <= wes / 2) && (sum + VW[1][i] > wes / 2))
                break;
            sum = sum + VW[1][i];
        }

        short int tmp = 0;
        for (int i = 1; i < Size + 1; i++)
        {
            cout.width(3);
            cout << VW[0][i];
            cout << "[";
            cout.width(2);
            cout << VW[1][i];
            cout << "]" << "  ";
            tmp++;
            if (tmp == 10)
            {
                cout << endl;
                tmp = 0;
            }
        }

        addRST_R(p, VW[0][i], VW[1][i]);
        A2(p, left, i - 1, VW);
        A2(p, i + 1, right, VW);
    }
}

void firstlab()
{

    Vertex *Root = new Vertex{1, nullptr, nullptr};

    Root->Left = new Vertex{2, nullptr, nullptr};

    Root->Right = new Vertex{3, nullptr, nullptr};

    Root->Left->Left = new Vertex{4, nullptr, nullptr};

    Root->Right->Right = new Vertex{5, nullptr, nullptr};

    Root->Left->Left->Right = new Vertex{6, nullptr, nullptr};

    cout << "����� ������ ����" << endl;
    Obhod1(Root);
    cout << "\n"
         << endl;
    cout << "����� ����� �������" << endl;
    Obhod2(Root);
    cout << "\n"
         << endl;
    cout << "����� ����� �����" << endl;
    Obhod3(Root);
    cout << "\n"
         << endl;
    SummWays(Root, 1);
    TreeSize(Root);
    TreeSumm(Root);
    TreeHeight(Root);
    AveregeHeight(Root);
    PrintInfo(Root, Root);
}

void secthreeLab()
{
    const int n = 100;
    int *A = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }
    cout << "����" << endl;
    Vertex *root = ISDP(0, n - 1, A);
    pinning_index(root);
    LefttoRight(root);
    SummWays(root, 1);
    TreeSize(root);
    TreeSumm(root);
    TreeHeight(root);
    AveregeHeight(root);
    PrintInfo(root, root);

    cout << endl;

    cout << "��� ������� �����������" << endl;
    Vertex *Root = NULL;
    FillRand(A, 100);
    for (int i = 0; i < n; i++)
    {
        sdp1(A[i], Root);
    }
    pinning_index(Root);
    LefttoRight(Root);
    SummWays(Root, 1);
    TreeSize(Root);
    TreeSumm(Root);
    TreeHeight(Root);
    AveregeHeight(Root);
    PrintInfo(Root, Root);

    cout << endl;

    cout << "��� ���������" << endl;
    Vertex *Root1 = NULL;
    for (int i = 0; i < n; i++)
    {
        sdp2(A[i], Root1);
    }
    pinning_index(Root1);
    LefttoRight(Root1);
    SummWays(Root1, 1);
    TreeSize(Root1);
    TreeSumm(Root1);
    TreeHeight(Root1);
    AveregeHeight(Root1);
    PrintInfo(Root1, Root1);

    cout << endl;

    printf("n=100       ������      �����. �����    ������      �����.������\n");
    for (int q = 100; q < 101; q += 100)
    {
        cout << "����";
        cout << "\t    " << TreeSize(root);
        cout << "\t         " << TreeSumm(root);
        cout << "\t         " << TreeHeight(root);
        cout << "\t       " << AveregeHeight(root);
        cout << endl;
        cout << "���1";
        cout << "\t    " << TreeSize(Root);
        cout << "\t         " << TreeSumm(Root);
        cout << "\t         " << TreeHeight(Root);
        cout << "\t       " << AveregeHeight(Root);
        cout << endl;
        cout << "���2";
        cout << "\t    " << TreeSize(Root1);
        cout << "\t         " << TreeSumm(Root1);
        cout << "\t         " << TreeHeight(Root1);
        cout << "\t       " << AveregeHeight(Root1);
        cout << endl;
    }
}

void fourthLab()
{
    const int N = 10;
    int *A = new int[N];
    Vertex *root = NULL;
    for (int i = 0; i < N; i++)
    {
        A[i] = rand() % 100;
        sdp1(A[i], root);
    }
    cout << "���: ";
    Obhod1(root);
    cout << endl;
    int delData;
    for (int i = 0; i < N;)
    {
        cout << "������� ������� ��� ��������: ";
        cin >> delData;
        if (DeleteSDP(delData, root))
            ++i;
        cout << "���: ";
        Obhod1(root);
        cout << endl;
    }
}

void fifthLab()
{
    const int n = 100;
    int *A = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }
    cout << "����" << endl;
    Vertex *root = ISDP(0, n - 1, A);
    pinning_index(root);
    LefttoRight(root);
    SummWays(root, 1);
    TreeSize(root);
    TreeSumm(root);
    TreeHeight(root);
    AveregeHeight(root);
    PrintInfo(root, root);

    cout << endl;

    cout << "���" << endl;
    Vertex *Root = NULL;
    bool rost = false;
    FillRand(A, 100);
    for (int i = 0; i < n; i++)
    {
        addAVL(Root, A[i], rost);
    }
    pinning_index(Root);
    LefttoRight(Root);
    SummWays(Root, 1);
    TreeSize(Root);
    TreeSumm(Root);
    TreeHeight(Root);
    AveregeHeight(Root);
    PrintInfo(Root, Root);

    cout << endl;

    printf("n=100       ������      �����. �����    ������      �����.������\n");
    for (int q = 100; q < 101; q += 100)
    {
        cout << "����";
        cout << "\t    " << TreeSize(root);
        cout << "\t         " << TreeSumm(root);
        cout << "\t         " << TreeHeight(root);
        cout << "\t       " << AveregeHeight(root);
        cout << endl;
        cout << "���";
        cout << "\t    " << TreeSize(Root);
        cout << "\t         " << TreeSumm(Root);
        cout << "\t         " << TreeHeight(Root);
        cout << "\t       " << AveregeHeight(Root);
        cout << endl;
    }
}

void sixlab()
{
    bool rost = false;
    const int N = 10;
    int *A = new int[N];
    Vertex *root = NULL;
    for (int i = 0; i < N; i++)
    {
        A[i] = rand() % 100;
        addAVL(root, A[i], rost);
    }
    cout << "���: ";
    Obhod1(root);
    cout << endl;
    int delData;
    bool ymen;
    for (int i = 0; i < N;)
    {
        cout << "������� ������� ��� ��������: ";
        cin >> delData;
        ymen = false;
        if (DeleteAVL(delData, root, ymen))
            ++i;
        cout << "���: ";
        Obhod1(root);
        cout << endl;
    }
}

void sevenlab()
{
    const int n = 100;
    int *A = new int[n];
    srand(time(NULL));

    Vertex *root = nullptr;
    bool VR = true, HR = true;

    cout << "\n ���" << endl;

    // ���������� ������� ���������� ������� � ������� � ������
    FillRand(A, 100);
    for (int i = 0; i < n; i++)
    {
        B2INSERT(A[i], root, VR, HR);
    }

    cout << " ����� ������: ";
    inOrderTraversal(root);
    cout << endl;

    cout << "\n ���" << endl;
    Vertex *Root = NULL;
    bool rost = false;
    FillRand(A, 100);
    for (int i = 0; i < n; i++)
    {
        addAVL(Root, A[i], rost);
    }
    pinning_index(Root);
    LefttoRight(Root);
    SummWays(Root, 1);
    TreeSize(Root);
    TreeSumm(Root);
    TreeHeight(Root);
    AveregeHeight(Root);
    PrintInfo(Root, Root);

    cout << endl;

    printf("n=100       ������      �����. �����    ������      �����.������\n");
    for (int q = 100; q < 101; q += 100)
    {
        cout << "���";
        cout << "\t    " << TreeSize(Root);
        cout << "\t         " << TreeSumm(Root);
        cout << "\t         " << TreeHeight(Root);
        cout << "\t       " << AveregeHeight(Root);
        cout << endl;
        cout << "���";
        cout << "\t    " << TreeSize(root);
        cout << "\t         " << TreeSumm(root);
        cout << "\t         " << TreeHeight(root);
        cout << "\t       " << AveregeHeight(root);
        cout << endl;
    }
    int levels = countLevels(root);
    cout << "\n ���������� ������� ��������� ������: " << levels << endl;
}

void eightlab()
{
    int x;
    setlocale(LC_ALL, "Rus");
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

    // ���������� ������
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
    int **AW1 = new int *[n1 + 1]; // ������� �����
    int **AP1 = new int *[n1 + 1]; // ������� ���������� �����
    int **AR1 = new int *[n1 + 1]; // ������� ��������

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

void ninelab()
{
    int x;
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    const int n = 100;
    const int n1 = 9;
    int **VandW = new int *[2];

    for (int i = 0; i < 2; i++)
    {
        VandW[i] = new int[n + 1];
        VandW[i][0] = 0;
    }

    // ��������� ������ ���������������� �������
    bool table[n] = {false};
    for (int i = 1; i < n + 1; i++)
    {
        while (table[x = rand() % n])
            ;
        table[x] = true;
        VandW[0][i] = x;
    }

    // ���������� ������
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

    // ��������� ����
    for (int i = 1; i < n + 1; i++)
    {
        VandW[1][i] = rand() % n + 1;
    }

    // ����� ��������� ������ � �����
    cout << "����� ��������� ������[�����]" << endl;
    short int tmp = 0;
    for (int i = 1; i < Size + 1; i++)
    {
        cout.width(3);
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

    tree *DOP_A2 = NULL;
    cout << "������ ������������ ������ (������������ �������� #2)" << endl;
    cout << "����[����]" << endl;
    A2_print(DOP_A2, 1, Size, VandW);
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
    createTreeDOP(DOP, 0, Size, AR, VandW);

    cout << "������ ������������ ������ (������������ �������� #1)" << endl;
    cout << "����[����]" << endl;
    tree *DOP_A1 = NULL;
    A1_print(DOP_A1, Size + 1, VandW);
    cout << endl;

    cout << "����� ���(������ ��������) ����� �������:\n";
    LefttoRight1(DOP);
    cout << endl
         << "������: " << TreeSize1(DOP) << endl;
    cout << "�����. �����: " << TreeSumm1(DOP) << endl;
    cout << "�����������.������: " << weightedAverageHeightTree(DOP) << endl;
    cout << "AP[0,n] / AW[0,n] = " << (double)AP[0][n] / AW[0][n] << endl;
    cout << endl;

    cout << "����� �1 ����� �������:\n";
    LefttoRight1(DOP_A1);
    cout << endl
         << "������: " << TreeSize1(DOP_A1) << endl;
    cout << "�����. �����: " << TreeSumm1(DOP_A1) << endl;
    cout << "������: " << TreeHeight1(DOP_A1) << endl;
    cout << "�����������.������: " << weightedAverageHeightTree(DOP_A1) << endl;
    cout << endl;

    cout << "����� �2 ����� �������:\n";
    LefttoRight1(DOP_A2);
    cout << endl
         << "������: " << TreeSize1(DOP_A2) << endl;
    cout << "�����. �����: " << TreeSumm1(DOP_A2) << endl;
    cout << "������: " << TreeHeight1(DOP_A2) << endl;
    cout << "�����������.������: " << weightedAverageHeightTree(DOP_A2) << endl;
    cout << endl;

    printf("n=100       ������      �����. �����    ������      �����������.������\n");
    for (int q = 100; q < 101; q += 100)
    {
        cout << "���";
        cout << "\t    " << TreeSize1(DOP);
        cout << "\t         " << TreeSumm1(DOP);
        cout << "\t         " << TreeHeight1(DOP);
        cout << "\t       " << weightedAverageHeightTree(DOP);
        cout << endl;
        cout << "�1";
        cout << "\t    " << TreeSize1(DOP_A1);
        cout << "\t         " << TreeSumm1(DOP_A1);
        cout << "\t         " << TreeHeight1(DOP_A1);
        cout << "\t       " << weightedAverageHeightTree(DOP_A1);
        cout << endl;
        cout << "�2";
        cout << "\t    " << TreeSize1(DOP_A2);
        cout << "\t         " << TreeSumm1(DOP_A2);
        cout << "\t         " << TreeHeight1(DOP_A2);
        cout << "\t       " << weightedAverageHeightTree(DOP_A2);
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "ru-RU");
    int variant;
    Vertex *Root = nullptr;
    do
    {
        print_menu();

        variant = get_variant(9);

        switch (variant)
        {
        case 1:
            firstlab();
            break;
        case 2:
            secthreeLab();
            break;
        case 3:
            fourthLab();
            break;
        case 4:
            fifthLab();
            break;
        case 5:
            sixlab();
            break;

        case 6:
            sevenlab();
            break;

        case 7:
            eightlab();
            break;
        case 8:
            ninelab();
            break;
        }

        if (variant != 9)
            system("pause");
    } while (variant != 9);
}
