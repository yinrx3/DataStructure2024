#include <iostream>
using namespace std;
#define initsize 10
typedef struct
{
    int length;
    int maxsize;
    int *data;
}SeqList;
void InitList(SeqList &L)
{
    L.length=0;
    L.maxsize=initsize;
    L.data=new int[initsize];
}
void IncreaseSize(SeqList &L,int len)
{
    int *p=L.data;
    L.data=new int[L.maxsize+len];
    for(int i=1;i<L.length;i++)
    {
        L.data[i]=p[i];
    }
    L.maxsize=L.maxsize+len;
    delete[] p;
}
int main()
{
    SeqList L;
    InitList(L);
    IncreaseSize(L,5);
    return 0;
}
