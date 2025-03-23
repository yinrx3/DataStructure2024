#include <iostream>
using namespace std;
void sortarray(int* array,int n){
    int left=0;
    int right=n-1;
    while(left<right){
        while(left<right&&array[left]<0)
            ++left;
        while(left<right&&array[right]>=0)
            --right;
        if(left<right){
            swap(array[left],array[right]);
            ++left;
            --right;
        }
    }
}
int main(){
    int array[8]={1,-1,5,3,-2,6,-3,4};
    sortarray(array,8);
    for(int i=0;i<8;++i){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}