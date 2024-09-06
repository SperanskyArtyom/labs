#include <iostream>

int** genRandMatrix(int size, int maxValue);
void printMatrix(int** matrix);
int main() {
    srand(time(nullptr));
    int size = rand() % 10;
    int maxValue = 100;
    int **matrix = genRandMatrix(size, maxValue);
    printMatrix(matrix);
    for (int i = 0; i < size + 1; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

int* genRandArray(int size, int maxValue){
    int* array = new int[size+1];
    array[0] = size;
    for (int i = 1; i < size+1; i++){
        array[i] = rand() % maxValue + 1;
    }
    return array;
}

int** genRandMatrix(int size, int maxValue){
    int** matrix = new int*[size+1];
    matrix[0] = new int;
    matrix[0][0] = size;
    for(int i = 1; i < size+1; i++){
        int columnSize = rand() % 10;
        matrix[i] = genRandArray(columnSize, maxValue);
    }
    return matrix;
}

void print(int* arr){
    int size = arr[0];
    std::cout << size << ":\t";
    for(int i = 1; i < size + 1; i++){
        std::cout << arr[i] << '\t';
    }
    std::cout << std::endl;
}

void printMatrix(int** matrix){
    int size = matrix[0][0];
    std::cout << size << '\n';
    for (int i = 1; i < size + 1; i++){
        print(matrix[i]);
    }
}
