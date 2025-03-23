#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size=nums.size();
        int* dp=new int[size];
        for(int i=0;i<size;++i){
            dp[i]=1;
        }
        //以上是初始化过程
        for(int i=1;i<size;++i){
            for(int j=0;j<i;++j){
                if(nums[i]>nums[j]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
        }
        int result=0;
        for(int i=0;i<size;++i){
            result=max(result,dp[i]);
        }
        return result;
    }
};
