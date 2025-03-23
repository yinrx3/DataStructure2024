#include <iostream>
using namespace std;

/* UPLOAD START */
// You can use VecList, LinkList or none of these structures in writing the IntPolynomial class
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

class IntPolynomial{
    private:
        
    public:
        IntPolynomial(){
            
        }
        IntPolynomial(int * c, int * d, int n){
            
        }
        ~IntPolynomial(){
            
        }
        int getDegree(){
            
        }
        IntPolynomial* Add(IntPolynomial* b){
            
        }
        IntPolynomial* Subtract(IntPolynomial* b){
            
        }
        IntPolynomial* Multiply(IntPolynomial* b){

        }
        void printPolynomial(){
            
        }
};

/* UPLOAD END */

void test1(){    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    p4.printPolynomial();
}

void test2(){
    int p1c[3] = {3,5,-6};
    int p1d[3] = {0,1,4};
    IntPolynomial p1(p1c,p1d,3);
    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    
    p1.Add(&p4)->printPolynomial();
    p4.Subtract(&p1)->printPolynomial();
    
    p4.Add(&p4)->printPolynomial();
    p4.Subtract(&p4)->printPolynomial();
}

void test3(){
    int p1c[3] = {1,-1,5};
    int p1d[3] = {0,3,7};
    IntPolynomial p1(p1c,p1d,3);
    
    int p2c[4] = {1,1,6,10};
    int p2d[4] = {0,3,20,40};
    IntPolynomial p2(p2c,p2d,4);
    
    p1.Multiply(&p2)->printPolynomial();
}

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); 
        default:
        ;
    }
    return 0;
}