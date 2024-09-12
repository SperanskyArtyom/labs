#pragma once

#include <iostream>
#include <algorithm>

struct Vertex
{
    int Data;
    Vertex *Left;
    Vertex *Right;
};

void obhod_rootLR(Vertex *);
void obhod_LrootR(Vertex *);
void obhod_LRroot(Vertex *);

int size(Vertex *);
int summary(Vertex *);
int height(Vertex *);
int pathLenght(Vertex *, int);
int pathLenght(Vertex *);

double avgHeight(Vertex *);
