#include "tree.h"
#include <iomanip>

using std::cout;

int main()
{
    extern int C;
    const int n = 100;
    int A[n];
    for (int i = 0; i < n; i++)
        A[i] = i + 1;
    auto root = createISDP(A, 0, n - 1);
    fillIndexes(root, 1, 1, height(root));
    cout << "Слева направо:\n";
    indexObhod_LrootR(root);

    cout << "\n\nСверху вниз:\n";
    indexObhod_rootLR(root);
    cout << "\n\nРазмер: " << size(root) << "\nКонтрольная сумма: " << summary(root)
         << "\nВысота: " << height(root) << "\nСредняя высота: ";
    printf("%.2f\n", avgHeight(root));

    return 0;
}
