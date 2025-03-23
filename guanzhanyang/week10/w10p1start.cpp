#include <iostream>
using namespace std;

/* UPLOAD START */

int longestSubsequenceLength(int* arr, int n){
    //这里dp[i]代表到第i个（包含）元素最长递增子序列的长度
    int dp[n+1];
    
    // 初始化dp数组，每个元素本身就是一个长度为1的递增子序列
    for (int i = 0; i <= n; ++i) {
        dp[i] = 1;
    }
    
    // 计算dp数组的值
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (arr[j-1] < arr[i-1]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    // 找到dp数组中的最大值
    int maxLength = 0;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }
    
    return maxLength;
}

/* UPLOAD END */

void test1(){
    int a[8] = {10,9,2,5,3,7,101,18};
    cout << longestSubsequenceLength(a,8) << endl; //4
}

void test2(){
    int a[7] = {1,2,3,5,3,7,8};
    cout << longestSubsequenceLength(a,7) << endl; //6
}

int main(){
    test1();
    test2();
    return 0;
}