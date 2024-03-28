#include "heapsort.h"
#include "service_procedures.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

extern int M, C;

using namespace std;

double C_theor(int N){
    return 2.0 * N * log2(N) + N + 2.0;
}
double M_theor(int N){
    return N * log2(N) + 6.5 * N - 4;
}

int main(){
    srand(time(nullptr));
    const int N = 500;
    cout << "C + M теор " << C_theor(N) + M_theor(N) << '\n';
    int arr[N];
    FillRand(arr, N);
//    PrintMass(arr, N);
    HeapSort(arr, N);
//    PrintMass(arr, N);
    cout << "С + M fact " << C + M << '\n';
    return 0;
}