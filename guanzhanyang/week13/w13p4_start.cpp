#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

class PancakeStack{
    private:
        int* stacksizes;
        int numCakes;
    public:
        PancakeStack(){
            stacksizes = NULL;
            numCakes = 0;
        }
        PancakeStack(int* sizes, int n){
            stacksizes = NULL;
            setStackSizes(sizes,n);
        }
        ~PancakeStack(){
            if(stacksizes!=NULL) delete [] stacksizes;
        }
        void setStackSizes(int* sizes, int n){
            if(stacksizes!=NULL) delete [] stacksizes;
            stacksizes = new int[n];
            numCakes = n;
            for(int i=0;i<n;i++){
                stacksizes[i] = sizes[i];
            }
        }
        void printsizes(){
            for(int i=0;i<numCakes;i++){
                cout << left << setw(6) << stacksizes[i];
                if(i%10==9) cout << endl;
            }
            cout << endl;
        }
        int getStackSize(){
            return numCakes;
        }
        int getSizeAtPos(int x){
            return stacksizes[x];
        }
        void flip(int k){
            // flip the cakes from stacksizes[0] through stacksizes[k] around.
            // (0,1,2,3,4,5,...,k,k+1,...,n) -> (k,k-1,...,1,0,k+1,...,n)
            int tmp = 0;
            for(int i=0;i<k-i;i++){
                tmp = stacksizes[i];
                stacksizes[i] = stacksizes[k-i];
                stacksizes[k-i] = tmp;
            }
        }
};

/* UPLOAD START */

void sortCakes(PancakeStack &x){
    // TODO
    // arrange cakes from small to large.
    int n=x.getStackSize();
    for(int i=n-1;i>0;i--){
        //不断找出前i个中最大的，放到前i个的最后面
        int maxPos=0;
        for(int j=1;j<=i;++j){
            if(x.getSizeAtPos(maxPos)<x.getSizeAtPos(j)){
                maxPos=j;
            }
        }
        if(maxPos==i) continue;
        if(maxPos!=0) x.flip(maxPos);
        x.flip(i);
    }
}

/* UPLOAD END */

void test1(){
    int cakes[10] = {9,7,3,2,10,1,5,6,8,4};
    PancakeStack pcs(cakes,10);
    
    sortCakes(pcs);
    pcs.printsizes();
}

int main(){
    test1();
    return 0;
}
