#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

template<class T>
class miniHashTable{
    private:
        int tableSize; // hashtable size better be a prime that is 11 mod 12.
        //哈希表的大小，最好是一个正数
        int numData;//存储的数据数量
        T* hashEntries;//存储数据的数组
        bool* inUse;//标记某个位置是否被占用
        bool* onceUsed;//标记某个位置是否曾经被占用

        //下面两个是哈希函数指针和探测函数指针
        int (*hashfn)(T,int);
        int (*probefn)(int,int);

        int collisions=0;
    
    public:
        


};