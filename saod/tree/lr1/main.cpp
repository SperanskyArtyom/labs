#include "tree.h"
#include <iomanip>

int main()
{
    Vertex *root = new Vertex;
    root->Data = 1;

    root->Left = new Vertex;
    root->Left->Data = 2;

    root->Right = new Vertex;
    root->Right->Data = 3;

    root->Left->Left = nullptr;

    root->Left->Right = new Vertex;
    root->Left->Right->Data = 4;

    root->Right->Left = nullptr;
    root->Right->Right = new Vertex;
    root->Right->Right->Data = 5;
    root->Right->Right->Left = nullptr;
    root->Right->Right->Right = nullptr;

    root->Left->Right->Left = new Vertex;
    root->Left->Right->Left->Data = 6;
    root->Left->Right->Right = nullptr;

    root->Left->Right->Left->Left = nullptr;
    root->Left->Right->Left->Right = nullptr;

    std::cout << "Обход сверху вниз: ";
    obhod_rootLR(root);
    std::cout << std::endl
              << "Обход слева направо: ";

    obhod_LrootR(root);
    std::cout << std::endl
              << "Обход снизу вверх: ";

    obhod_LRroot(root);
    std::cout << std::endl;

    std::cout << "\nРазмер: " << size(root) << "\nКонтрольная сумма: " << summary(root) << "\nВысота: " << height(root) << "\nСредняя высота: ";
    printf("%.2f\n", avgHeight(root));
    return 0;
}
