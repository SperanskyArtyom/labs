//
// Created by artem on 08.03.24.
//

#ifndef LR6_SORTS_H
#define LR6_SORTS_H

#include <vector>

void SelectSort(int *sortArr, int size);
void UpgradeSelectSort(int *sortArr, int size);
void BubbleSort(int *sortArr, int size);
void ShakerSort(int sortArr[], int size);
void InsertSort(int *sortArr, int size);
void kSort (int sortArr[], int size, int k);
void ShellSort(int sortArr[], int size, const int H[], int m);
int KnuthSequence(int *H, int n);
void SedgewickSequence(int sequence[], int size);
int sejsize (int N);
void FibbonachiSequence(int sequence[], int size);
int fibsize (int N);
int BSearch1(const int arr[], int size, int key);
int BSearch2 (const int arr[], int size, int key);
std::vector<int> BSearchAll1(const int arr[], int size, int key);
std::vector<int> BSearchAll2 (const int arr[], int size, int key);

#endif //LR6_SORTS_H
