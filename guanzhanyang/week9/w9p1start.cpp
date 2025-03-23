#include <iostream>
using namespace std;

/* Question 1 UPLOAD START */

int numStepsToN_v2(int N, int mod_num){
    // calculate the number of ways to get to N
    // allowed step on each move: +1, +2, +3
    // However, no two consecutive steps are the same.
    if(N==0){return 1;}
    else if (N==1)return 1;
    else if(N==2) return 1;
    else if(N==3) return 3;
    int dp[N+1][4]={0};
    dp[1][1]=1;
    dp[2][2]=1;
    dp[3][3]=1;
    dp[3][2]=1;
    dp[3][1]=1;
    for(int i=4;i<=N;++i){
        for(int j=1;j<=3;++j){
            if(i>=j){
                for(int k=1;k<=3;++k){
                    if(k!=j){
                        dp[i][j]=(dp[i][j]+dp[i-j][k])%mod_num;
                    }
                }
            }
        }
    }
    int result=0;
    for(int i=1;i<=3;++i){
        result=(result+dp[N][i])%mod_num;
    }
    return result;
}

/* Question 1 UPLOAD END */

int main(){
    for(int i=0;i<=10;i++)
        cout << i << ": " << numStepsToN_v2(i,9999999) << endl;
    return 0;
}


/*
0: 1
1: 1
2: 1
3: 3
4: 3
5: 4
6: 8
7: 9
8: 12
9: 21
10: 27
*/