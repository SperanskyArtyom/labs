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

void indexObhod_rootLR(Vertex *);
void indexObhod_LrootR(Vertex *);

int size(Vertex *);
int summary(Vertex *);
int height(Vertex *);
int pathLenght(Vertex *, int);
int pathLenght(Vertex *);

double avgHeight(Vertex *);

bool isSearchTree(Vertex *);
bool treeSearch(Vertex *, int);

Vertex *createISDP(int *, int, int);

void fillIndexes(Vertex *, int, int, int);
