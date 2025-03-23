//preview 0-1 bag question
#include <iostream>
#include <vector>
using namespace std;
int BagQuestion(int n,int* weight,int* value,int volume){
    if(volume==0) return 0;
    int** dp=new int*[n];
    for(int i=0;i<n;++i){
        dp[i]=new int[volume+1];
        for(int j=0;j<=volume;++j) dp[i][j]=0;
    }
    //这里dp数组的含义是dp[i][j]表示从下标0-i个物品中选择，容量j的情况下最大价值
    //第一步初始化,容量为0,最大价值全是0,dp[i][0]=0
    for(int i=0;i<n;++i){
        dp[i][0]=0;//这一步可以不用
    }
    //第二步初始化,i=0只能携带下标为0的
    for(int j=0;j<=volume;++j){
        if(j>=weight[0]){
            dp[0][j]=value[0];
        }
    }
    //以上完成了初始化过程,下面进行状态转移方程
    for(int i=1;i<n;++i){//这里遍历物品
        for(int j=1;j<=volume;++j){
            if(j<weight[i]) dp[i][j]=dp[i-1][j];
            else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
            }
        }
    }
    return dp[n-1][volume];
}
int oneBagQuestion(int n,int* weight,int* value,int volume)
{
    if(volume==0) return 0;
    //这个函数尝试用一维数组解决这个问题
    int* dp=new int[volume+1];
    for(int i=0;i<=volume;++i){
        dp[i]=0;//完成初始化
    }
    dp[0]=0;//其实这一步也可以不用写
    for(int i=0;i<n;++i){//遍历物品
        for(int j=volume;j>=weight[i];--j){
            dp[j]=max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }
    return dp[volume];
}

int main(){
    int n=5;
    int weight[3]={1,3,4};
    int value[3]={15,20,30};
    cout<<"Volume from 0 to 4 :"<<endl;
    for(int i=0;i<=4;++i){
        cout<<"volume "<<i<<" value "<<BagQuestion(n,weight,value,i)<<endl;
        cout<<"volume(one) "<<i<<" value "<<oneBagQuestion(n,weight,value,i)<<endl;
    }
}
