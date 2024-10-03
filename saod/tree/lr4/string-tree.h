#include <string>
#include <vector>
#include <iostream>

struct Vertex
{
    std::string Data;
    int number;
    Vertex *Left;
    Vertex *Right;
};

void addToSDP(Vertex *&p, std::string data)
{
    if (p == nullptr)
    {
        p = new Vertex;
        p->Data = data;
        p->Left = nullptr;
        p->Right = nullptr;
        p->number = 1;
    }
    else if (data < p->Data)
        addToSDP(p->Left, data);
    else if (data > p->Data)
        addToSDP(p->Right, data);
    else
        p->number++;
}

Vertex *createSDP(std::vector<std::string> arr)
{
    Vertex *root = nullptr;
    for (auto str : arr)
        addToSDP(root, str);
    return root;
}

void printVertexMap(Vertex *root)
{
    if (root != nullptr)
    {
        std::cout << root->Data << " : " << root->number << '\n';
        printVertexMap(root->Left);
        printVertexMap(root->Right);
    }
}
