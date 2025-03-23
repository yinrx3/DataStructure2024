#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <string>
using namespace std;

int hash1(int x, int hashMax){
    return x % hashMax;
}

int hash2(int x, int hashMax){
    // Here, hashMax needs to be 2 mod 3.
    int tmp1 = x%hashMax;
    int tmp2 = (tmp1 * tmp1) % hashMax;
    tmp2 = (tmp2 * tmp1) % hashMax;
    return tmp2;
}

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
        void insertLast(T x){
            insertEleAtPos(length,x);
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

/* UPLOAD START */

template <class T>
class OpenHashTable{
    private:
		// other variables?
		int tableSize;
        int numData;

        VecList<T>* colli;


        int (*hashfn)(T,int);

        int collisions=0;
    public:
        OpenHashTable(){
            //default table size set as 47
            numData=0;
            tableSize=47;
            colli=new VecList<T>[tableSize];
            hashfn = NULL;
        }
        OpenHashTable(int table_size){
            // pray that whatever's given to us is a prime. or else things can get real ugly.
            numData=0;
            tableSize=table_size;
            colli=new VecList<T>[tableSize];
            hashfn = NULL;
        }
        ~OpenHashTable(){
            delete[] colli;
        }
        void setHashFn(int (*f)(T, int)){
            if(hashfn==NULL)
                hashfn = f;
            else{
                cout << "Cannot reset hash function." << endl;
            }
        }
        bool isEmpty(){
            return numData==0;
        }
        bool searchData(T x){
            int hashCur=hashfn(x,tableSize);
            return (colli[hashCur].locateEle(x) != -1);
        }

        void insertData(T x){
            int posAdd = hashfn(x, tableSize);
            if (colli[posAdd].isEmpty()) {
                colli[posAdd].insertLast(x);
                return;
            }
            else {
                colli[posAdd].insertLast(x);
                collisions++;
                return;
            }
        }
        void deleteData(T x){
            int posAdd = hashfn(x, tableSize);
            int xpos = colli[posAdd].locateEle(x);
            if (xpos != -1) colli[posAdd].deleteEleAtPos(xpos);
        }

        void myinsertData(T x){
            if(searchData(x)) return ;

            int hashCur=hashfn(x,tableSize);
            if(!colli[hashCur].isEmpty()) ++collisions;
            colli[hashCur].insertLast(x);
            ++numData;
        }
        void mydeleteData(T x){
            if(!searchData(x)) return ;

            int hashCur=hashfn(x,tableSize);
            int pos = colli[hashCur].locateEle(x);
            if(pos != -1) {  // 确保位置有效
                colli[hashCur].deleteEleAtPos(pos);
                --numData;
            }
        
        }

        void printTable(){
            for(int i=0;i<tableSize;++i){
                if(!colli[i].isEmpty()){
                    cout<<"Cell "<<i<<": ";
                    colli[i].printList();
                    cout<<endl;
                }
            }
        }
        int getCollisionCount(){
            return collisions;
        }
};

/* UPLOAD END */

void test1(int (*h)(int, int)){
    OpenHashTable<int> ht(23); //the table with 23 entries should be fine.
    ht.setHashFn(h);
    int randomNums[20];
    for(int i=0;i<20;i++)
        randomNums[i] = rand() % 10000;
    for(int i=0;i<20;i++){
        ht.insertData(randomNums[i]);
    }
    ht.printTable();
    cout << "Collision count: " << ht.getCollisionCount() << endl;
    cout << endl;
}

int main()
{
    srand(123456);
    test1(hash1);
	
    return 0;
}
