#include "QuickSort.h"

int M, C, maxDepth;

void QuickSort(int* arr, int left, int right){
    static int depth = 0;
    depth++;
    int x = arr[(left + right) / 2], i = left, j = right;
    M++;
    while (i <= j) {
        while (++C && arr[i] < x)
            i++;
        while (++C && arr[j] > x)
            j--;
        if (i <= j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            M += 3;
            i++;
            j--;
        }
    }
    if (left < j){
        QuickSort(arr, left, j);
    }
    if (right > i){
        QuickSort(arr, i, right);
    }
    if (maxDepth < depth)
        maxDepth = depth;
    depth = 0;
}

void QuickSortV2(int* arr, int left, int right){
    static int depth = 0;
    depth++;
    while (left < right) {
        int x = arr[(left + right) / 2], i = left, j = right;
        while (i <= j) {
            while (++C && arr[i] < x)
                i++;
            while (++C && arr[j] > x)
                j--;
            if (i <= j){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                M += 3;
                i++;
                j--;
            }
        }
        if (j - left < right - i){
            QuickSortV2(arr, left, j);
            left = i;
        } else{
            QuickSortV2(arr, i, right);
            right = j;
        }
        if(depth > maxDepth)
            maxDepth = depth;
        depth = 0;
    }
}