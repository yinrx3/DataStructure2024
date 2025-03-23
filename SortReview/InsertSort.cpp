#include <iostream>
using namespace std;
//插入排序
//更好的策略是一边比较一边向后移动

//核心思想是不断向有序区里面增加元素
void InsertSort(int a[],int n){
    //n是元素的个数
    for(int i=1;i<n;++i){
        //第一个数字默认是有序的
        if(a[i]<a[i-1]){//只有小于前一个才需要进行插入操作
            //这里满足if后放进去，进行一边移动一边插入操作
            int temp=a[i];
            //下面是倒着一个一个比较
            int j=i-1;
            do{
                a[j+1]=a[j];
                j--;
            }while(j>=0&&temp<a[j]);//重点，这里while判断里面两个条件不能颠倒,因为首先保证j是由越界
            a[j+1]=temp;
        }
    }
}
//复杂度分析 时间最好O(n) 最坏O(n^2) 平均O(n^2) 辅助空间O(1) 稳定排序 

int main(){
    int a[10]={21,12,7,1,90,56,44,32,81,44};
    InsertSort(a,10);
    for(int i=0;i<10;++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}
