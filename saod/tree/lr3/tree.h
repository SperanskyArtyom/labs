#pragma once

#include <iostream>
#include <algorithm>

struct Vertex
{
    int Data;
    int Index;
    Vertex *Left;
    Vertex *Right;
};

void obhod_rootLR(Vertex *);
void obhod_LrootR(Vertex *);
void obhod_LRroot(Vertex *);

void fillIndexes(Vertex *, int, int, int);
void indexObhod_rootLR(Vertex *);
void indexObhod_LrootR(Vertex *);

int size(Vertex *);
long long summary(Vertex *);
int height(Vertex *);
int pathLenght(Vertex *, int);
int pathLenght(Vertex *);

double avgHeight(Vertex *);

bool isSearchTree(Vertex *);
bool treeSearch(Vertex *, int);

Vertex *createISDP(int *, int, int);
Vertex *createSDP(int *arr, int size);
Vertex *createSDPv2(int *arr, int size);

void addToSDP(Vertex *&root, int data);
void addToSDPv2(Vertex *&root, int data);
