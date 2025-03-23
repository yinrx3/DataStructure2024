#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
     /* time */
#include <iomanip>
#include <algorithm>
using namespace std;

/* UPLOAD START */

template <class T>
class ASet{ // for now we assume datatype T can be sorted
    private:
        T* elements;
        int size;
        int capacity;

        void resize(int newCapacity){
            T* newElements=new T[newCapacity];
            for(int i=0;i<size;++i){
                newElements[i]=elements[i];
            }
            delete [] elements;
            elements=newElements;
            capacity=newCapacity;
        }
    public:
        ASet():capacity(10),size(0)
        {
            elements=new T[capacity];
        }
        ASet(T* arr, int n):capacity(n>10?n:10),size(0)
        { //incoming array is guaranteed not to have duplicates.
            elements=new T[capacity];
            for(int i=0;i<n;++i){
                addEle(arr[i]);
            }
        }
        ~ASet(){
            delete[] elements;
        }
        void addEle(T x){
            if(hasEle(x)) return ;
            if(size==capacity){
                resize(capacity*2);
            }
            elements[size++]=x;
        }
        bool isEmpty(){
            return size==0;
        }
        bool removeEle(T x){
            // returns true if removed.
            // returns false if it is not in the set
            for(int i=0;i<size;++i){
                if(elements[i]==x){
                    elements[i]=elements[--size];
                    return true;
                }
            }
            return false;

        }
        bool hasEle(T x){
            for(int i=0;i<size;++i){
                if(elements[i]==x){
                    return true;
                }
            }
            return false;
        }
        bool isSubsetOf(ASet<T>* S){
            for(int i=0;i<size;++i){
                if(!S->hasEle(elements[i])){
                    return false;
                }
            }
            return true;
        }
        bool containsSet(ASet<T>* S){
            return S->isSubsetOf(this);
        }
        bool isDisjointFrom(ASet<T>* S){
            //本集合中的元素在S中全部找不到
            for(int i=0;i<size;++i){
                //如果找到了返回false
                if(S->hasEle(elements[i])){
                    return false;
                }
            }
            return true;
        }
        int cardinality(){
            return size;
        }
        ASet<T>* setUnion(ASet<T>* S){
            ASet<T>* result=new ASet<T>();
            for(int i=0;i<size;++i){
                result->addEle(elements[i]);
            }
            for(int i=0;i<S->size;++i){
                result->addEle(S->elements[i]);
            }
            return result;
        }
        ASet<T>* intersect(ASet<T>* S){
            ASet<T>* result=new ASet<T>();
            for(int i=0;i<size;++i){
                if(S->hasEle(elements[i])){
                    result->addEle(elements[i]);
                }
            }
            return result;
        }
        ASet<T>* subtract(ASet<T>* S){
            ASet<T>* result=new ASet<T>();
            for(int i=0;i<size;++i){
                if(!S->hasEle(elements[i])){
                    result->addEle(elements[i]);
                }
            }
            return result;
        }

        ASet<T>* symDiff(ASet<T>* S) {
            ASet<T>* result = new ASet<T>();
            for (int i = 0; i < size; ++i) {
                if (!S->hasEle(elements[i])) {
                    result->addEle(elements[i]);
                }
            }
            for (int i = 0; i < S->size; ++i) {
                if (!hasEle(S->elements[i])) {
                    result->addEle(S->elements[i]);
                }
            }
            return result;
        }

    void printSet() {
        //这里只要对集合进行排序即可
        for(int i=0;i<size-1;++i){
            bool swaped=false;
            for(int j=0;j<size-i-1;++j){
                if(elements[j]>elements[j+1]){
                    swap(elements[j],elements[j+1]);
                    swaped=true;
                }
            }
            if(!swaped){
                break;
            }
        }


        cout<<"{";
        for(int i=0;i<size;++i){
            if(i<size-1){
                cout<<elements[i]<<",";
            }
            if(i==size-1){
                cout<<elements[i]<<"}"<<endl;
            }
        }
    }
};

/* UPLOAD END */

void simpleTest(){
    ASet<int> A;
    for(int i=1;i<=4;i++){
        A.addEle(i);
    }
    cout << "Set A: ";
    A.printSet();
    cout << "Cardinality of A: " << A.cardinality() << endl << endl;
    
    int tmpB[4] = {3,6,5,4};
    ASet<int> B(tmpB,4);
    cout << "Set B: ";
    B.printSet();
    cout << "Cardinality of B: " << B.cardinality() << endl << endl;
    
    ASet<int>* C = A.intersect(&B);
    ASet<int>* D = A.subtract(&B);
    
    cout << "Intersecting A and B gets set C, ";
    C->printSet();
    cout << "Union of A and B is ";
    (A.setUnion(&B))->printSet();
    cout << "Let set D be the set of elements in A but not B. Then set D is ";
    D->printSet();
    cout << "Symmetric difference of A and B is ";
    (A.symDiff(&B))->printSet();
    
    cout << endl << "Checking subset relations:" << endl;
    cout << "A " << (A.containsSet(C) ? "contains" : "does not contain") << " set C" << endl;
    cout << "B " << (B.containsSet(D) ? "contains" : "does not contain") << " set D" << endl;
    cout << "C is " << (C->isSubsetOf(&A) ? "" : "not ") << "a subset of A" << endl;
    cout << "D is " << (D->isSubsetOf(&B) ? "" : "not ") << "a subset of B" << endl;
}

int main(){
    simpleTest();
    return 0;
}