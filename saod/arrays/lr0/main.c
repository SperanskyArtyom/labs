#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"

int main()
{
    srand(time(NULL));
    int N = 10, A[N];
    FillInc(A, N);
    PrintMass(A, N);
    printf("Check Sum: %ld, Run Numbers: %d\n", CheckSum(A, N), RunNumbers(A, N));
    FillDec(A, N);
    PrintMass(A, N);
    printf("Check Sum: %ld, Run Numbers: %d\n", CheckSum(A, N), RunNumbers(A, N));
    FillRand(A, N);
    PrintMass(A, N);
    printf("Check Sum: %ld, Run Numbers: %d\n", CheckSum(A, N), RunNumbers(A, N));
    return 0;
}
