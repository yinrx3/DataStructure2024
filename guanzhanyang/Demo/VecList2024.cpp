#include <iostream>
using namespace std;

template <class T>
class VecList{
private:
    T* arr; // 
    int capacity; // 
    int length; // 

    void doubleListSize(){
        T* newArr = new T[2*capacity];
        for(int i=0;i<length;i++){
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = 2*capacity;
    }
public:
    VecList(){
        arr = new T[100];
        capacity = 100;
        length = 0;
    }
    VecList(T* a, int n){ // a �����ݵ����飬 n ��������
        arr = new T[100+2*n];
        capacity = 100+2*n;
        length = n;
        for(int i=0;i<n;i++){
            arr[i] = a[i];
        }
    }
    ~VecList(){
        delete[] arr;
    }
    int getLength(){
        return length;
    }
    bool isEmpty(){
        return length==0;
    }
    void insertEleAtPos(int i, T x){
        if(i<0 || i > length){
            throw "Illegal position";
        }
        if(capacity == length){
            doubleListSize();
        }
        for(int j=length-1;j>=i;j--){ // ��λ
            arr[j+1] = arr[j];
        }
        arr[i] = x;
        length++;
    }
    T deleteEleAtPos(int i){
        if(i < 0 || i >= length){
            throw "Illegal position";
        }
        T tmp = arr[i];
        for(int j=i+1;j<length;j++){
            arr[j-1] = arr[j];
        }
        length--;
        return tmp;
    }
    void setEleAtPos(int i, T x){
        if(i < 0 || i >= length){
            throw "Illegal position";
        }
        arr[i] = x;
    }
    T getEleAtPos(int i){
        if(i < 0 || i >= length){
            throw "Illegal position";
        }
        return arr[i];
    }
    int locateEle(T x){ // �ش� x �������д����ҵ�һ�γ��ֵ�λ��
        int k = 0;
        while(k < length){
            if(arr[k] == x) return k;
            else k++;
        }
        return -1;
    }
    void printList(){
        for(int i=0;i<length;i++){
            cout << arr[i] << " ";
        }
    }
};

int main(){
    VecList<int> v1;
    v1.insertEleAtPos(0,14);
    v1.insertEleAtPos(1,9);
    v1.printList();
    cout << endl;

    try{
        v1.insertEleAtPos(10,5);
    }
    catch(const char* s){
        cout << s << endl;
    }
    for(int i=30;i<40;i++){
        v1.insertEleAtPos(v1.getLength(),i);
    }
    v1.printList();
    cout << endl;

    v1.deleteEleAtPos(7);
    v1.printList();
    cout << endl;

    int pos33 = v1.locateEle(33);
    if(pos33!=-1) v1.deleteEleAtPos(pos33);
    v1.printList();
    cout << endl;

    string s[3] = {"Data","Structures","Algorithms"};
    VecList<string>* v2;
    v2 = new VecList<string>(s,3);

    v2->printList();
    cout << endl;

    return 0;
}
