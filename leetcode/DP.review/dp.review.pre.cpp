#include <iostream>
#include <vector>
using namespace std;

//96不同的二叉搜索树
//给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
int numTrees(int n){
    int* dp=new int[n+1];
    for(int i=0;i<=n;++i) dp[i]=0; 
    if(n==0) return 1;
    if(n==1) return 1;
    dp[0]=1;dp[1]=1;//以上初始化好了
    for(int i=2;i<=n;++i){
        for(int j=0;j<=i-1;++j){
            dp[i]+=dp[i-1-j]*dp[j];
        }
    }
    return dp[n];
}

//322零钱兑换，返回需要零钱最小个数，不能兑换就返回-1
int coinChange(vector<int>& coins,int amount){
    int* dp=new int[amount+1];
    for(int i=0;i<=amount;++i) dp[i]=INT_MAX;
    dp[0]=0;//如果总金额是0,那么最小个数是0
    for(int i=1;i<=amount;++i){
        for(int j=0;j<coins.size();++j){
            if(i-coins[j]>=0&&dp[i-coins[j]]!=INT_MAX){
                dp[i]=min(dp[i],dp[i-coins[j]]+1);
            }
        }
    }
    int result=(dp[amount]==INT_MAX)?-1:dp[amount];
    delete[] dp;
    return result;
}

//343整数拆分
//给定一个正整数n将其拆分为k个正整数的和(k>=2),并使这些整数的乘积最大化.返回你可以获得的最大乘积
int integerBreak(int n){
    int* dp=new int[n+1];
    for(int i=0;i<=n;++i) dp[i]=0;
    dp[2]=1; if(n==2) return 1;
    dp[3]=2;
    for(int i=4;i<=n;++i){
        for(int j=1;j<=i;++j){
            dp[i]=max(dp[i],max(j*(i-j),j*dp[i-j]));
        }
    }
    return dp[n];
}

int main(){
    cout<<"The number of nodes is the number of binary search trees of n : ";
    for(int i=0;i<=10;++i){
        cout<<numTrees(i)<<" ";
    }
    cout<<endl;

    cout<<"Coins <1,2,5,10,20,50,100> while change 80 to 120:"<<endl;
    vector<int> coins={1,2,5,10,20,50,100};
    for(int i=80;i<=120;++i){
        cout<<coinChange(coins,i)<<" ";
    }
    cout<<endl;

    cout<<"The product of the elements obtained by splitting integer 2 to 20 is at most :"<<endl;
    for(int i=2;i<=20;++i){
        cout<<integerBreak(i)<<" ";
    }cout<<endl;

}