//494.目标和
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=0;
        for(int i=0;i<nums.size();++i) sum+=nums[i];
        if((sum-target)%2==1) return 0;
        if((sum-target)<0) return 0;
        int neg=(sum-target)/2;
        //下面问题就是能不能从nums里面选出数使得总数字等于neg
        int* dp=new int[neg+1];//dp[j]表示装满容量为j有多少种方法
        for(int i=0;i<=neg;++i){
            dp[i]=0;
        }
        dp[0]=1;
        for(int i=0;i<nums.size();++i){
            for(int j=neg;j>=nums[i];--j){
                dp[j]+=dp[j-nums[i]];
            }
        }
        return dp[neg];
    }
};

int findTargetSumWays(int n,int* nums, int target) {
    int sum=0;
    for(int i=0;i<n;++i){
        sum+=nums[i];
    }
    if(sum-target<0) return 0;
    if((sum-target)%2==1) return 0;
    int neg=(sum-target)/2;//实际上问的是凑成neg的方法由多少种
    int** dp=new int*[n];
    for(int i=0;i<n;++i){
        dp[i]=new int[neg+1];
        for(int j=0;j<=neg;++j){
            dp[i][j]=0;
        }
    }//下面进行初始化dp[0][?]
    dp[0][0]=1;
    if(nums[0]<=neg){
        dp[0][nums[0]]+=1;
    }

    for(int i=1;i<n;++i){
        for(int j=1;j<=neg;++j){
            dp[i][j]=dp[i-1][j];
            if(j-nums[i]>=0){
                dp[i][j]+=dp[i-1][j-nums[i]];
            }
        }
    }
    return dp[n-1][neg];
}
