#include "tree.h"
#include "cstdlib"

int main()
{
    bool HR = true;
    bool VR = true;

    srand(time(nullptr));
    int arr[100];
    for (int i = 0; i < 100; i++)
        arr[i] = rand();
    Vertex *DBD = createDBD(arr, 100, VR, HR);
    Vertex *AVL = createAVL(arr, 100);
    table(AVL, DBD, 100);

    return 0;
}
