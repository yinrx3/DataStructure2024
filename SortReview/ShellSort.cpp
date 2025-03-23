#include <iostream>
using namespace std;
//希尔排序实质上是插入排序的优化版
//时间复杂度 最好 O(n) 最坏 O(n^2) 平均O(n^1.3) 辅助空间O(1) 不稳定排序
void ShellSort(int a[],int n){
    //取序列长度的一半，每次折半，直到为1
    for(int d=n/2;d>=1;d/=2){//对每个组分别进行插入排序,插入排序是可以直接从第2个数开始的，第一个数默认有序
        for(int i=d;i<n;i++){//第一个数默认有序，如果是第一组第二个数字下标是0+d
            //直接插入排序的代码
            if(a[i]<a[i-d]){
                int temp=a[i];
                int j=i-d;
                do{
                    a[j+d]=a[j];
                    j-=d;
                }while(j>=0&&a[j]>temp);
                a[j+d]=temp;
            }
        }
    }
}

int main(){
    int a[10]={2,12,18,24,37,25,9,63,3,7};
    ShellSort(a,10);
    for(int i=0;i<10;++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}

