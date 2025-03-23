#include <iostream>
using namespace std;
int main()
{
    //首先要有一个输入，保存的数据结构用数组
    int n,m;
    cin>>n>>m;
    int* arr=new int[n];
    for(int i=0;i<n;++i)
    {
        arr[i]=i+1;
    }


    int numleft=n;
    int i=0;
    int step=0;
    while(numleft!=0)
    {
        if(arr[i]==0){}
        if(arr[i]!=0&&step!=m)
        {
            ++step;
        }
        if(arr[i]!=0&&step==m)
        {
            cout<<arr[i]<<" ";
            arr[i]=0;
            --numleft;
            step=0;
        }
        if(i==n-1)
        {
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout<<endl;

    return 0;
}