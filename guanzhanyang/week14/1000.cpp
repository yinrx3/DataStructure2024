#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

/* UPLOAD START */

template <class T>
class ASet{ // for now we assume datatype T can be sorted
    private:
        T* set;
        int num;
    public:
        ASet(){
            num=0;
        }
        ASet(T* arr, int n){ //incoming array is guaranteed not to have duplicates.
            num=n;
            set=new T[n];
            for(int i=0;i<num;++i){
                set[i]=arr[i];
            }
        }
        ~ASet(){
            delete[] set;
        }
        void addEle(T x){
            //先看x是不是已经在集合里面了
            for(int i=0;i<num;++i){
                if(set[i]==x) return ;
            }
            ++num;
            T* newset=new T[num];
            for(int i=0;i<num-1;++i){
                newset[i]=set[i];
            }
            newset[num-1]=x;
            set=newset;
        }
        bool isEmpty(){
            return num==0;
        }
        bool removeEle(T x){
            // returns true if removed.
            // returns false if it is not in the set
            bool result=false;
            for(int i=0;i<num;++i){
                if(set[i]==x){
                    result=true;
                }
            }
            if(!result) return false;

            //下面说明在里面
            
        }
        bool hasEle(T x){
            
        }
        bool isSubsetOf(ASet<T>* S){
            
        }
        bool containsSet(ASet<T>* S){
            
        }
        bool isDisjointFrom(ASet<T>* S){
            
        }
        int cardinality(){
            
        }
        ASet<T>* setUnion(ASet<T>* S){
            
        }
        ASet<T>* intersect(ASet<T>* S){
            
        }
        ASet<T>* subtract(ASet<T>* S){
            
        }
        ASet<T>* symDiff(ASet<T>* S){
            
        }
        void printSet(){ //print the elements of S in ascending order
            
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