#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

int main()
{
    srand(time(NULL));
    int n = 10;
    int A[n];
    FillRand(A, n);

    Vertex *root = createAVL(A, n);
    ObhodLR(root);

    bool decreased;
    int i = 0;
    while (i < n)
    {
        int key;
        printf("\nУдалить элемент: ");
        scanf("%d", &key);
        if (deleteFromAVL(root, key, decreased))
        {
            printf("Элемент %d удалён\n", key);
            ObhodLR(root);
            i++;
        }
        else
        {
            printf("Элемента %d нет в дереве\n", key);
        }
    }

    freeTree(root);
    return 0;
}
