#include <iostream>
using namespace std;
#define Maxsize 10
typedef struct
{
    int length=10;
    int data[Maxsize];
} Sqlist;
void InitList(Sqlist &L)//传引用
{
    //for(int i=0;i<Maxsize;i++)
    //{
    //    L.data[i]=0;
    //}
    L.length=0;
}
int main()
{
    Sqlist L;
    InitList(L);
    for(int i=0;i<Maxsize;++i)
    {
        cout<<L.data[i]<<" ";
    }
    cout<<endl;//内存中会有遗留的脏数据，所以需要给各个数据元素设置默认值
    return 0;
}