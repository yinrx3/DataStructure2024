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
};

int main(){
    int r[3] = {1,2,3};
    VecList<int> L(r,3);
    cout << "Current List: " << endl;
    L.printList();
    cout << endl;
    try{
        L.insertEleAtPos(1,4);
        L.insertEleAtPos(4,5);
        L.insertEleAtPos(5,6);
        L.insertEleAtPos(6,7);
    }
    catch(const char* s){
        cout << s << endl;
    }
    cout << "After adding elements:" << endl;
    L.printList();
    cout << endl << "Searching for position of 3: " << L.locateEle(3) << endl;
    try{
        L.deleteEleAtPos(0);
    }
    catch(const char* s){
        cout << s << endl;
    }
    cout << "Now we have deleted element at position 0: " << endl;
    L.printList();
    cout << endl;
    
    VecList<int> L2(r,3);
    for(int i=3;i<=300;i++){
        L2.insertEleAtPos(i,i+1);
    }
    L2.printList();
    return 0;
}