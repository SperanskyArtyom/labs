#include <fstream>
#include <cstdlib>
#include <time.h>
#include "heapsort.h"
#include "shellsort.h"

extern int M, C, M2, C2;

void T_sorts(int n, int &t1, int &t2)
{
    int *arr1 = new int[n];
    int *arr2 = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = rand();
        arr2[i] = arr1[i];
    }

    int H[n];
    int m = KnuthSequence(H, n);
    ShellSort(arr1, n, H, m);
    t1 = M2 + C2;
    if (M2 + C2 == 0)
        t1++;
    HeapSort(arr2, n);
    t2 = M + C;
    if (M + C == 0)
        t2++;
    delete[] arr1;
    delete[] arr2;
}

int main()
{
    srand(time(NULL));
    int T_shell, T_heap;
    std::string name = "sort.txt";
    std::ofstream out;
    out.open(name);
    if (out.is_open())
        for (int N = 10; N <= 500; N+= 10)
        {
            T_sorts(N, T_shell, T_heap);
            out << N << "\t" << T_shell << "\t" << T_heap << "\n";
        }
    out.close();

    system("./graphics.gpi");
    return 0;
}
