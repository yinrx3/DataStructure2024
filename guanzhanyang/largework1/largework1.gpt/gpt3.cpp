#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 布尔可满足性问题
using Clause = vector<int>; // 使用一个容器存储一个三元布尔表达式
using Formula = vector<Clause>; // 再使用一个容器存储所有表达式

// 函数声明
bool if_pure_literal_elimination(Formula &formula, vector<int> &solution);
int if_pure_literal(Formula &formula, int xi, stack<int> &position);
bool if_Clause_Satisfied(Clause clause, vector<int> &solution);
bool solve_SAT(Formula &formula, vector<int> &solution);

// 纯文字消去函数
bool if_pure_literal_elimination(Formula &formula, vector<int> &solution) {
    bool if_delete_some_formula = false;
    int numword = solution.size();
    for (int xi = 0; xi < numword; ++xi) {
        stack<int> position;
        int result_if_pure_xi = if_pure_literal(formula, xi, position);
        if (result_if_pure_xi == 2) {
            solution[xi] = -1; // 空文字保持未赋值
        }
        if (result_if_pure_xi == 1) {
            solution[xi] = 1; // 纯正文字赋值为true
            while (!position.empty()) {
                formula.erase(formula.begin() + position.top());
                position.pop();
            }
            if_delete_some_formula = true;
        }
        if (result_if_pure_xi == -1) {
            solution[xi] = 0; // 纯负文字赋值为false
            while (!position.empty()) {
                formula.erase(formula.begin() + position.top());
                position.pop();
            }
            if_delete_some_formula = true;
        }
    }
    return if_delete_some_formula;
}

// 判断单个变量是否纯文字
int if_pure_literal(Formula &formula, int xi, stack<int> &position) {
    int xn = xi + 1; // 恢复成x_n的形式
    int size = formula.size();
    int numplus = 0, numminus = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (formula[i][j] == xn) {
                ++numplus;
                position.push(i);
            }
            if (formula[i][j] == -xn) {
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

// 测试在目前赋值下单个字句能否被满足，包括当前未赋值情况
bool if_Clause_Satisfied(Clause clause, vector<int> &solution) {
    for (int i = 0; i < 3; ++i) {
        int varIndex = abs(clause[i]) - 1; // 获取变量索引
        if ((clause[i] > 0 && solution[varIndex] == 1) || (clause[i] < 0 && solution[varIndex] == 0)) {
            return true; // 该子句被满足
        }
    }
    return false; // 不满足
}

// 递归回溯解决SAT问题
bool solve_SAT(Formula &formula, vector<int> &solution) {
    // 先消去纯文字
    while (if_pure_literal_elimination(formula, solution)) {}

    // 如果公式已空，则满足
    if (formula.empty()) {
        return true;
    }

    // 找到第一个未赋值的变量
    int varIndex = -1;
    for (int i = 0; i < solution.size(); ++i) {
        if (solution[i] == -1) {
            varIndex = i;
            break;
        }
    }
    if (varIndex == -1) return false; // 所有变量都赋值了，但公式没空则不满足

    // 进行分支搜索，尝试赋值为true和false
    for (int value = 0; value <= 1; ++value) {
        solution[varIndex] = value; // 尝试赋值
        // 剔除被赋值后无法满足的子句
        Formula newFormula;
        for (const auto &clause : formula) {
            if (!if_Clause_Satisfied(clause, solution)) {
                newFormula.push_back(clause); // 子句无法满足，加入新公式
            }
        }
        if (solve_SAT(newFormula, solution)) {
            return true; // 找到解
        }
        // 恢复状态
        solution[varIndex] = -1; // 恢复未赋值状态
    }
    return false; // 变量无法满足
}

int main() {
    int n = 0; // 变量个数
    int m = 0; // 表达式个数
    cin >> n >> m; // 输入变量和表达式的个数

    vector<int> solution(n, -1); // 每个变量有三个状态，未赋值是-1
    Formula formula; // 存储所有三元表达式

    // 输入表达式
    for (int i = 0; i < m; ++i) {
        Clause expression(3); // 每个表达式包含三个文字
        for (int j = 0; j < 3; ++j) {
            cin >> expression[j];
        }
        formula.push_back(expression);
    }

    // 尝试寻找解
    if (solve_SAT(formula, solution)) {
        cout << "SATISFIABLE:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "x" << (i + 1) << ": " << solution[i] << endl; // 输出赋值
        }
    } else {
        cout << "UNSATISFIABLE" << endl; // 不满足
    }

    return 0;
}