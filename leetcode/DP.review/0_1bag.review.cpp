//review 0-1 bag question
#include <iostream>
using namespace std;

int maxValueBag(int n,int* weight,int* value,int volume){
    if(volume==0) return 0;
    int** dp=new int*[n];
    for(int i=0;i<n;++i){
        dp[i]=new int[volume+1];
        for(int j=0;j<=volume;++j){
            dp[i][j]=0;//以上完成了初始化
        }
    }
    //  dp[i][0]=0    dp[0][j]=(?)
    for(int j=0;j<=volume;++j){
        if(weight[0]<=j){
            dp[0][j]=value[0];
        }
    }
    //下面就是利用状态转移方程了
    for(int i=1;i<=n-1;++i){//不断向背包加物品，遍历物品
        for(int j=1;j<=volume;++j){//遍历背包容量
            if(j-weight[i]<0){
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
            }
        }
    }
    return dp[n-1][volume];
}

int maxValueBagOne(int n,int* weight,int* value,int volume){
    if(volume==0) return 0;
    int* dp=new int[volume+1];
    for(int j=0;j<=volume;++j) dp[j]=0;

    for(int i=0;i<=n-1;++i){//遍历物品
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
        cout<<"volume "<<i<<" value "<<maxValueBag(n,weight,value,i)<<endl;
        cout<<"volume "<<i<<" value "<<maxValueBagOne(n,weight,value,i)<<endl;
    }
}

