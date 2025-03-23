#include <iostream>
using namespace std;
//这里学习大根堆的形式
void HeapSort(int a[],int n);
void DownAdjust(int a[],int k,int n);

//这里默认数组a已经是排序数据从下标1开始的
void HeapSort(int a[],int n){
    for(int i=n/2;i>=1;--i){
        //从第一个非叶子结点开始调整，最后一个叶子下标是n,它的双亲节点是最后一个非叶子结点，下标是n/2当然向下取整
        DownAdjust(a,i,n);
    }
    for(int i=n;i>=2;i--){
        //这里的i实际上指的是剩下来的堆长度
        swap(a[1],a[i]);
        DownAdjust(a,1,i-1);
    }
}

void DownAdjust(int a[],int k,int n){//接受三个参数，数组a,要调整的节点的下标k,长度n
    int i=k;//i是要调整的结点
    int j=i*2;//下标j代表的是要调整结点的左孩子
    while(j<=n){//判断最多调整到叶子结点
        //将i和它的孩子进行比较
        //可以直接让i和孩子中那个较大的作对比
        if(j+1<=n&&a[j+1]>a[j]){
            j++;//右孩子存在且大于左孩子，就让j指向右孩子
        }
        //执行到这里，j是更大孩子的下标（如果有右孩子）
        if(a[i]<a[j]){
            swap(a[i],a[j]);
            i=j;
            j=i*2;
        }
        else{
            break;
        }
    }
}

int main(){
    int a[11]={-999,23,12,18,24,26,25,9,4,3,7};
    HeapSort(a,10);
    for(int i=1;i<11;++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;

}