#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 布尔可满足性问题
using Clause = vector<int>; // 使用一个容器存储一个三元布尔表达式
using Fomula = vector<Clause>; // 再使用一个容器存储所有表达式

void pure_literal_elimination(Fomula &fomula, vector<int> &solution);
int if_pure_literal(Fomula &fomula, int xi, stack<int> &position);
void unit_propagation(Fomula &fomula, vector<int> &solution);
bool dpll(Fomula &fomula, vector<int> &solution, stack<pair<int, bool>> &decision_stack);

// 纯文字消去函数
void pure_literal_elimination(Fomula &fomula, vector<int> &solution) {
    int numword = solution.size();
    for (int xi = 0; xi < numword; ++xi) {
        stack<int> position;
        int result_if_pure_xi = if_pure_literal(fomula, xi, position);
        if (result_if_pure_xi == 2) {
            solution[xi] = 1; // 空文字直接赋值为true
        }
        if (result_if_pure_xi == 1) {
            solution[xi] = 1; // 纯正文字直接赋值true, 再把含有纯正文字表达式的给删除
            while (!position.empty()) {
                fomula.erase(fomula.begin() + position.top());
                position.pop();
            }
        }
        if (result_if_pure_xi == -1) {
            solution[xi] = 0; // 纯负文字直接赋值为否, 再把含有纯正文字表达式的给删除
            while (!position.empty()) {
                fomula.erase(fomula.begin() + position.top());
                position.pop();
            }
        }
    }
}

// 判断单个变量是否纯文字, 空文字, 杂文字并记录含有这个文字的表达式位置
int if_pure_literal(Fomula &fomula, int xi, stack<int> &position) {
    int xn = xi + 1; // 恢复成x_n的形式
    int size = fomula.size();
    // 设置两个变量分别统计正文字和负文字数量
    int numplus = 0, numminus = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (fomula[i][j] == xn) {
                ++numplus;
                position.push(i);
            }
            if (fomula[i][j] == -xn) {
                ++numminus;
                position.push(i);
            }
        }
    }
    if (numplus == 0 && numminus == 0) {
        return 2; // 空文字返回2
    }
    if (numplus != 0 && numminus != 0) {
        return 0; // 杂文字返回0
    }
    if (numplus != 0 && numminus == 0) {
        return 1; // 纯正文字返回1
    }
    if (numplus == 0 && numminus != 0) {
        return -1; // 纯负文字返回-1
    }
    return 0;
}

// 单元传播函数
void unit_propagation(Fomula &fomula, vector<int> &solution) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto &clause : fomula) {
            int unassigned = 0, unit = 0;
            for (int literal : clause) {
                int var = abs(literal) - 1;
                if (solution[var] == -1) {
                    unassigned++;
                    unit = literal;
                } else if ((literal > 0 && solution[var] == 1) || (literal < 0 && solution[var] == 0)) {
                    goto next_clause; // 跳过这个子句
                }
            }
            if (unassigned == 1) {
                int var = abs(unit) - 1;
                solution[var] = (unit > 0) ? 1 : 0;
                changed = true;
            }
            next_clause:;
        }
    }
}

// 冲突检测和子句学习
bool conflict_analysis(Fomula &fomula, vector<int> &solution, stack<pair<int, bool>> &decision_stack) {
    for (const auto &clause : fomula) {
        bool all_false = true;
        for (int literal : clause) {
            int var = abs(literal) - 1;
            if (solution[var] == -1 || (literal > 0 && solution[var] == 1) || (literal < 0 && solution[var] == 0)) {
                all_false = false;
                break;
            }
        }
        if (all_false) {
            // 发现冲突
            return true;
        }
    }
    return false;
}

// DPLL 算法
bool dpll(Fomula &fomula, vector<int> &solution, stack<pair<int, bool>> &decision_stack) {
    // 单元传播
    unit_propagation(fomula, solution);

    // 冲突检测
    if (conflict_analysis(fomula, solution, decision_stack)) {
        // 回溯
        if (decision_stack.empty()) {
            return false; // 无法找到解
        }
        auto last_decision = decision_stack.top();
        decision_stack.pop();
        int var = last_decision.first;
        solution[var] = last_decision.second ? 0 : -1; // 回溯并尝试相反的赋值
        return dpll(fomula, solution, decision_stack);
    }

    // 检查是否所有子句都满足
    for (const auto &clause : fomula) {
        bool satisfied = false;
        for (int literal : clause) {
            int var = abs(literal) - 1;
            if ((literal > 0 && solution[var] == 1) || (literal < 0 && solution[var] == 0)) {
                satisfied = true;
                break;
            }
        }
        if (!satisfied) {
            // 选择一个未赋值的变量进行决策
            for (int i = 0; i < solution.size(); ++i) {
                if (solution[i] == -1) {
                    solution[i] = 1; // 假设为真
                    decision_stack.push({i, true});
                    if (dpll(fomula, solution, decision_stack)) {
                        return true;
                    }
                    // 回溯
                    solution[i] = 0; // 假设为假
                    decision_stack.push({i, false});
                    if (dpll(fomula, solution, decision_stack)) {
                        return true;
                    }
                    // 回溯
                    solution[i] = -1;
                    decision_stack.pop();
                    return false; // 无法找到解
                }
            }
        }
    }

    return true; // 所有子句都满足
}

int main() {
    int n = 0; // 这是变量个数
    int m = 0; // 这是表达式个数
    cin >> n;
    cin >> m; // 以上是输入的第一部分.

    vector<int> solution(n, -1); // 我们定义一个结构体存储n个变量，每个变量有三个状态，true是1，false是0，未赋值是-1
    Fomula fomula; // 把所有三元表达式放进一个向量表

    // 读入m个布尔表达式
    for (int i = 0; i < m; ++i) {
        Clause expression;
        for (int j = 0; j < 3; ++j) {
            int data = 0;
            cin >> data;
            expression.push_back(data);
        }
        fomula.push_back(expression);
    }

    // 纯文字消去
    pure_literal_elimination(fomula, solution);

    // 初始化决策栈
    stack<pair<int, bool>> decision_stack;
    
    // 运行 DPLL 算法
    if (dpll(fomula, solution, decision_stack)) {
        cout << "SAT" << endl;
        for (int i = 0; i < solution.size(); ++i) {
            cout << i + 1 << ": " << solution[i] << endl;
        }
    } else {
        cout << "UNSAT" << endl;
    }

    return 0;
}