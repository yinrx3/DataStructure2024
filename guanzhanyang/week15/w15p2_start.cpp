#include <iostream>
#include <stdlib.h>
using namespace std;

/* UPLOAD START */

int maxQuadProduct(int* arr, int n){
    // TODO
    for(int i=0;i<n-1;++i){
        for(int j=0;j<n-1-i;++j){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }

    int max1=arr[n-1]*arr[n-2]*arr[n-3]*arr[n-4];
    int max2=arr[0]*arr[1]*arr[2]*arr[3];
    int max3=arr[0]*arr[1]*arr[n-1]*arr[n-2];

    return max(max1,max(max2,max3));
}

/* UPLOAD END */

void test1(){
    int tmp1[7] = {3,7,5,1,9,10,2};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,7) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    cout << endl;
}

int main()
{
    test1();
    return 0;
}
