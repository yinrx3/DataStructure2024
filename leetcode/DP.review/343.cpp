//343整数拆分
#include <iostream>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        int* dp=new int[n+1];//dp[i]表示i可以被拆分之后最大乘积
        for(int i=0;i<=n;++i){
            dp[i]=0;
        }
        dp[2]=1;
        if(n==2) return 1;
        dp[3]=2;
        //下面要确定状态转移方程
        for(int i=4;i<=n;++i){
            for(int j=1;j<i-1;++j){
                dp[i]=max(dp[i],max((i-j)*j,dp[i-j]*j));
            }
        }
        return dp[n];
    }
};

int main(){
    Solution s;
    cout<<s.integerBreak(9)<<endl;
}