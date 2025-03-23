#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;

// 布尔可满足性问题
using Clause = vector<int>; // 使用一个容器存储一个三元布尔表达式
using Formula = vector<Clause>; // 再使用一个容器存储所有表达式
struct literal {
    int val = -1;
    int num_satisfied = 0; // 用来存储当前极性下使得新满足true的表达式个数，方便从栈中回弹
    int num_assignment = 0; // 用来存储赋值的次数，如果赋值达到两次，就是两种极性都赋值了一遍，就要往回回弹上一个
};

// 以上新定义的以及重新命名的表达式
int if_Clause_Satisfied(Clause clause, vector<literal> literal_solution);
bool if_Formula_Satisfied(Formula formula, vector<literal> literal_solution);
void first_assignment_to_xi(queue<Clause> Clause_not_Satisfied, int xi, vector<literal> &literal_solution);
void one_by_one_get_xi(vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied);
int once_false_look_back(int xk, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied);
bool xk_single_assignment_test(int xk, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied);
bool xk_both_assignment_test(int xk, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied);
void look_back_deal_c(int c, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied);

// 下面开始函数定义部分
int if_Clause_Satisfied(Clause clause, vector<literal> literal_solution) {
    vector<int> clause_result_val; // 这个是clause里面三个对应项的结果
    for (int i = 0; i < 3; ++i) {
        clause_result_val.push_back(literal_solution[abs(clause[i]) - 1].val);
    }
    vector<int> clause_solution_result; // 这个是在当前环境下的单个元素正负
    for (int i = 0; i < 3; ++i) {
        if ((clause[i] > 0 && clause_result_val[i] == 1) || (clause[i] < 0 && clause_result_val[i] == 0)) {
            clause_solution_result.push_back(1);
        }
        if ((clause[i] > 0 && clause_result_val[i] == 0) || (clause[i] < 0 && clause_result_val[i] == 1)) {
            clause_solution_result.push_back(0);
        }
        if (clause_result_val[i] == -1) {
            clause_solution_result.push_back(-1);
        }
    }
    // 返回值为1代表当前表达式确定为true，0代表确定为假，-1表示还有未定元
    if (clause_solution_result[0] == 1 || clause_solution_result[1] == 1 || clause_solution_result[2] == 1) {
        return 1;
    } else if (clause_solution_result[0] == 0 && clause_solution_result[1] == 0 && clause_solution_result[2] == 0) {
        return 0;
    } else {
        return -1;
    }
}

bool if_Formula_Satisfied(Formula formula, vector<literal> literal_solution) {
    for (int i = 0; i < formula.size(); ++i) {
        if (if_Clause_Satisfied(formula[i], literal_solution) != 1) {
            return false;
        }
    }
    return true;
}

void first_assignment_to_xi(queue<Clause> Clause_not_Satisfied, int xi, vector<literal> &literal_solution) {
    if (xi <= 0 || xi > literal_solution.size() + 1) {
        cout << "Invalid variable index: " << xi << endl;
        return;
    }
    int numplus = 0, numminus = 0;
    while (!Clause_not_Satisfied.empty()) {
        Clause clause_now_considering = Clause_not_Satisfied.front();
        for (int j = 0; j < 3; ++j) {
            if (clause_now_considering[j] == xi) {
                ++numplus;
            }
            if (clause_now_considering[j] == -xi) {
                ++numminus;
            }
        }
        Clause_not_Satisfied.pop();
    }
    if (numminus > numplus) {
        literal_solution[xi - 1].val = 0;
        literal_solution[xi - 1].num_assignment = 1;
    } else {
        literal_solution[xi - 1].val = 1;
        literal_solution[xi - 1].num_assignment = 1;
    }
}

void one_by_one_get_xi(vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied) {
    int max = literal_solution.size();
    int xk = 1;
    first_assignment_to_xi(Clause_not_Satisfied, xk, literal_solution);
    while (xk <= max) {
        if (xk_both_assignment_test(xk, literal_solution, Clause_not_Satisfied, Clause_Temporary_Satisfied)) {
            ++xk;
            if (xk <= max) {
                first_assignment_to_xi(Clause_not_Satisfied, xk, literal_solution);
            }
        } else {
            xk = once_false_look_back(xk, literal_solution, Clause_not_Satisfied, Clause_Temporary_Satisfied);
            if (xk == 0) break; // 如果回溯到0，停止循环
        }
    }
}

void look_back_deal_c(int c, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied) {
    for (int i = 0; i < literal_solution[c].num_satisfied; ++i) {
        Clause clause_back_to_queue = Clause_Temporary_Satisfied.top();
        Clause_not_Satisfied.push(clause_back_to_queue);
        Clause_Temporary_Satisfied.pop();
    }
    literal_solution[c].num_satisfied = 0;
    literal_solution[c].num_assignment = 0;
}

int once_false_look_back(int xk, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied) {
    int k = xk - 1; // 从变量名字转成位序
    int c = k - 1; // 这里用c返回，因为k已经处理成
    while (literal_solution[c].num_assignment == 2) {
        look_back_deal_c(c, literal_solution, Clause_not_Satisfied, Clause_Temporary_Satisfied);
        --c;
    }
    return c + 1; // 返回的是变量本身文字，不是位序
}

bool xk_single_assignment_test(int xk, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied) {
    bool if_non_unsatisfied = true;
    int k = xk - 1; // 还原变量名字成它的位序
    int range_Clause = Clause_not_Satisfied.size();
    for (int i = 0; i < range_Clause; ++i) {
        Clause clause_considering = Clause_not_Satisfied.front();
        if (if_Clause_Satisfied(clause_considering, literal_solution) == 1) {
            Clause_Temporary_Satisfied.push(clause_considering);
            ++literal_solution[k].num_satisfied;
            Clause_not_Satisfied.pop();
        } else if (if_Clause_Satisfied(clause_considering, literal_solution) == -1) {
            Clause_not_Satisfied.pop();
            Clause_not_Satisfied.push(clause_considering);
        } else {
            if_non_unsatisfied = false;
            break;
        }
    }
    if (if_non_unsatisfied) {
        for (int j = 0; j < literal_solution[k].num_satisfied; ++j) {
            Clause clause_back_to_queue = Clause_Temporary_Satisfied.top();
            Clause_not_Satisfied.push(clause_back_to_queue);
            Clause_Temporary_Satisfied.pop();
        }
        literal_solution[k].num_satisfied = 0;
        literal_solution[k].num_assignment = 0;
        return false;
    }
    return true;
}

bool xk_both_assignment_test(int xk, vector<literal> &literal_solution, queue<Clause> &Clause_not_Satisfied, stack<Clause> &Clause_Temporary_Satisfied)
{
int k = xk - 1; // 还原到位序
if (xk_single_assignment_test(xk, literal_solution, Clause_not_Satisfied, Clause_Temporary_Satisfied)) {
return true;
} else {
// 重置当前变量的值，尝试另一种赋值
if (literal_solution[k].val == 0) {
literal_solution[k].val = 1;
} else if (literal_solution[k].val == 1) {
literal_solution[k].val = 0;
}
literal_solution[k].num_assignment = 2; // 标记为已经尝试过两种赋值
// 再次测试当前变量的另一种赋值
return xk_single_assignment_test(xk, literal_solution, Clause_not_Satisfied, Clause_Temporary_Satisfied);
}
}

int main() {
int n = 0; // 这是变量个数
int m = 0; // 这是表达式个数
cin >> n;
cin >> m; // 以上是输入的第一部分
Formula formula; // 把所有三元表达式放进一个向量表
// 下面传入数据
for (int i = 0; i < m; ++i) {
    Clause expression;
    for (int j = 0; j < 3; ++j) {
        int data = 0;
        cin >> data;
        expression.push_back(data);
    }
    formula.push_back(expression);
}

queue<Clause> Clause_not_Satisfied; // 接受全部目前的formula
stack<Clause> Clause_Temporary_Satisfied; // 初始为空

vector<literal> literal_solution(n);
// 初始化literal_solution
for (int i = 0; i < n; ++i) {
    literal_solution[i].val = -1; // 初始化为未赋值状态
}

// 所有的表达式放进队列 queue<Clause> Clause_not_Satisfied
for (int i = 0; i < formula.size(); ++i) {
    Clause_not_Satisfied.push(formula[i]);
}

// 开始求解过程
one_by_one_get_xi(literal_solution, Clause_not_Satisfied, Clause_Temporary_Satisfied);

// 测试:输出所有文字状态
for (int i = 0; i < literal_solution.size(); ++i) {
    cout << literal_solution[i].val << " ";
}
cout << endl;

return 0;
}