//组合总数

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int* dp=new int[target+1];
        for(int i=0;i<=target;++i){dp[i]=0;}
        dp[0]=1;
        //求排列，先遍历背包
        for(int j=1;j<=target;++j){
            for(int i=0;i<nums.size();++i){
                if(j>=nums[i]){
                    dp[j]+=dp[j-nums[i]];
                }
            }
        }
        return dp[target];
    }
};