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
//以下是所有函数声明
bool if_clause_satisfied(Clause clause,vector<literal> solution);
void sort_to_two_queue(queue<Clause> &formula,queue<Clause> &unsatisfied,vector<literal> solution);
int what_to_change(queue<Clause> unsatisfied,vector<literal> &solution);
//函数声明结束，下面是函数实现部分
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
    
}


int what_to_change(queue<Clause> unsatisfied,vector<literal> &solution){
    int minscores=100000000;
    int min_at_position=0;
    while(!unsatisfied.empty()){
        Clause considering=unsatisfied.front();
        for(int i=0;i<3;++i){
            if(solution[abs(considering[i])-1].scores<minscores){
                minscores=solution[abs(considering[i])-1].scores;
                min_at_position=abs(considering[i])-1;
            }
        }
        unsatisfied.pop();
    }
    if(solution[min_at_position].val==1){
        solution[min_at_position].val=0;
        solution[min_at_position].scores+=solution[min_at_position].minus;
    }
    else{
        solution[min_at_position].val=1;
        solution[min_at_position].scores+=solution[min_at_position].plus;
    }
    cout<<min_at_position<<endl;
    return min_at_position;
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
            solution[i].scores=solution[i].plus;
        }
        else{solution[i].val=0;
            solution[i].scores=solution[i].minus;
        }
    }

    queue<Clause> unsatisfied;
    //将满足的留在formula里面，不满足的放在unsatisfied里面
    sort_to_two_queue(formula,unsatisfied,solution);
    //下面是需要根据错误的表达式进行修改赋值
    //我希望修改到的是，修改之后错误队列中数量减少，也就是修改错误队列中错误数量最少得
    //同时，对正确formula队列的影响是最小的
    /*考虑到实际情况，错误队列中每个元素出现的次数差不多只出现一次或者两次（依照概率），所以修改的，应该是在外面
    影响最小的，我们定义分数score是表示修改之后出现的影响尽可能小
    如果当前变量赋值为1，也就是plus大于minus，我应该是希望plus尽可能小
    如果当前变量赋值为0，也就是minus大于plus，我应该是希望minus尽可能小
    最后优先修改分数少的,同时修改之后，转换minus和plus
    */
    while(!unsatisfied.empty()){
        what_to_change(unsatisfied,solution);
        sort_to_two_queue(formula,unsatisfied,solution);
    }
    //输出所有结果
    for(int i=0;i<n;++i){
        cout<<solution[i].val<<" ";
    }
    return 0;
}