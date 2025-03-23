//堆排序，这里尝试写小根堆的形式
//注意，堆排序平均最难和最简单时间复杂度均为O(nlogn),空间复杂度为O(1)
//堆排序不稳定
#include <iostream>
using namespace std;

void DownAdjust(int a[],int k,int n){
    int i=k;int j=2*i;//这里j是左孩子
    while(j<=n){
        if(j+1<=n&&a[j+1]<a[j]){
            //小根堆要找到最小的孩子
            j++;
        }
        //这里实际上是找到了更小孩子的下标
        if(a[j]<a[i]){
            //小根堆是将小的放在前面
            swap(a[i],a[j]);
            i=j;
            j=2*i;
        }
        else{break;}
    }
}

void HeapSort(int a[],int n){
    //首先完成建堆的过程，这里要创建的是小根堆的情况
    for(int i=n/2;i>=1;--i){
        DownAdjust(a,i,n);
    }
    //到这里完成建堆过程,下面进行输出
    for(int i=2;i<=n;++i){
        //这里i实际上是数组长度
        DownAdjust(a+i-1,1,n-i+1);
    }
}

int main(){
    int a[11]={-999,2,12,18,24,37,25,9,63,3,7};
    HeapSort(a,10);
    for(int i=1;i<11;++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}

