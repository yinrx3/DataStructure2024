//96.不同的二叉搜索树
#include <iostream>
using namespace std;
class Solution {
public:
    int numTrees(int n) {
        int* dp=new int[n+1];
        for(int i=0;i<=n;++i){
            dp[i]=0;
        }
        dp[0]=1; if(n>=1) dp[1]=1;
        if(n==0) return 1;
        if(n==1) return 1;
        for(int i=2;i<=n;++i){
            for(int j=1;j<=i;++j){
                dp[i]+=dp[j-1]*dp[i-j];
            }
        }
        return dp[n];
    }
};

int main(){
    Solution s;
    for(int i=0;i<=18;++i){
        cout<<s.numTrees(i)<<" ";
    }
    cout<<endl;
    
}