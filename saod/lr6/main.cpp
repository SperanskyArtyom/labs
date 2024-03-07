//
// Created by artem on 08.03.24.
//

#include "sorts.h"
#include "service_procedures.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

extern int M, C;
using namespace std;

int main()
{
    system("clear");
    srand(time(nullptr));
    int A[10];
    cout << "Dec Array\n";
    FillDec(A, 10);
    int H[2];
    int m = KnuthSequence(H, 10);
    ShellSort(A, 10, H, m);
    cout << "C: " << C << " M: " << M << " checksum: " << CheckSum(A, 10) << " series: " << RunNumbers(A, 10) << endl;
    PrintMass(A, 10);
    cout << "Inc Array\n";
    FillInc(A, 10);
    ShellSort(A, 10, H, m);
    cout << "C: " << C << " M: " << M << " checksum: " << CheckSum(A, 10) << " series: " << RunNumbers(A, 10) << endl;
    PrintMass(A, 10);
    cout << "Rand Array\n";
    FillRand(A, 10);
    ShellSort(A, 10, H, m);
    cout << "C: " << C << " M: " << M << " checksum: " << CheckSum(A, 10) << " series: " << RunNumbers(A, 10) << endl;
    PrintMass(A, 10);
    return 0;
}