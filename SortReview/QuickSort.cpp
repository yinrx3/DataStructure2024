#include <iostream>
using namespace std;
//快速排序
//复杂度分析 最好 时间 O(nlogn) 空间 O(logn)
//最坏 时间O(n^2) 空间 O(n)
//平均 时间O(nlogn) O(logn)
//不稳定排序
int Partition(int a[],int left,int right){//函数目的是将枢轴归位,返回归位后枢轴的位序
    int pivot=a[left];
    while(left<right){
        //这里相当于不断填坑挖坑
        while(left<right&&a[right]>=pivot) right--;//让r从右往左走，走到第一个小于pivot的,或者left==right
        a[left]=a[right];
        while(left<right&&a[left]<=pivot) left++;
        a[right]=a[left];
    }
    a[left]=pivot;//到这里的话left与right相等
    return left;
}

void QuickSort(int a[],int left,int right){
    if(left<right){//递归的结束条件(区间长度等于1,left=right和区间长度为0，left>right)
        int i=Partition(a,left,right);//这里的i实际上是枢轴归位后的位序,这里执行划分
        QuickSort(a,left,i-1);//递归左区间
        QuickSort(a,i+1,right);//递归右区间
    }
}
int main(){
    int a[10]={21,12,7,1,90,56,44,32,81,44};
    QuickSort(a,0,9);
    for(int i=0;i<10;++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}
