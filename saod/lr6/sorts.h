//
// Created by artem on 08.03.24.
//

#ifndef LR6_SORTS_H
#define LR6_SORTS_H
void SelectSort(int *sortArr, int size);
void UpgradeSelectSort(int *sortArr, int size);
void BubbleSort(int *sortArr, int size);
void ShakerSort(int sortArr[], int size);
void InsertSort(int *sortArr, int size);
void kSort (int sortArr[], int size, int k);
void ShellSort(int sortArr[], int size, const int H[], int m);
int KnuthSequence(int *H, int n);

#endif //LR6_SORTS_H
