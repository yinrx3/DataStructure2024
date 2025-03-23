#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
using Clause=vector<int>;
struct literal
{
    int val=-1;
    int minus=0;
    int plus=0;
    int scores=0;
};
//以上声明了存储解的形式
bool if_clause_satisfied(Clause clause,vector<literal> solution){
    //检测在当前解下能否被满足
    for(int i=0;i<3;++i){
        if((clause[i]>0&&solution[clause[i]-1].val==1)||(clause[i]<0&&solution[-clause[i]-1].val==0)){
            return true;
        }
    }
    return false;
}

void sort_to_two_queue(queue<Clause> &formula,queue<Clause> &unsatisfied,vector<literal> solution)
{
    //这个函数是将当前赋值下面，满足的留在formula里面，不满足的放进unsatiefied
    int size_formula=formula.size();
    int size_unsatisfied=unsatisfied.size();
    for(int i=0;i<size_formula;++i){
        if(if_clause_satisfied(formula.front(),solution)){
            formula.push(formula.front());
            formula.pop();
        }
        else{
            unsatisfied.push(formula.front());
            formula.pop();
        }
    }
    for(int j=0;j<size_unsatisfied;++j){
        if(if_clause_satisfied(unsatisfied.front(),solution)){
            formula.push(unsatisfied.front());
            unsatisfied.pop();
        }
        else{
            unsatisfied.push(unsatisfied.front());
            unsatisfied.pop();
        }
    }
}

int main()
{
    int n=0,m=0;
    cin>>n>>m;
    vector<literal> solution(n);
    queue<Clause> formula;
    for(int i=0;i<m;++i){
        Clause expression(3);
        for(int j=0;j<3;++j){
            cin>>expression[j];
            if(expression[j]>0){
                ++solution[expression[j]-1].plus;
            }
            else{
                ++solution[-expression[j]-1].minus;
            }
        }
        formula.push(expression);
    }

    //根据以上表达式中对应元素的个数赋予初值
    for(int i=0;i<n;++i){
        if(solution[i].plus>=solution[i].minus){
            solution[i].val=1;
        }
        else{solution[i].val=0;}
        solution[i].scores=abs(solution[i].plus-solution[i].minus);
    }

    queue<Clause> unsatisfied;
    //将满足的留在formula里面，不满足的放在unsatisfied里面
    sort_to_two_queue(formula,unsatisfied,solution);


    
    //输出所有结果
    for(int i=0;i<n;++i){
        cout<<solution[i].val<<" ";
    }



    return 0;
}