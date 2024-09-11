#include <iostream>

int** genRandMatrix(int size, int maxValue);
void printMatrix(int** matrix, int size);
void printA(int** matrix, int size);

int main() {
    srand(time(nullptr));
    int size = rand() % 10;
    int maxValue = 100;
    auto matrix = genRandMatrix(size, maxValue);
    printMatrix(matrix, size);

    for (int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

int* genRandArray(int size, int maxValue){
    int* array = new int[size];
    for (int i = 0; i < size; i++){
        array[i] = rand() % maxValue + 1;
    }
    return array;
}

int** genRandMatrix(int size, int maxValue){
    int** matrix = new int*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = genRandArray(size, maxValue);
    }
    return matrix;
}

void print(int* arr, int size){
    for(int i = 0; i < size; i++)
        std::cout << arr[i] << '\t';
    std::cout << std::endl;
}

void printMatrix(int** matrix, int size){
    for (int i = 0; i < size; i++)
        print(matrix[i], size);
}

void printA(int** matrix, int size){
    
}