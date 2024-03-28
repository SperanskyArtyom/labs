#include "heapsort.h"
#include "service_procedures.h"

#include <iostream>
#include <cmath>

extern int M, C;

using namespace std;

double C_theor(int N){
    return 2.0 * N * log2(N) + N + 2.0;
}
double M_theor(int N){
    return N * log2(N) + 6.5 * N - 4;
}

int main(){
    const int N = 10;
    cout << "C теор " << C_theor(N) << " М теор " << M_theor(N) << '\n';
    int arr[N];
    FillInc(arr, N);
    PrintMass(arr, N);
    HeapSort(arr, N);
    PrintMass(arr, N);
    cout << "С факт " << C << " М факт " << M << '\n';
    return 0;
}