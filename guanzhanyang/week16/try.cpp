#include <iostream>
#include <iomanip>
using namespace std;

/* UPLOAD START */

template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        T* a;
        int length=0;
        int capacity;
    public:
        AMinHeap(){
            capacity=100;
            a=new T[capacity];
        }
        AMinHeap(T* arr, int n){
            length=n;
            if(n>=capacity){
                capacity=2*n;
                T* newa=new T[capacity];
                delete a;
                a=newa;
            }
            for(int i=1;i<=n;++i){
                a[i]=arr[i-1];
            }

            //下面是建堆过程
            for(int i=length/2;i>=1;--i){
                DownAdjust(a,i,length);
            }
        }

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

        ~AMinHeap(){
            delete[] a;
        }
        bool isEmpty(){
            return length==0;
        }
        T getMin(){
            if(length==0) throw"Heap Empty";
            return a[1];
        }
        void push(T x){
            ++length;
            if(length>=capacity){
                capacity=2*length;
                T* newa=new T[capacity];
                for(int i=1;i<=length-1;++i){
                    newa[i]=a[i];
                }
            }
            a[length]=x;
            UpAdjustLast(a,length);
        }

        void UpAdjustLast(int a[],int n){
            //这里是前面的已经是堆，调整放进去的最后一个结点
            int j=n;
            int i=j/2;//双亲节点
            while(i>=1){
                if(a[i]>a[j]){
                    swap(a[i],a[j]);
                    j=i;
                    i=j/2;
                }
                else{break;}
            }
        }

        T delMin(){
            
        }
        T* getLevelOrderArray(){
            
        }
        int getNumData(){
            return length;
        }
};

/* UPLOAD END */

template <class T>
void printLevelOrder(T* data, int numItems){ //assumes class T has an overloaded ostream << operator.
    for(int i=1;i<=numItems;i++){
        cout << data[i] << " ";
    }
}

int test1(){ // normal test
    AMinHeap<int> amh;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    amh.push(10);
    amh.push(8);
    amh.push(6);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    amh.push(4);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    
    cout << "Top: " << amh.getMin() << endl;
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    
    cout << "Popping:" << endl;
    while(!amh.isEmpty()){
        cout << "Current Min: " << amh.delMin() << endl;
        cout << endl;
    }
    return 0;
}

int main(){
    //unit test for Heap.
    test1();
    return 0;
}