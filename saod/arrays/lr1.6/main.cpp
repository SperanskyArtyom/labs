//
// Created by artem on 08.03.24.
//

#include "sorts.h"
#include "service_procedures.h"
#include <iostream>
#include <cstdlib>
#include <vector>

extern int M, C;
using namespace std;

int main()
{
    int n = 100, index;
    vector<int> indexes;
    system("clear");
    int A[n];
    FillInc(A, n);
    index = BSearch1(A, n, A[0]);
    cout << "BSearch1 key: " << A[0] << "\n index: " << index << " " << A[index];
    cout << " C =" << C;
    index = BSearch2(A, n, A[0]);
    cout << "\nBSearch2 key: " << A[0] << "\n index: " << index << " " << A[index];
    cout << " C =" << C;
    index = BSearch1(A, n, A[n-1]);
    cout << "\nBSearch2 key: " << A[n-1] << "\n index: " << index << " " << A[index];
    cout << " C =" << C;
    index = BSearch2(A, n, A[n-1]);
    cout << "\nBSearch2 key: " << A[n-1] << "\n index: " << index << " " << A[index];
    cout << " C =" << C;
    index = BSearch1(A, n, -100);
    cout << "\nBSearch2 key: " << -100 << "\n index: " << index;
    cout << " C =" << C;    index = BSearch2(A, n, -100);
    cout << "\nBSearch2 key: " << -100 << "\n index: " << index;
    cout << " C =" << C;
    cout << "\n_____________________________________";

    indexes = BSearchAll1(A, n, -1);
    cout << "\nBSearchAll1 key:" << -1;
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    indexes = BSearchAll2(A, n, -1);
    cout << "\nBSearchAll2 key:" << -1;
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    indexes = BSearchAll1(A, n, A[0]);
    cout << "\nBSearchAll1 key:" << A[0];
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    indexes = BSearchAll2(A, n, A[0]);
    cout << "\nBSearchAll2 key:" << A[0];
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    indexes = BSearchAll1(A, n, A[n-1]);
    cout << "\nBSearchAll1 key:" << A[n-1];
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    indexes = BSearchAll2(A, n, A[n-1]);
    cout << "\nBSearchAll2 key:" << A[n-1];
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    for (int i = 0; i < 5; i++)
        A[i] = 1;
    indexes = BSearchAll1(A, n, A[0]);
    cout << "\nBSearchAll1 key:" << A[0];
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    indexes = BSearchAll2(A, n, A[0]);
    cout << "\nBSearchAll2 key:" << A[0];
    if (indexes.empty())
        cout << "\nnot found";
    else
        for (int i : indexes)
            cout << "\nindex:" << i << " key: " << A[i];
    cout << " C =" << C;

    return 0;
}