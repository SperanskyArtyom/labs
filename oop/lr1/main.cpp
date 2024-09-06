#include <iostream>

int* genRandArray(int size, int maxValue);
void print(int* arr);

int main() {
    srand(time(nullptr));
    int size = rand()%10;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);
    print(arr);
    delete[] arr;
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

void print(int* arr){
    int size = arr[0];
    std::cout << size << ":\t";
    for(int i = 1; i < size + 1; i++){
        std::cout << arr[i] << '\t';
    }
    std::cout << std::endl;
}
