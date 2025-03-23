#pragma once

struct Vertex
{
    int data;
    int balance;
    Vertex *L;
    Vertex *R;
};

void FillRand(int A[], int n);
Vertex *createAVL(int A[], int n);
void ObhodLR(Vertex *root);
bool deleteFromAVL(Vertex *&p, int key, bool &decreased);
void freeTree(Vertex *);
