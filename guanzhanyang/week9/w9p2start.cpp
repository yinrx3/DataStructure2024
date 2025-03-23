#include <iostream>
using namespace std;

/* Question 2 UPLOAD START */

int numOfBinaryTrees(int n){
    // return the number of binary trees with n nodes mod 30011
    // max of n will be 150 in this problem
    //dp[i]代表含有i个节点的二叉树数量
    int dp[n+1]={0};
    dp[0]=1;dp[1]=1;dp[2]=2;dp[3]=5;
    //考虑左右子树的情况，有一个根节点，左孩子对应的树是k个，右孩子对应的树是n-1-k个
    //k最小是0最大是i-1
    for(int i=4;i<=n;++i){
        for(int k=0;k<=i-1;++k){
            dp[i]=(dp[i]+dp[k]*dp[i-1-k])%30011;
        }
    }
    return dp[n];


}
/* Question 2 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (2*i) << ": " << numOfBinaryTrees(2*i) << endl;
    }
}

int main(){
    test();
    return 0;
}