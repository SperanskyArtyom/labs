#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

#include "sorts.h"

using namespace std;

const int ARR_SIZE = 3*10000;

const int MAX_ELEMENT = 10000;
float timer(void (*sortType)(int*, int), int *arr, int size);
float timer(void (*sortType)(float*, int), float *arr, int size);
void fillRand(int *arr, int size);
void fillRand(float *arr, int size);
void copyArr(const int *arrCopyFrom, int *arrayCopyTo, int size);

void copyArr(const float *arrCopyFrom, float *arrCopyTo, int size);

int main() {
    srand(time(nullptr));
    int selectInt[ARR_SIZE], upgSelectInt[ARR_SIZE], bubbleInt[ARR_SIZE], shakerInt[ARR_SIZE], insertInt[ARR_SIZE];
    float selectFloat[ARR_SIZE], upgSelectFloat[ARR_SIZE], bubbleFloat[ARR_SIZE], shakerFloat[ARR_SIZE], insertFloat[ARR_SIZE];
    fillRand(selectInt, ARR_SIZE);
    copyArr(selectInt, upgSelectInt, ARR_SIZE);
    copyArr(selectInt, bubbleInt, ARR_SIZE);
    copyArr(selectInt, shakerInt, ARR_SIZE);
    copyArr(selectInt, insertInt, ARR_SIZE);
    cout << "Оценка времени работы различных сортировок массивов целых чисел.\n";
    cout << "Selection Sort:         " << timer(SelectSort, selectInt, ARR_SIZE) << " c\n";
    cout << "Upgrade Selection Sort: " << timer(UpgradeSelectSort, upgSelectInt, ARR_SIZE) << " c\n";
    cout << "Bubble Sort:            " << timer(BubbleSort, bubbleInt, ARR_SIZE) << " c\n";
    cout << "Cocktail Sort:          " << timer(ShakerSort, shakerInt, ARR_SIZE) << " c\n";
    cout << "Insertion Sort:         " << timer(InsertSort, insertInt, ARR_SIZE) << " c\n";

    fillRand(selectFloat, ARR_SIZE);
    copyArr(selectFloat, upgSelectFloat, ARR_SIZE);
    copyArr(selectFloat, bubbleFloat, ARR_SIZE);
    copyArr(selectFloat, shakerFloat, ARR_SIZE);
    copyArr(selectFloat, insertFloat, ARR_SIZE);
    cout << "\nОценка времени работы различных сортировок массивов вещественных чисел.\n";
    cout << "Selection Sort:         " << timer(SelectSort, selectFloat, ARR_SIZE) << " c\n";
    cout << "Upgrade Selection Sort: " << timer(UpgradeSelectSort, upgSelectFloat, ARR_SIZE) << " c\n";
    cout << "Bubble Sort:            " << timer(BubbleSort, bubbleFloat, ARR_SIZE) << " c\n";
    cout << "Cocktail Sort:          " << timer(ShakerSort, shakerFloat, ARR_SIZE) << " c\n";
    cout << "Insertion Sort:         " << timer(InsertSort, insertFloat, ARR_SIZE) << " c\n";

    return 0;
}

void fillRand(int *arr, int size){
    for (int i = 0; i < size; i++)
        arr[i] = rand() % MAX_ELEMENT;
}

void fillRand(float *arr, int size){
    for (int i = 0; i < size; i++){
        arr[i] = ((float)rand()) * MAX_ELEMENT / (float)RAND_MAX;
    }
}

void copyArr(const int *arrCopyFrom, int *arrayCopyTo, int size)
{
    for(int i = 0; i < size; i++)
        arrayCopyTo[i] = arrCopyFrom[i];
}

void copyArr(const float *arrCopyFrom, float *arrCopyTo, int size)
{
    for(int i = 0; i < size; i++)
        arrCopyTo[i] = arrCopyFrom[i];
}

float timer(void (*sortType)(int*, int), int *arr, int size){
    auto start = chrono::steady_clock::now();
    sortType(arr, size);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return (float) elapsed_ms.count() / 1000;
}

float timer(void (*sortType)(float*, int), float *arr, int size){
    auto start = chrono::steady_clock::now();
    sortType(arr, size);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return (float) elapsed_ms.count() / 1000;
}