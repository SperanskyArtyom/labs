#include <iostream>
#include "list.h"

void listSplit(List *&S, List *&a, List *&b, int &n);
Queue mergeSeries(List *&a, int q, List*&b, int r);
void mergeSort(List *&S);

int main() {
    List *head = nullptr, *a, *b;
    int n;
    fillDec(head, 25);
//    listSplit(head, a, b, n);
////    print(a);
//    std::cout << '\t'<< listLen(a) << "\n";
////    print(b);
//    std::cout << '\t'<< listLen(b) << "\n" << n << "\n";
//    auto c = mergeSeries(a, listLen(a), b, listLen(b));
//    print(c.head, true);
//    std::cout << "\nSeries: " << RunNumbers(c.head) << ' ' << RunNumbers(a) << ' ' << RunNumbers(b) << '\n';
    mergeSort(head);
    print(head);
    return 0;
}

void listSplit(List *&S, List *&a, List *&b, int &n){
    a = S;
    b = S->next;
    n = 1;
    auto k = a;
    auto p = b;
    while ( p != nullptr){
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

Queue mergeSeries(List *&a, int q, List*&b, int r){
    Queue c = initQ();
    while (q != 0 && r != 0){
        if (a->data <= b->data){
            fromStackToQueue(a, c);
            q--;
        }
        else{
            fromStackToQueue(b, c);
            r--;
        }
    }
    while (q > 0){
        fromStackToQueue(a, c);
        q--;
    }
    while (r > 0){
        fromStackToQueue(b, c);
        r--;
    }
    return c;
}

void mergeSort(List *&S){
    List *a, *b;
    Queue c[2];
    int n, q, r;
    listSplit(S, a, b, n);
    int p = 1;
    while (p < n){
        c[0] = initQ();
        c[1] = initQ();
        int i = 0, m = n;
        while (m > 0){
            if (m >= p)
                q = p;
            else
                q = m;
            m -= q;
            if (m >= p)
                r = p;
            else
                r = m;
            m -= r;
            c[i] = mergeSeries(a, q, b, r);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p *= 2;
    }
    c[0].tail->next = nullptr;
    S = c[0].head;
}