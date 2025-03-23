#include <iostream>
using namespace std;
#define MaxSize 10
typedef struct
{
    int data[MaxSize];
    int length;
}SqList;
void InitList(SqList &L)//传引用
{
    for(int i=0;i<MaxSize;i++)
    {
        L.data[i]=0;
    }
    
    L.length=MaxSize;
}
bool ListInsert(SqList &L,int i,int e)//往第i个位置插入数据e
{  
    if( i<1||i>L.length+1)
    {
        return false;
    }
    if(L.length>=MaxSize)
    {
        return false;
    }
    for(int j=L.length;j>=i;j--)
    {
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}
bool ListDelete(SqList &L,int i,int &e)
{
    if(i<1||i>L.length) 
        return false;//判断i的范围是否有效
    e=L.data[i-1];
    for(int j=i;j<L.length;j++)
    {
        L.data[j-1]=L.data[j];
    }
    L.length--;
    return true;
}
int main()
{
    SqList L;
    InitList(L);
    int e=-1;
    if(ListDelete(L,3,e))
        cout<<"The "<< 3<<" brother element has been removed and the deleted element is "<<e<<" !"<<endl;
    else
        cout<<"The bit sequence i is invalid, and the deletion failed"<<endl;
    return 0;
}