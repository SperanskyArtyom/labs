#include "tree.h"
#include "visual.h"
#include <iostream>

using namespace std;

int main()
{
    srand(time(nullptr));
    int const n = 100;
    int A[n];
    for (int i = 0; i < n; i++)
        A[i] = rand() % 500 + 1;
    Vertex *AVL = createAVL(A, n);

    cout << "Обход АВЛ слева направо:\n";
    obhod_LrootR(AVL);
    // drawTree(AVL);
    cout << endl;
    system("./table");

    return 0;
}
