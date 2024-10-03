#include <tree.h>
#include <iostream>

int main()
{
    int const n = 20;
    int A[n];
    for (int i = 0; i < n; i++)
        A[i] = rand() % 500 + 1;
    Vertex *root = createSDPv2(A, n);

    std::cout << "Обход дерева слева направо:\n";
    obhod_LrootR(root);
    for (int i = 0; i < 10; i++)
    {
        std::cout << "\nУдалить вершину с ключём ";
        int x;
        std::cin >> x;
        deleteVertex(x, root);
        std::cout << "Обход дерева слева направо после удаления вершины с ключём " << x << "\n";
        obhod_LrootR(root);
        std::cout << "\n";
    }
}
