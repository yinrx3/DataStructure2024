#include <iostream>
using namespace std;

/* Question 3 UPLOAD START */
int numOfFriendPairs(int n){
    // return the number of pairings with n people mod 10000019
    // max of n will be 150 in this problem
    if(n==0)return 1;
    else if(n==1) return 1;
    else if(n==2) return 2;
    else if(n==3) return 4;
    else if(n==4) return 10;
    int dp[n+1]={0};
    dp[0]=1;
    dp[1]=1;
    dp[2]=2;
    dp[3]=4;
    dp[4]=10;
    for(int i=5;i<=n;++i){
        dp[i]=(dp[i-1]+(i-1)*dp[i-2])%10000019;
    }
    return dp[n];
}
/* Question 3 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (3*i) << ": " << numOfFriendPairs(3*i) << endl;
    }
}

int main(){
    test();
    return 0;
}