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
    int n = 100;
    system("clear");
    srand(time(nullptr));
    int A[n];
    cout << "Dec Array\n";
    FillDec(A, n);
    int H[2];
    int m = KnuthSequence(H, n);
    ShellSort(A, n, H, m);
    cout << "C: " << C << " M: " << M << " checksum: " << CheckSum(A, n) << " series: " << RunNumbers(A, n) << endl;
    
    cout << "Inc Array\n";
    FillInc(A, n);
    ShellSort(A, n, H, m);
    cout << "C: " << C << " M: " << M << " checksum: " << CheckSum(A, n) << " series: " << RunNumbers(A, n) << endl;
    
    cout << "Rand Array\n";
    FillRand(A, n);
    ShellSort(A, n, H, m);
    cout << "C: " << C << " M: " << M << " checksum: " << CheckSum(A, n) << " series: " << RunNumbers(A, n) << endl;
    
    return 0;
}