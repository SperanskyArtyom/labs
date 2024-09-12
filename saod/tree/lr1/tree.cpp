#include "tree.h"

void obhod_rootLR(Vertex *p)
{
    if (p != nullptr)
    {
        std::cout << p->Data << '\t';
        obhod_rootLR(p->Left);
        obhod_rootLR(p->Right);
    }
}

void obhod_LrootR(Vertex *p)
{
    if (p != nullptr)
    {
        obhod_LrootR(p->Left);
        std::cout << p->Data << '\t';
        obhod_LrootR(p->Right);
    }
}

void obhod_LRroot(Vertex *p)
{
    if (p != nullptr)
    {
        obhod_LRroot(p->Left);
        obhod_LRroot(p->Right);
        std::cout << p->Data << '\t';
    }
}

int size(Vertex *p)
{
    if (p == nullptr)
        return 0;
    return 1 + size(p->Left) + size(p->Right);
}

int summary(Vertex *p)
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
