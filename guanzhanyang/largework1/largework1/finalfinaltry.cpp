#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;
//布尔可满足性问题
using Clause=vector<int>;//使用一个容器存储一个三元布尔表达式
struct literal
{
    int val=-1;
    int num_satisfied=0;
    int num_assigment=0;
    //这三个仅仅在决定给谁赋值时候有用
    int score=0;
};
//首先是所有函数的声明
void one_by_one_get_xk(int n,queue<Clause> &clause_left,stack<Clause> &satisfied,
stack<int> &solution_considered,vector<literal> &solution);
int once_false_look_back(int xk,queue<Clause> &clause_left,stack<Clause> &satisfied,
stack<int> &solution_considered,vector<literal> &solution);
int what_to_assigment(int n,queue<Clause> clause_left,vector<literal> solution);
int assigment(int n,queue<Clause> clause_left,vector<literal> &solution,stack<int> &solution_considered);
bool single_cur_solution_test(int xk,queue<Clause> &clause_left,stack<Clause> &satisfied,vector<literal> &solution);
int if_clause_satisfied_solution(Clause clause,vector<literal> solution);


//下面是所有函数的定义
void one_by_one_get_xk(int n,queue<Clause> &clause_left,stack<Clause> &satisfied,
stack<int> &solution_considered,vector<literal> &solution)
{
    int xk=assigment(n,clause_left,solution,solution_considered);
    while(!clause_left.empty()){
        if(solution[xk-1].num_assigment==1){
            //如果当前处理的是非回溯的
            if(single_cur_solution_test(xk,clause_left,satisfied,solution)){
                if(!clause_left.empty()){
                    xk=assigment(n,clause_left,solution,solution_considered);
                }
                else{break;}
            }
            else{
                if(solution[xk-1].val==0){
                    solution[xk-1].val=1;
                    solution[xk-1].num_assigment=2;
                }
                else{
                    solution[xk-1].val=0;
                    solution[xk-1].num_assigment=2;
                }
                if(single_cur_solution_test(xk,clause_left,satisfied,solution)){
                    if(!clause_left.empty()){
                    xk=assigment(n,clause_left,solution,solution_considered);
                }
                    else{break;}
                }
                else{
                    xk=once_false_look_back(xk,clause_left,satisfied,solution_considered,solution);
                }
            }
        }
        else{
            //如果当前处理的回溯的
            if(single_cur_solution_test(xk,clause_left,satisfied,solution)){
                if(!clause_left.empty()){
                    xk=assigment(n,clause_left,solution,solution_considered);
                }
                else{break;}
            }
            else{
                solution[xk-1].val=-1;
                solution[xk-1].num_assigment=0;
                xk=once_false_look_back(xk,clause_left,satisfied,solution_considered,solution);
            }
        }
    }
}

int once_false_look_back(int xk,queue<Clause> &clause_left,stack<Clause> &satisfied,
stack<int> &solution_considered,vector<literal> &solution)
{
    solution_considered.pop();
    solution[xk-1].val=-1;
    solution[xk-1].num_assigment=0;
    xk=solution_considered.top();
    while(solution[xk-1].num_assigment==2){
        while(solution[xk-1].num_satisfied!=0){
            clause_left.push(satisfied.top());
            satisfied.pop();
            --solution[xk-1].num_satisfied;
        }
        solution[xk-1].num_satisfied=0;
        solution[xk-1].num_assigment=0;
        solution[xk-1].val=-1;
        solution_considered.pop();
        xk=solution_considered.top();
    }
    //已经找到要回溯的了，现在再一次清空暂时满足栈
    while(solution[xk-1].num_satisfied!=0){
        clause_left.push(satisfied.top());
        satisfied.pop();
        --solution[xk-1].num_satisfied;
    }
    solution[xk-1].num_assigment=2;
    if(solution[xk-1].val==1){
        solution[xk-1].val=0;
    }
    else if(solution[xk-1].val==0){
        solution[xk-1].val=1;
    }
    return xk;
}

int what_to_assigment(int n,queue<Clause> clause_left,vector<literal> solution)
{
    //这个里面不进行进出栈和对solution操作，只返回应该赋值的名字和位序
    //这个里面实际上对solution不进行操作
    //目的是找出当前剩下的clause当中数值仍然是-1（未赋值）的变量
    while(!clause_left.empty()){
        Clause front=clause_left.front();
        for(int i=0;i<3;++i){
            if(solution[abs(front[i])-1].val==-1){
                if(front[i]>0){
                    ++solution[abs(front[i])-1].score;
                }
                else{
                    --solution[abs(front[i])-1].score;
                }
            }
        }
        clause_left.pop();
    }
    //目的是找到剩下的里面错误赋值后错误次数最少

    int maxscore=-1;
    int maxindex=-1;//存储的变量名字不是位序
    for(int i=0;i<n;++i){
        if(solution[i].val==-1){
            if(abs(solution[i].score)>maxscore){
                maxscore=abs(solution[i].score);
                maxindex=i+1;
            }
        }
    }
    if(solution[maxindex-1].score>=0){
        return maxindex;
    }
    else{
        return -maxindex;
    }
    //如果赋正值，返回要赋值的变量的名字
    //如果赋非值，返回要赋值的变量的名字的相反数
}

int assigment(int n,queue<Clause> clause_left,vector<literal> &solution,stack<int> &solution_considered)
{
    int assig=what_to_assigment(n,clause_left,solution);
    int xk=abs(assig);
    if(assig>0){solution[assig-1].val=1;solution_considered.push(xk);}
    else{solution[-assig-1].val=0;solution_considered.push(xk);}
    solution[xk-1].num_assigment=1;
    return xk;
    //这个函数完成赋值，修改赋值次数，进栈的操作
}

bool single_cur_solution_test(int xk,queue<Clause> &clause_left,stack<Clause> &satisfied,vector<literal> &solution)
{
    bool result=true;
    //只需要判断是否存在不满足的式子，即哪怕全部都是无法判断的也返回true
    //如果出现一个不满足，就要把1.暂时满足的倒回去2.对应的num_satisfied=0重新设置为0
    //这个将栈什么的都传入进去，进栈出栈操作全部要做（如果出现错误的话）
    int size_left=clause_left.size();
    for(int i=0;i<size_left;++i){
        Clause considering=clause_left.front();
        if(if_clause_satisfied_solution(considering,solution)==1){
            satisfied.push(considering);
            clause_left.pop();
            ++solution[xk-1].num_satisfied;
        }
        else if(if_clause_satisfied_solution(considering,solution)==-1){
            clause_left.push(clause_left.front());
            clause_left.pop();
        }
        else{
            result=false;
            break;
        }
    }
    if(result){return result;}
    else{
        while(solution[xk-1].num_satisfied!=0){
            clause_left.push(satisfied.top());
            satisfied.pop();
            --solution[xk-1].num_satisfied;
        }
        return result;
    }
}

int if_clause_satisfied_solution(Clause clause,vector<literal> solution)
{
    //如果可以满足就返回1，错误就返回0，无法判断就返回-1
    int iffalse=0;//判断是否错误，如果一个错误就+1，最后如果是3就返回结果0
    for(int i=0;i<3;++i){
        if((clause[i]>0&&solution[clause[i]-1].val==1)||(clause[i]<0&&solution[-clause[i]-1].val==0))
        {return 1;}
        if((clause[i]>0&&solution[clause[i]-1].val==0)||(clause[i]<0&&solution[-clause[i]-1].val==1))
        {++iffalse;}
    }
    if(iffalse==3){return 0;}
    else{return -1;}
}


//下面是主函数
int main()
{
    int n=0;//这是变量个数
    int m=0;//这是表达式个数
    cin>>n;
    cin>>m;//以上是输入的第一部分.
    queue<Clause> clause_left;
    stack<Clause> satisfied;
    for(int i=0;i<m;++i){
        Clause expression(3);
        for(int j=0;j<3;++j){
            cin>>expression[j];
        }
        clause_left.push(expression);
    }
    stack<int> solution_considered;
    vector<literal> solution(n);
    //这两个同时存储解的情况
    one_by_one_get_xk(n,clause_left,satisfied,solution_considered,solution);
    for(int i=0;i<n;++i){
        if(solution[i].val==-1){
            cout<<1<<" ";
        }
        else{
            cout<<solution[i].val<<" ";
        }
    }
    cout<<endl;
    return 0;
}
