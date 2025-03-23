#include <iostream>
using namespace std;


template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
        
        void flipList(){
            for(int i=0;i<length/2;++i)
            {
                T x=arr[i];
                arr[i]=arr[length-i-1];
                arr[length-i-1]=x;
            }


        }
        
        void rotateList(int n){
            for(int i=0;i<n;++i)
            {
                T x=arr[length-1];
                for(int j=length-2;j>=0;--j)
                {
                    arr[j+1]=arr[j];
                }
                arr[0]=x;
            }
        }
};
/* Upload END */

void test1(){
    VecList<int> L;
    for(int i=0;i<10;i++){
        L.insertEleAtPos(i,i);
    }
    L.printList();
    cout << endl;
    L.flipList();
    L.printList();
    cout << endl;
    L.flipList();
    L.printList();
    cout << endl;
}

void test2(){
    VecList<int> L;
    for(int i=0;i<20;i++){
        L.insertEleAtPos(i,i);
    }
    L.printList();
    cout << endl;
    for(int i=0;i<5;i++){
        L.rotateList(3);
        L.printList();
        cout << endl;
    }
}


int main(){
    test1();
    test2();
    return 0;
}