#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

int quad_probe_next(int st, int tryNum){
    //quadratic probing scheme
    if(tryNum%2==1) return st+((tryNum+1)/2)*((tryNum+1)/2);
    else return st - (tryNum/2) * (tryNum/2);
}

int linear_probe_next(int st, int tryNum){
    return st + tryNum;
}

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
class miniHashTable{
    private:
        int tableSize; // hashtable size better be a prime that is 11 mod 12.
        int numData;
        T* hashEntries;
        bool* inUse;
        bool* onceUsed;
        int (*hashfn)(T,int);
        int (*probefn)(int,int);
        int collisions = 0;
    public:
        miniHashTable(){
            //default table size set as 47
            numData = 0;
            collisions = 0;
            tableSize = 47;
            hashEntries = new T[47];
            inUse = new bool[47];
            onceUsed = new bool[47];
            for(int i=0;i<47;i++){
                inUse[i] = false;
                onceUsed[i] = false;
            }
            hashfn = NULL;
            probefn = NULL;
        }
        miniHashTable(int table_size){
            // pray that whatever's given to us is a prime. or else things can get real ugly.
            numData = 0;
            collisions = 0;
            tableSize = table_size;
            hashEntries = new T[table_size];
            inUse = new bool[table_size];
            onceUsed = new bool[table_size];
            for(int i=0;i<table_size;i++){
                inUse[i] = false;
                onceUsed[i] = false;
            }
            hashfn = NULL;
            probefn = NULL;
        }
        ~miniHashTable(){
            delete [] hashEntries;
            delete [] inUse;
            delete [] onceUsed;
        }
        void setHashFn(int (*f)(T, int)){
            if(hashfn==NULL)
                hashfn = f;
            else{
                cout << "Cannot reset hash function." << endl;
            }
        }
        void setProbeFn(int (*f)(int,int)){
            if(probefn==NULL)
                probefn = f;
            else{
                cout << "Cannot reset probe function." << endl;
            }
        }
        bool isEmpty(){
            return (numData==0);
        }
        bool isFull(){
            return (numData==tableSize);
        }
        bool searchData(T x){
            int k=0;
            int hashCell = hashfn(x,tableSize);
            int hashNext = hashCell;
            while(onceUsed[hashNext]){
                k++;
                if(hashEntries[hashNext]==x) return true;
                else hashNext = probefn(hashCell+tableSize,k) % tableSize;
            }
            return false;
        }
        void insertData(T x){
            int k=0;
            if(isFull()){
                cout << "Table full." << endl;
                return;
            }
            int hashCell = hashfn(x,tableSize);
            int hashNext = hashCell;
            while(inUse[hashNext]){
                k++;
                hashNext = probefn(hashCell+tableSize,k) % tableSize;
                collisions++;
            }
            numData++;
            hashEntries[hashNext] = x;
            inUse[hashNext] = true;
            onceUsed[hashNext] = true;
        }
        void deleteData(T x){
            int k=0;
            int hashCell = hashfn(x,tableSize);
            int hashNext = hashCell;
            while(inUse[hashNext]){
                k++;
                if(hashEntries[hashNext]==x){
                    inUse[hashNext] = false;
                    numData--;
                    return;
                }
                else hashNext = probefn(hashCell+tableSize,k) % tableSize;
            }
            return;
        }
        void printTable(){
            for(int i=0;i<tableSize;i++){
                cout << "Cell " << i << ": ";
                if(inUse[i]) cout << hashEntries[i];
                cout << endl;
            }
        }
        int getCollisionCount(){
            return collisions;
        }
};

void test(int (*h)(int,int),int (*p)(int,int)){
    miniHashTable<int> ht(23); //the table with 47 entries should be fine.
    ht.setHashFn(h);
    ht.setProbeFn(p);
    int randomNums[15];
    for(int i=0;i<15;i++)
        randomNums[i] = rand() % 10000;
    for(int i=0;i<15;i++){
        cout << randomNums[i] << " (" << h(randomNums[i],23) << "), ";
        ht.insertData(randomNums[i]);
        if(i%5==4){
            cout << endl;
            cout << "Current Table is as follows:" << endl;
            ht.printTable();
            cout << endl;
        }
    }
    cout << "Collision count: " << ht.getCollisionCount() << endl;
    cout << endl;
}

int main()
{
    srand(time(NULL));
    cout << "Simplest hash and linear probe:" << endl;
    test(hash1,linear_probe_next);
    
    cout << "Simplest hash and quadratic probe:" << endl;
    test(hash1,quad_probe_next);
    
    cout << "Not so simple hash and linear probe:" << endl;
    test(hash2,linear_probe_next);
    
    cout << "Simplest hash and linear probe:" << endl;
    test(hash2,quad_probe_next);

    return 0;
}
