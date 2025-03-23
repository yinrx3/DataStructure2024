#include <iostream>
#include <iomanip>
#include <stdlib.h> // for srand and rand

using namespace std;

template <class T>
class ArrayWrap{
    private:
        int length;
        T* baseArray;
        mutable int readCount; // mutable to allow modification in const functions
    public:
        ArrayWrap(){ // never actually used
            length = 0;
            baseArray = NULL;
            readCount = 0;
        }
        ArrayWrap(T* arr, int n){
            length = n;
            baseArray = arr;
            readCount = 0;
        }
        int getLength(){
            return length;
        }
        int getReadCount(){
            return readCount;
        }
        T& operator[](int pos){
            readCount++;
            return baseArray[pos];
        }
        const T& operator[](int pos) const{
            readCount++;
            return baseArray[pos];
        }
};

/* UPLOAD START */
// ques 1
int missingAPterm(ArrayWrap<int> &aw){
    // Requirement: runtime efficiency should be O(ln n)
    // This will be observed via readCount.
    // TODO
    int size=aw.getLength();
    int low=0;
    int high=size-1;
    int commondifference=(aw[high]-aw[low])/size;

    while(low<=high){
        int mid=low+(high-low)/2;
        if(aw[mid]==aw[0]+mid*commondifference){
            low=mid+1;
        }
        else if(aw[mid]>aw[0]+mid*commondifference){
            high=mid-1;
        }
    }
    return aw[0]+low*commondifference;
}
/* UPLOAD END */

/* UPLOAD START */
// ques 2
int maxEleBitonic(ArrayWrap<int> &aw){
    // Requirement: runtime efficiency should be O(ln n)
    // This will be observed via readCount.
    // TODO
    int left=0;
    int right=aw.getLength()-1;
    if(right==0) return aw[0];
    if(right==1) return aw[0]>aw[1]?aw[0]:aw[1];
    while(left<right){
        int mid=left+(right-left)/2;
        //判断是否在递增里面
        if(aw[mid]<aw[mid+1]){
            //说明mid右边仍然是递增的
            left=mid+1;
        }
        else{
            right=mid;
        }
    }
    return max(aw[left],max(aw[0],aw[aw.getLength()-1]));
}
/* UPLOAD END */

void test0(){
    // demonstrates usage of the class ArrayWrap
    int a[10];
    for(int i=0;i<10;i++){
        a[i] = i;
    }
    ArrayWrap<int> aw(a,10);
    int sum = 0;
    for(int i=0;i<aw.getLength();i++){
        sum += aw[i];
        aw[i] += 10;
    }
    cout << "Sum is " << sum << ", readCount is " << aw.getReadCount() << endl;
    for(int i=0;i<aw.getLength();i++){
        cout << aw[i] << " ";
    }
    cout << endl << "New readCount is " << aw.getReadCount() << endl;
}

void test2(){ // ques 2 test
    int a[10] = {1,3,5,7,9,13,15,17,19,21};
    int b[70];
    b[0] = 4;
    b[1] = 18;
    for(int i=2;i<70;i++){
        b[i] = b[i-1]+7;
    }
    
    ArrayWrap<int> aw1(a,10);
    ArrayWrap<int> aw2(b,70);
    
    cout << "Missing term for first sequence: " << missingAPterm(aw1);
    cout << ", readCount = " << aw1.getReadCount() << endl;
    cout << "Missing term for second sequence: " << missingAPterm(aw2);
    cout << ", readCount = " << aw2.getReadCount() << endl;
}

void test3(){ // ques 3 test
    int a[10] = {1,3,7,9,11,10,9,7,4,-1};
    int b[50];
    for(int i=0;i<50;i++){
        b[i] = i;
    }
    
    ArrayWrap<int> aw1(a,10);
    ArrayWrap<int> aw2(b,50);
    
    int d[1000];
    d[0] = 0;
    for(int i=1;i<1000;i++){
        d[i] = d[i-1] + 15;
        if(i==300) d[i]+= 15;
    }
    
    ArrayWrap<int> aw4(d,1000);
    
    cout << "Max term in first sequence: " << maxEleBitonic(aw1);
    cout << ", readCount = " << aw1.getReadCount() << endl;
    cout << "Max term in second sequence: " << maxEleBitonic(aw2);
    cout << ", readCount = " << aw2.getReadCount() << endl;
    
    // Stress Test
    cout << "Max term in third sequence: " << maxEleBitonic(aw4);
    cout << ", readCount = " << aw4.getReadCount() << endl;
    cout << (aw4.getReadCount() == 0 ? "Cheater " : "") << (aw4.getReadCount() < 150 ? "Passed" : "Failed") << endl;
}

int main(){
    //test0(); // test the use of class ArrayWrap
    //test2();
    cout << endl;
    test3();
    
    return 0;
}
