//零钱兑换，返回硬币最少总个数
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int* dp=new int[amount+1];
        for(int i=0;i<=amount;++i){
            dp[i]=INT_MAX;
        }
        dp[0]=0;//以上是初始化过程
        //下面要列出状态转移方程
        for(int i=1;i<=amount;++i){//遍历背包
            for(int j=0;j<coins.size();++j){//遍历物品
                if(i-coins[j]>=0&&dp[i-coins[j]]!=INT_MAX){
                    dp[i]=min(dp[i],dp[i-coins[j]]+1);
                }
            }
        }
        int result=(dp[amount]==INT_MAX)?-1:dp[amount];
        delete [] dp;
        return result;
    }
};