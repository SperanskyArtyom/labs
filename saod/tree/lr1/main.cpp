#include "tree.h"
#include <iomanip>

int main()
{
    Vertex *root = new Vertex;
    root->Data = 3;
    root->Left = new Vertex;
    root->Left->Data = 2;
    root->Left->Left = nullptr;
    root->Left->Right = nullptr;
    root->Right = new Vertex;
    root->Right->Data = 1;
    root->Right->Left = nullptr;
    root->Right->Right = new Vertex;
    root->Right->Right->Data = 5;
    root->Right->Right->Left = nullptr;
    root->Right->Right->Right = new Vertex;
    root->Right->Right->Right->Data = 0;
    root->Right->Right->Right->Left = nullptr;
    root->Right->Right->Right->Right = nullptr;

    obhod_rootLR(root);
    std::cout << std::endl;

    obhod_LrootR(root);
    std::cout << std::endl;

    obhod_LRroot(root);
    std::cout << std::endl;

    // printf("%.2f\n", avgHeight(root));
    return 0;
}
