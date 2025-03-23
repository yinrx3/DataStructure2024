#include <iostream>
using namespace std;

//首先是堆排序首先来实现大根堆形式
//注意，堆排序平均最难和最简单时间复杂度均为O(nlogn),空间复杂度为O(1)
//堆排序不稳定
void BigDownAdjust(int a[],int k,int n){//接受数组,要调整的结点下标，元素总个数
    int i=k;int j=i*2;//i是节点，j是节点的左孩子
    while(j<=n){
        //由于是大根堆，希望找到最大的孩子
        if(j+1<=n&&a[j+1]>a[j]){
            ++j;
        }//以上已经找到了最小的孩子，可能仍然保持为左孩子
        //下面是交换条件
        if(a[i]<a[j]){
            swap(a[i],a[j]);
            i=j;
            j=2*i;
        }
        else{break;}//不需要调整就说明这个节点为根的堆已经构建完成
    }
}

void HeapSort(int a[],int n){//接受数组头空元素地址,和元素的个数
    //首先要完成建堆过程
    for(int i=n/2;i>=1;--i){
        BigDownAdjust(a,i,n);
    }//到这一步完成了建堆过程
    //下面是输出过程
    for(int i=n;i>=2;--i){
        swap(a[i],a[1]);
        BigDownAdjust(a,1,i-1);
    }
}

//快速排序
//复杂度分析 最好 时间 O(nlogn) 空间 O(logn)
//最坏 时间O(n^2) 空间 O(n)
//平均 时间O(nlogn) O(logn)
//快速排序不稳定排序
int Partition(int a[],int left,int right){
    int pivot=a[left];
    while(left<right){//下面就是两边不断来填坑,先填左边的坑，再填右边的坑
        while(left<right&&a[right]>=pivot) right--;
        a[left]=a[right];
        while(left<right&&a[left]<=pivot) left++;
        a[right]=a[left];
    }
    a[left]=pivot;
    return left;
}

void QuickSort(int a[],int left,int right){
    if(left<right){
        int pivotIndex=Partition(a,left,right);
        QuickSort(a,left,pivotIndex-1);
        QuickSort(a,pivotIndex+1,right);
    }
}

//插入排序
//更好的策略是一边比较一边向后移动
//核心思想是不断向有序区里面增加元素
//复杂度分析 时间最好O(n) 最坏O(n^2) 平均O(n^2) 辅助空间O(1) 稳定排序 
void InsertSort(int a[],int n){
    for(int i=1;i<n;++i){//第一个元素只有一个元素默认是有序的
        if(a[i]<a[i-1]){//只有下面的元素小于有序区才需要进行插入排序
            int temp=a[i];//i是有序区后面的第一个元素,i-1是有序区最后一个元素
            int j=i-1;
            do{
                a[j+1]=a[j];
                --j;
            }while(j>=0&&temp<a[j]);
            a[j+1]=temp;
        }
    }
}





