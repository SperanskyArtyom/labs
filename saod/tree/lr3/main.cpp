#include "tree.h"
#include <iostream>

int comp1(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    srand(time(nullptr));
    int n = 100, A[n];
    for (int i = 0; i < n; i++)
        A[i] = rand() % 10001;
    Vertex *root = createSDP(A, n);
    std::cout << "Обход СДП, созданного методом двойной косвенности:\n";
    obhod_LrootR(root);
    Vertex *root2 = createSDPv2(A, n);
    std::cout << "\nОбход СДП, созданного рекурсивно:\n";
    obhod_LrootR(root2);
    std::cout << '\n';
    qsort(A, 100, sizeof(int), comp1);
    Vertex *ISDP = createISDP(A, 0, 99);
    fillIndexes(ISDP, 1, 1, height(ISDP));
    std::cout << "Oбход слева направо ИСДП:\n";
    indexObhod_LrootR(ISDP);
    std::cout << '\n';
    system("./table");
    return 0;
}
