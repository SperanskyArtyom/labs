#include "tree.h"

int C;

void obhod_rootLR(Vertex *p)
{
    if (p != nullptr)
    {
        std::cout << p->Data << "\t ";
        obhod_rootLR(p->Left);
        obhod_rootLR(p->Right);
    }
}

void obhod_LrootR(Vertex *p)
{
    if (p != nullptr)
    {
        obhod_LrootR(p->Left);
        std::cout << p->Data << "\t ";
        obhod_LrootR(p->Right);
    }
}

void obhod_LRroot(Vertex *p)
{
    if (p != nullptr)
    {
        obhod_LRroot(p->Left);
        obhod_LRroot(p->Right);
        std::cout << p->Data << "\t ";
    }
}

int size(Vertex *p)
{
    if (p == nullptr)
        return 0;
    return 1 + size(p->Left) + size(p->Right);
}

long long summary(Vertex *p)
{
    if (p == nullptr)
        return 0;
    return p->Data + summary(p->Left) + summary(p->Right);
}

int height(Vertex *p)
{
    if (p == nullptr)
        return 0;
    return 1 + std::max(height(p->Left), height(p->Right));
}

int pathLenght(Vertex *p, int level)
{
    if (p == nullptr)
        return 0;
    return level + pathLenght(p->Left, level + 1) + pathLenght(p->Right, level + 1);
}

int pathLenght(Vertex *p)
{
    return pathLenght(p, 1);
}

double avgHeight(Vertex *root)
{
    return (double)pathLenght(root) / size(root);
}

bool isSearchTree(Vertex *p)
{
    if (p != nullptr && ((p->Left != nullptr && (p->Data <= p->Left->Data || !isSearchTree(p->Left))) ||
                         (p->Right != nullptr && (p->Data >= p->Right->Data || !isSearchTree(p->Right)))))
        return false;
    return true;
}

bool treeSearch(Vertex *root, int x)
{
    C = 0;
    Vertex *p = root;
    while (p != nullptr)
    {
        if (++C && p->Data < x)
            p = p->Right;
        else if (++C && p->Data > x)
            p = p->Left;
        else
            return true;
    }
    return false;
}

Vertex *createISDP(int *sortedArr, int L, int R)
{
    if (L > R)
        return nullptr;
    int m = (L + R) / 2;
    Vertex *p = new Vertex;
    p->Data = sortedArr[m];
    p->Left = createISDP(sortedArr, L, m - 1);
    p->Right = createISDP(sortedArr, m + 1, R);
    return p;
}

int plus = 0;

void fillIndexes(Vertex *p, int idx, int h, int height)
{
    if (h == height - 1)
    {
        p->Index = idx;
        if (plus == 0)
        {
            plus = idx * 2;
        }
        if (p->Left != NULL)
        {
            (p->Left)->Index = plus++;
        }
        if (p->Right != NULL)
        {
            (p->Right)->Index = plus++;
        }
        return;
    }
    else
    {
        p->Index = idx;
        fillIndexes(p->Left, idx * 2, h + 1, height);
        fillIndexes(p->Right, idx * 2 + 1, h + 1, height);
    }
}

void indexObhod_rootLR(Vertex *p)
{
    if (p != nullptr)
    {
        std::cout << p->Index << "\t ";
        indexObhod_rootLR(p->Left);
        indexObhod_rootLR(p->Right);
    }
}

void indexObhod_LrootR(Vertex *p)
{
    if (p != nullptr)
    {
        indexObhod_LrootR(p->Left);
        std::cout << p->Index << "\t ";
        indexObhod_LrootR(p->Right);
    }
}

void addToSDP(Vertex *&root, int data)
{
    Vertex **p = &root;
    while (*p != nullptr)
    {
        if (data < (*p)->Data)
            p = &((*p)->Left);
        else if (data > (*p)->Data)
            p = &((*p)->Right);
        else
            return;
    }
    (*p) = new Vertex;
    (*p)->Data = data;
    (*p)->Left = nullptr;
    (*p)->Right = nullptr;
}

void addToSDPv2(Vertex *&p, int data)
{
    if (p == nullptr)
    {
        p = new Vertex;
        p->Data = data;
        p->Left = nullptr;
        p->Right = nullptr;
    }
    else if (data < p->Data)
        addToSDPv2(p->Left, data);
    else if (data > p->Data)
        addToSDPv2(p->Right, data);
}

Vertex *createSDP(int *arr, int size)
{
    Vertex *root = nullptr;
    for (int i = 0; i < size; i++)
        addToSDP(root, arr[i]);
    return root;
}

Vertex *createSDPv2(int *arr, int size)
{
    Vertex *root = nullptr;
    for (int i = 0; i < size; i++)
        addToSDPv2(root, arr[i]);
    return root;
}

void deleteVertex(int x, Vertex *&root)
{
    auto p = &root;
    while (*p != nullptr)
    {
        if ((*p)->Data < x)
            p = &(*p)->Right;
        else if ((*p)->Data > x)
            p = &(*p)->Left;
        else
            break;
    }
    if (*p != nullptr)
    {
        auto q = *p;
        if (q->Left == nullptr)
            *p = q->Right;
        else if (q->Right == nullptr)
            *p = q->Left;
        else
        {
            auto r = q->Left;
            auto s = q;
            while (r->Right != nullptr)
            {
                s = r;
                r = r->Right;
            }
            if (s->Left != r)
            {
                s->Right = r->Left;
                r->Left = q->Left;
                r->Right = q->Right;
                *p = r;
            }
            else
            {
                r->Right = q->Right;
                *p = r;
            }
        }
        delete q;
    }
}
