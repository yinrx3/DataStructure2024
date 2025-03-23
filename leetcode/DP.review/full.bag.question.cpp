//preview full bag question
#include <iostream>
#include <vector>
using namespace std;

int BagQuestionComplete(int n,int* weight,int* value,int volume){
    if(volume==0) return 0;
    int** dp=new int*[n];
    for(int i=0;i<n;++i){
        dp[i]=new int[volume+1];
        for(int j=0;j<=volume;++j) dp[i][j]=0;
    }
    //dp[0][j] 
    for(int j=1;j<=volume;++j){
        if(j>=weight[0]){dp[0][j]=(j/weight[0])*value[0];}
    }
    for(int i=1;i<n;++i){
        for(int j=1;j<=volume;++j){
            if(j<weight[i]){
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i]);
            }
        }
    }
    return dp[n-1][volume];
}

int BagQuestionCompleteOne(int n,int* weight,int* value,int volume){
    if(volume==0) return 0;
    int* dp=new int[volume+1];
    for(int i=0;i<=volume;++i){
        dp[i]=0;
    }
    for(int i=0;i<n;++i){
        for(int j=weight[i];j<=volume;++j){
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
        cout<<"volume "<<i<<" value "<<BagQuestionComplete(n,weight,value,i)<<endl;
        cout<<"volume "<<i<<" value ONE "<<BagQuestionCompleteOne(n,weight,value,i)<<endl;
       
    }
}