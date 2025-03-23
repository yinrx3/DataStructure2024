//474 一和零
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        //这里相当于是两个0-1背包问题
        //这里dp[i][j]表示最多有i个0和j个1
        int** dp=new int*[m+1];
        for(int i=0;i<=m;++i){
            dp[i]=new int[n+1];
            for(int j=0;j<=n;++j){
                dp[i][j]=0;
            }
        }
        
    }
};