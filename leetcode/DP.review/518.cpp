//零钱兑换，返回凑成总金额的硬币组合数量
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int* dp=new int[amount+1];
        for(int i=0;i<=amount;++i){
            dp[i]=0;
        }
        dp[0]=1;
        for(int i=0;i<coins.size();++i){
            for(int j=coins[i];j<=amount;++j){
                dp[j]+=dp[j-coins[i]];
            }
        }
        return dp[amount];
    }
};

int main(){
    Solution s;
    cout<<"Coins <1,2,5,10,20,50,100> while change 80 to 120:"<<endl;
    vector<int> coins={1,2,5,10,20,50,100};
    for(int i=80;i<=120;++i){
        cout<<s.change(i,coins)<<" ";
    }
    cout<<endl;
}