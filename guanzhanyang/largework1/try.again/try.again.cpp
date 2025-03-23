#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
using Clause=vector<int>;
struct literal{
    int name;
    int val=-1;
    int plus=0;
    int minus=0;
    int score=0;
};
//以上是基本定义的内容
//以下是函数声明部分

//以下是函数定义部分
int what_to_assigment(queue<Clause> formula_left,int n)
{
    //这里n是变量的个数
    //根据剩下的formula，找出一个相对极性最大的进行赋值
    vector<literal> find_assigmrnt(n);
    while(!formula_left.empty()){
        Clause considering=formula_left.front();
        for(int i=0;i<3;++i){
            if(considering[i]>0){
                ++find_assigmrnt[considering[i]-1].plus;
                ++find_assigmrnt[considering[i]-1].score;
            }
            else{
                find_assigmrnt[-considering[i]-1].minus;
                --find_assigmrnt[-considering[i]-1].score;
            }
        }
        formula_left.pop();
    }
    int maxscore=0;
    int maxscore_literal=0;
    for(int i=0;i<n;++i){
        find_assigmrnt[i].name=i+1;
        if(abs(find_assigmrnt[i].score)>maxscore){
            maxscore=abs(find_assigmrnt[i].score);
            maxscore_literal=i+1;
        }
    }
    if(find_assigmrnt[maxscore_literal-1].score>=0){
        return maxscore_literal;
    }
    else{
        return -maxscore_literal;
    }
    //这个函数找到剩下的里面出现的最多的
    //如果正极性出现的多，就返回 +变量名，如果负极性更多，就返回 -变量名
}

void sort_to_two_queue(queue<Clause> &formula_left,queue<Clause> &satisfied,vector<literal> solution)
{

}

bool if_clause_satisfied(Clause clause,vector<literal> solution){
    //检测在当前解下能否被满足
    for(int i=0;i<3;++i){
        if((clause[i]>0&&solution[clause[i]-1].val==1)||(clause[i]<0&&solution[-clause[i]-1].val==0)){
            return true;
        }
    }
    return false;
}


int main(){
    int n=0,m=0;
    cin>>n>>m;
    vector<literal> solution(n);
    for(int i=0;i<n;++i){
        solution[i].name=i+1;
    }
    queue<Clause> formula_left;
    queue<Clause> satisfied;
    for(int i=0;i<m;++i){
        Clause expression(3);
        for(int j=0;j<3;++j){
            cin>>expression[j];
        }
        formula_left.push(expression);
    }
    queue<literal> been_assigment;
    queue<literal> left_literal;



    while(!formula_left.empty()&&left_literal.empty()){
        int name_to_assig=what_to_assigment(formula_left,n);
        if(name_to_assig>0){solution[name_to_assig-1].val=1;}
        else{solution[name_to_assig-1].val=0;}

    }



    return 0;
}