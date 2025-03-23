#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
//布尔可满足性问题
using Clause=vector<int>;//使用一个容器存储一个三元布尔表达式
using Fomula=vector<Clause>;//再使用一个容器存储所有表达式
struct literal
{
    int name;
    int num_in_fomula=0;
    int val=-1;
    int num_satisfied=0;//用来存储当前极性下使得新满足true的表达式个数，方便从栈中回弹
    int num_assigment=0;//用来存储赋值的次数，如果赋值达到两次，就是两种极性都赋值了一遍，就要往回回弹上一个
};
//以上新定义的以及重新命名的表达式
int if_Clause_Satisfied(Clause clause,vector<literal> literal_solution);
bool if_Fomula_Satisfied(Fomula fomula,vector<literal> literal_solution);
void first_assigment_to_xi(queue<Clause> Clause_not_Satisfied,int xi,vector<literal> &literal_solution);
void one_by_one_get_xi(vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied);
void look_back_deal_c(int c,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied);
int once_false_look_back(int xk,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied);
bool xk_single_assigment_test(int xk,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied);
bool xk_both_assigment_test(int xk,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied);
/*对xi应该赋值为正极性还是负极性
这里queue<Clause> Clause_not_Satisfied不用传引用，防止改变，只是拷贝传参即可*/



//这个代码是为了根据出现次数进行重排literal
bool compareLiterals(const literal &a, const literal &b) {
    return a.num_in_fomula > b.num_in_fomula; // 降序排序
}
void sort_literal_by_num(Fomula fomula, vector<literal> &literal_solution) {
    for (int i = 0; i < literal_solution.size(); ++i) {
        int compare = literal_solution[i].name;
        int cnt_in_fomula = 0;
        for (int j = 0; j < fomula.size(); ++j) {
            Clause computing = fomula[j];
            for (int k = 0; k < 3; ++k) {
                if (abs(computing[k]) == compare) {
                    ++cnt_in_fomula;
                }
            }
        }
        literal_solution[i].num_in_fomula = cnt_in_fomula;
    }
    // 现在根据 num_in_fomula 进行重排
    sort(literal_solution.begin(), literal_solution.end(), compareLiterals);
}

bool compareLiteralsByName(const literal &a, const literal &b) {
    return a.name < b.name; // 升序排序
}

void sort_literal_by_name(vector<literal> &literal_solution) {
    sort(literal_solution.begin(), literal_solution.end(), compareLiteralsByName);
}

//下面开始函数定义部分
int if_Clause_Satisfied(Clause clause,vector<literal> literal_solution)//测试在目前赋值下单个字句能否被满足，包括当前未赋值情况
{
    //经过测试这个是对的
    //假设clause为1 -3 4，对应在solution里面结果为1 0 -1，存进clause_result_val
    //clause_solution_result 应该是1 1 -1
    vector<int> clause_result_val;//这个是clause里面三个对应项的结果
    for(int i=0;i<3;++i){
        clause_result_val.push_back(literal_solution[abs(clause[i])-1].val);
    }
    vector<int> clause_solution_result;//这个是在当前环境下的单个元素正负
    for(int i=0;i<3;++i){
        if((clause[i]>0&&clause_result_val[i]==1)||(clause[i]<0&&clause_result_val[i]==0)){clause_solution_result.push_back(1);}
        if((clause[i]>0&&clause_result_val[i]==0)||(clause[i]<0&&clause_result_val[i]==1)){clause_solution_result.push_back(0);}
        if(clause_result_val[i]==-1){clause_solution_result.push_back(-1);}
    }
    //返回值为1代表当前表达式确定为true，0代表确定为假，-1表示还有未定元
    //vector<int> clause_solution_result只要有一个为1，那么返回1.只有三个全是0返回0，只要有一个为-1，就返回-1
    if(clause_solution_result[0]==1||clause_solution_result[1]==1||clause_solution_result[2]==1){return 1;}
    else if(clause_solution_result[0]==0&&clause_solution_result[1]==0&&clause_solution_result[2]==0){return 0;}
    else{return -1;}
}

bool if_Fomula_Satisfied(Fomula fomula,vector<literal> literal_solution)//测试在目前赋值下整个布尔可满足方程组能否满足
{
    for(int i=0;i<fomula.size();++i)
    {
        if(if_Clause_Satisfied(fomula[i],literal_solution)!=1){
            return false;
        }
    }
    return true;
}

void first_assigment_to_xi(queue<Clause> Clause_not_Satisfied,int xi,vector<literal> &literal_solution)//对xi应该赋值为正极性还是负极性
{
    //这里只能传递拷贝值，不能传递引用
    //传递的是xi，不是它的下标索引
    //调用这个函数的时候一定是首次赋值，因此调用结束后num_assigment=1
    int numplus=0,numminus=0;
    while(!Clause_not_Satisfied.empty()){
        Clause clause_now_considering=Clause_not_Satisfied.front();
        for(int j=0;j<3;++j){
            if(clause_now_considering[j]==xi
            ){++numplus;}
            if(clause_now_considering[j]==-xi){++numminus;}
        }
        Clause_not_Satisfied.pop();
    }
    if(numminus>numplus){
        literal_solution[xi-1].val=0;
        literal_solution[xi-1].num_assigment=1;
    }
    else{
        literal_solution[xi-1].val=1;
        literal_solution[xi-1].num_assigment=1;
    }
}

void one_by_one_get_xi(vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied)
{
    int max=literal_solution.size();
    int xk=1;
    first_assigment_to_xi(Clause_not_Satisfied,xk,literal_solution);
    while(xk<=max){
        if(literal_solution[xk-1].num_assigment==1){//如果当前处理的是非回溯的
            if(xk_both_assigment_test(xk,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied)){
                ++xk;
                first_assigment_to_xi(Clause_not_Satisfied,xk,literal_solution);
            }
            else{
                xk=once_false_look_back(xk,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied);
            }
        }
        else{
            //如果当前处理的是回溯的
            if(xk_single_assigment_test(xk,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied)){
                ++xk;
                if(literal_solution[xk-1].val==-1){
                    first_assigment_to_xi(Clause_not_Satisfied,xk,literal_solution);
                }
            }
            else{
                literal_solution[xk-1].val=-1;
                literal_solution[xk-1].num_assigment=0;
                xk=once_false_look_back(xk,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied);
                //找到要回溯的点，特征是它的赋值次数变量一定是1，并且然后就要重新赋值
                //获取到之后下面还要再更改极性
                //有没有可能，回溯到的修改后依然不对呢，有可能，还要再往前回溯
            }
        }
    }
}

void look_back_deal_c(int c,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied)
{
    //这是仅有的传入进去的是c，位序，不是变量本身的顺序
    //这个函数操作，清空c对应的暂时满足栈
    while(literal_solution[c].num_satisfied!=0){
        Clause clause_back_to_queue=Clause_Temporary_Satisfied.top();//保存栈顶元素
        Clause_not_Satisfied.push(clause_back_to_queue);//栈顶元素压回栈
        Clause_Temporary_Satisfied.pop();//弹出栈顶元素
        --literal_solution[c].num_satisfied;
    }
}

int once_false_look_back(int xk,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied)
{
    //只有当k索引的元素赋值后存在不正确表达式才要调用这个回溯函数
    //函数的目标是找到上一个赋值次数为1的变量，并且要赋值为相反极性
    //找到上一个赋值次数不为2的
    int k=xk-1;//从变量名字转成位序
    //已经知道k对应位序不满足并且k对应的四个步骤已经处理
    int c=k-1;//这里用c返回，因为k已经处理成
    while(literal_solution[c].num_assigment==2){
        look_back_deal_c(c,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied);
        literal_solution[c].val=-1;
        literal_solution[c].num_assigment=0;
        --c;
    }
    //这里c已经是要回溯返回的了，但是c清空其对应的暂时满足栈，这里c是位序
    look_back_deal_c(c,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied);
    //然后对c索引根据其原先的值重新赋值
    if(literal_solution[c].val==0){
        literal_solution[c].val=1;
        literal_solution[c].num_assigment=2;
    }
    else if(literal_solution[c].val==1){
        literal_solution[c].val=0;
        literal_solution[c].num_assigment=2;
    }
    else{}
    return c+1;//返回的是变量本身文字，不是位序
}

bool xk_single_assigment_test(int xk,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied)
{
    //对于xk的首次单个极性赋值去测试是否满足
    //如果满足，就返回true，如果不满足，更改
    bool if_non_unsatisfied=true;
    int k=xk-1;//还原变量名字成它的位序
    int range_Clause=Clause_not_Satisfied.size();
    Clause clause_considering=Clause_not_Satisfied.front();
    for(int i=0;i<range_Clause;++i){
        if(if_Clause_Satisfied(clause_considering,literal_solution)==1){
            Clause_Temporary_Satisfied.push(clause_considering);
            ++literal_solution[k].num_satisfied;//增加计数，新满足的表达式个数
            Clause_not_Satisfied.pop();
            if(Clause_not_Satisfied.size()!=0){//这个仅在全部满足，且最后一个拿出时候出现队列为空的情况才会调用
                clause_considering=Clause_not_Satisfied.front();
            }
        }
        else if(if_Clause_Satisfied(clause_considering,literal_solution)==-1){
            Clause_not_Satisfied.pop();
            Clause_not_Satisfied.push(clause_considering);
            clause_considering=Clause_not_Satisfied.front();
        }
        else{
            if_non_unsatisfied=false;//意味着当前的赋值出现矛盾，这个函数内我们不改变极性
            break;
        }
    }
    //其实一旦出现错误，有四个事情需要做
    //1.从栈中还原literal_solution[k].num_satisfied个表达式退回队列
    //2.把相对应literal_solution[k].num_satisfied还原成0
    //3.4.更改对应元素的极性和改变赋值标记的次数（这个函数这两件事情不做）
    if(if_non_unsatisfied==true){return true;}
    else{
        while(literal_solution[k].num_satisfied!=0){
            Clause clause_back_to_queue=Clause_Temporary_Satisfied.top();//先获取栈顶元素
            Clause_not_Satisfied.push(clause_back_to_queue);//再将该元素压回队列
            Clause_Temporary_Satisfied.pop();//删去栈中相应表达式，即栈顶表达式
            --literal_solution[k].num_satisfied;
        }
        //这里完成了上面所说的事情1.2.我们在both里面做3.4
        //如果两次赋值都不行，就要回溯，回溯前当前位置赋值状态更改为未赋值状态
        return false;
    }
}

bool xk_both_assigment_test(int xk,vector<literal> &literal_solution,queue<Clause> &Clause_not_Satisfied,stack<Clause> &Clause_Temporary_Satisfied)
{
    //测试到xk的结果里面，对于xk，它的两种赋值都是假，就返回false
    int k=xk-1;//还原到位序
    if(xk_single_assigment_test(xk,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied)){return true;}
    else{
        if(literal_solution[k].val==0){
            literal_solution[k].val=1;
            literal_solution[k].num_assigment=2;
        }
        if(literal_solution[k].val==1){
            literal_solution[k].val=0;
            literal_solution[k].num_assigment=2;
        }
        if(xk_single_assigment_test(xk,literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied)){return true;}
        else{
            literal_solution[k].val=-1;
            literal_solution[k].num_assigment=0;
            return false;
        }
    }
}

int main()
{
    int n=0;//这是变量个数
    int m=0;//这是表达式个数
    cin>>n;
    cin>>m;//以上是输入的第一部分.
    /*下面我们需要依次读入m个布尔表达式，理论上每个表达式含有三个文字。每个表达式应该对应三块内容。表达式内容*/
    Fomula fomula;//把所有三元表达式放进一个向量表
    //下面传入数据
    for(int i=0;i<m;++i){
        Clause expression;
        for(int j=0;j<3;++j){
            int data=0;
            cin>>data;
            expression.push_back(data);
        }
        fomula.push_back(expression);
    }
    //首先先传入索引元
    queue<Clause> Clause_not_Satisfied;//接受全部目前的fomula
    stack<Clause> Clause_Temporary_Satisfied;//初始为空
    vector<literal> literal_solution(n);
    for(int i=0;i<n;++i){
        literal_solution[i].name=i+1;
    }//这里传入了文字名
    //下面依次获取各个文字出现的次数
    sort_literal_by_num(fomula,literal_solution);

    //所有的表达式放进队列 queue<Clause> Clause_not_Satisfied
    for(int i=0;i<fomula.size();++i){
        Clause_not_Satisfied.push(fomula[i]);
    }
    //创建 vector<literal> literal_solution
    one_by_one_get_xi(literal_solution,Clause_not_Satisfied,Clause_Temporary_Satisfied);
    //测试:输出所有文字状态

    if(if_Fomula_Satisfied(fomula,literal_solution)){
        cout<<"good"<<endl;
    }else{
        cout<<"bad"<<endl;
    }




    sort_literal_by_name(literal_solution);

    for(int i=0;i<literal_solution.size();++i){
        cout<<literal_solution[i].val<<" ";
    }
    cout<<endl;

    
    
    return 0;
}