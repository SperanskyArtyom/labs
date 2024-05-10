#include <list.h>

#include <iostream>
#include <cstdlib>

// Stack functions

void add(List *&head, int data){
    auto *p = new List;
    p->data = data;
    p->next = head;
    head = p;
}

void pop(List *&head){
    auto *p = head;
    head = head->next;
    delete p;
}

void clear(List *&head){
    while (head != nullptr)
        pop(head);
}

void print(List *&p){
    if(p != nullptr){
        print(p->next);
        std::cout << p->data << ' ';
    }
}

void print(List *&p, bool reversed){
    if (!reversed)
        print(p);
    else {
        if (p != nullptr) {
            std::cout << p->data << ' ';
            print(p->next, reversed);
        }
    }
}

void fillInc(List *&head, int n){
    clear(head);
    for (int i = 1; i <= n; i++)
        add(head, i);
}

void fillDec(List *&head, int n){
    clear(head);
    for (int i = 0; i < n; i++)
        add(head, n - i);
}

void fillRand(List *&head, int n){
    clear(head);
    for (int i = 0; i < n; i++)
        add(head, rand());
}

// Queue

Queue initQ(){
    Queue q;
    q.head = nullptr;
    q.tail = nullptr;
    return q;
}

void add(Queue &q, int n){
    auto *p = new List;
    p->data = n;
    p->next = nullptr;
    if (q.head != nullptr)
        q.tail->next = p;
    else q.head = p;
    q.tail = p;
}

void fillInc(Queue &q, int n){
    clear(q.head);
    for (int i = 1; i <= n; i++)
        add(q, i);
}

void fillDec(Queue &q, int n){
    clear(q.head);
    for (int i = 0; i < n; i++)
        add(q, n - i);
}

void fillRand(Queue &q, int n){
    clear(q.head);
    for (int i = 0; i < n; i++)
        add(q, rand());
}

long CheckSum(List *&head){
    long sum = 0;
    auto *p = head;
    while(p != nullptr){
        sum += p->data;
        p = p->next;
    }
    return  sum;
}

int RunNumbers(List *&head){
    if (head == nullptr)
        return 0;
    int count = 1;
    int previous = head->data;
    auto *p = head->next;
    while (p != nullptr){
        if (p->data > previous)
            count++;
        previous = p->data;
        p = p->next;
    }
    return count;
}