//416 分割等和子集
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=0;
        for(int i=0;i<nums.size();++i) sum+=nums[i];
        if(sum%2==1) return false;
        int target=sum/2;
        int* dp=new int[target+1];
        for(int i=0;i<=target;++i){
            dp[i]=0;
        }
        for(int i=0;i<nums.size();++i){
            for(int j=target;j>=nums[i];--j){
                dp[j]=max(dp[j],dp[j-nums[i]]+nums[i]);
            }
        }
        return dp[target]==target;
    }
};

bool canPartition(int* nums,int n){
    int sum=0;
    for(int i=0;i<n;++i) sum+=nums[i];
    if(sum%2==1) return false;
    int target=sum/2;
    //这里用二维数组处理
    int** dp=new int*[n];
    for(int i=0;i<n;++i){
        dp[i]=new int[target+1];
        for(int j=0;j<=target;++j){
            dp[i][j]=0;
        }
    }
    //dp[i][0]恒为0,dp[0][j] ?
    for(int j=1;j<=target;++j){
        if(j-nums[0]>=0){
            dp[0][j]=nums[0];
        }
    }

    //这里dp[i][j]表示下标0到i能够凑到不大于j的最大数字
    for(int i=1;i<=n-1;++i){
        for(int j=1;j<=target;++j){
            if(j<nums[i]){dp[i][j]=dp[i-1][j];}
            else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-nums[i]]+nums[i]);
            }
        }
    }
    return dp[n-1][target]==target;
}

bool boolcanPartition(int* nums,int n){
    int sum=0;
    for(int i=0;i<n;++i) sum+=nums[i];
    if(sum%2==1) return false;
    int target=sum/2;
    //这里用二维数组处理
    bool** dp=new bool*[n];
    for(int i=0;i<n;++i){
        dp[i]=new bool[target+1];
        for(int j=0;j<=target;++j){
            dp[i][j]=false;
        }
    }
    //这里dp[i][j]表示下标0到i能够凑到j
    if(nums[0]<=target)  dp[0][nums[0]]=true;

    for(int i=1;i<n;++i){
        for(int j=1;j<=target;++j){
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i]){
                dp[i][j]=dp[i-1][j] || dp[i-1][j-nums[i]];
            }
        }
    }
    return dp[n-1][target];
}