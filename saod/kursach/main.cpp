#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
// #include<graphics.h>
#include <ctime>

using namespace std;

struct record
{
    char depositor[30];
    unsigned short amount;
    char date[10];
    char lawyer[22];
};

struct record1
{
    char a[30];
    short int b;
    char c[22];
    char d[10];
};

struct record2
{
    char a[30];
    unsigned short int b;
    char c[10];
    char d[22];
};

struct record3
{
    char a[32];
    char b[18];
    short int c;
    short int d;
    char e[10];
};

int main()
{

    FILE *fp;
    fp = fopen("testBase3.dat", "rb");
    record tt[4000] = {0};
    record1 mas[4000] = {0};
    record2 mas2[4000] = {0};
    record3 mas3[4000] = {0};
    int i = 0, sum = 0;
    int ch[10];
    i = fread((record *)tt, sizeof(record), 4000, fp);
    cout << i << endl;
    for (int i = 0; i < 10; ++i)
    {
        wcout << tt[i].depositor;
        cout << tt[i].depositor << "\t" << tt[i].amount << "\t" << tt[i].date << "\t" << tt[i].lawyer << endl;
    }

    i = 0;
    /*while((i++)<4000)
    {
        //getchar();
        cout<<mas3[i].a<<mas3[i].b<<mas3[i].c<<mas3[i].d<<mas3[i].e<<endl;
    }
    */
    i = 0;
    /*while((i++)<4000)
    {
        //getchar();
        cout<<mas[i].a<<mas[i].b<<mas[i].c<<mas[i].d<<endl;
    }
    */
    i = 0;
    /*while((i++)<4000)
    {
        //getchar();
        cout<<mas2[i].a<<mas2[i].b<<mas2[i].c<<mas2[i].d<<endl;
    }
    */
    // cout<<sizeof(record)<<endl<<sizeof(record1)<<endl<<sizeof(record2)<<endl<<sizeof(record3)<<endl<<endl;
    //  getch();
    return 0;
}
