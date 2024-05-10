#pragma once

typedef struct tLE{
    struct tLE* next;
    int data;
}List;

typedef struct qu{
    List *head;
    List *tail;
}Queue;

// Stack functions

void add(List *&head, int data);
void pop(List *&head);
void clear(List *&head);
void print(List *&p);
void print(List *&p, bool reversed);
void fillInc(List *&head, int n);
void fillDec(List *&head, int n);
void fillRand(List *&head, int n);

// Queue
Queue initQ();
void add(Queue &q, int n);
void fillInc(Queue &q, int n);
void fillDec(Queue &q, int n);
void fillRand(Queue &q, int n);

long CheckSum(List *&head);
int RunNumbers(List *&head);